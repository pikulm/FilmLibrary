#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();
    bool isOpen() const;
    bool addFilm(const QString& title, const int& year, const double& userRating, const bool& ifWatched);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
