#ifndef OMDBMANAGER_H
#define OMDBMANAGER_H

#include <QNetworkReply>
#include <QObject>
#include <QString>

class OMDbManager : public QObject {
    Q_OBJECT

public:
    OMDbManager();
    ~OMDbManager();

    struct Answear {
        QString title;
        QString year;
        QString imdbRating;
    };

    OMDbManager::Answear fetchData(QString title, double year = 0);

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_networkManager;
    bool m_isNotReady;
    QString m_title;
    QString m_year;
    QString m_imdbRating;
};

#endif // OMDBMANAGER_H
