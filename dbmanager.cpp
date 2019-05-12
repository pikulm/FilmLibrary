#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::addFilm(const QString& title, const int &year, const double &userRating, const bool &ifWatched)
{
    bool success = false;
    QSqlQuery query("SELECT id FROM Film");
    query.last();
    int lastId = query.value(0).toInt() + 1;

    QSqlQuery queryAddFilm;
    queryAddFilm.prepare("INSERT INTO Film (id, title, year, imdbRating, userRating, ifWatched)"
                         "VALUES (:id, :title, :year, :imdbRating, :userRating, :ifWatched)");

    queryAddFilm.bindValue(":id", lastId);
    queryAddFilm.bindValue(":title", title);
    queryAddFilm.bindValue(":year", year);
    queryAddFilm.bindValue(":imdbRating", 0);
    queryAddFilm.bindValue(":userRating", userRating);
    queryAddFilm.bindValue(":ifWatched", ifWatched);


    if(queryAddFilm.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add film failed: " << queryAddFilm.lastError();
    }

    return success;
}

QVector<DbManager::Film> DbManager::readAll()
{
    QSqlQuery query("SELECT title, year, imdbRating, userRating, ifWatched FROM Film");

    QVector<DbManager::Film> films;

    while (query.next())
    {
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
