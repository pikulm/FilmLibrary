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
    void fetchData(QString title, double year = 0);

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_networkManager;
};

#endif // OMDBMANAGER_H
