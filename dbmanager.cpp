#include "dbmanager.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    // create database file if one does not exist
    if (!QFile::exists(path)) {
        QFile file("database.db");
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        file.close();
    }
    // configure & open database connection
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }
    createTable();
}

DbManager::~DbManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DbManager::isOpen() const { return m_db.isOpen(); }

bool DbManager::createTable() const
{
    bool success = false;

    QSqlQuery query;
    query.prepare(
        "CREATE TABLE Film (id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "title      VARCHAR NOT NULL,"
        "year       INTEGER NOT NULL,"
        "imdbRating DOUBLE,"
        "userRating DOUBLE,"
        "ifWatched  BOOLEAN)");

    if (!query.exec()) {
        qDebug() << "Couldn't create the table 'Film': one might already exist.";
        success = false;
    }
    return success;
}

bool DbManager::addFilm(const QString& title, const int& year,
    const double& userRating, const bool& ifWatched)
{
    bool success = false;
    QSqlQuery query("SELECT id FROM Film");
    query.last();
    int lastId = query.value(0).toInt() + 1;

    QSqlQuery queryAddFilm;
    queryAddFilm.prepare(
        "INSERT INTO Film (id, title, year, imdbRating, userRating, ifWatched)"
        "VALUES (:id, :title, :year, :imdbRating, :userRating, :ifWatched)");

    queryAddFilm.bindValue(":id", lastId);
    queryAddFilm.bindValue(":title", title);
    queryAddFilm.bindValue(":year", year);
    queryAddFilm.bindValue(":imdbRating", 0);
    queryAddFilm.bindValue(":userRating", userRating);
    queryAddFilm.bindValue(":ifWatched", ifWatched);

    if (queryAddFilm.exec()) {
        success = true;
    } else {
        qDebug() << "add film failed: " << queryAddFilm.lastError();
    }

    return success;
}

QVector<DbManager::Film> DbManager::readAll()
{
    QSqlQuery query(
        "SELECT title, year, imdbRating, userRating, ifWatched FROM Film");

    QVector<DbManager::Film> films;

    while (query.next()) {
        QString title = query.value(0).toString();
        int year = query.value(1).toInt();
        double imdbRating = query.value(2).toDouble();
        double userRating = query.value(3).toDouble();
        bool ifWatched = query.value(4).toBool();

        DbManager::Film film;
        film.title = title;
        film.year = year;
        film.imdbRating = imdbRating;
        film.userRating = userRating;
        film.ifWatched = ifWatched;

        films.append(film);
    }
    return films;
}
