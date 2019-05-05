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
}
