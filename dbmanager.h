#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();

    struct Film
    {
        QString title;
        int year;
        double userRating;
        double imdbRating;
        bool ifWatched;
    };

    bool isOpen() const;
    bool addFilm(const QString& title, const int& year, const double& userRating, const bool& ifWatched);
    QVector<Film> readAll();
    bool createTable() const;

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
