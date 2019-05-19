#include "omdbmanager.h"
#include <QDebug>
#include <QNetworkAccessManager>

OMDbManager::OMDbManager()
{
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);

    connect(networkManager, &QNetworkAccessManager::finished,
        this, &OMDbManager::replyFinished);

    networkManager->get(QNetworkRequest(QUrl("http://www.omdbapi.com/?t=titanic&apikey=8aaa2cd7")));
}

void OMDbManager::replyFinished(QNetworkReply* reply)
{
    QString data = static_cast<QString>(reply->readAll());

    qDebug() << data;
}
