#include "omdbmanager.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrlQuery>

/* TODO: 1. Create request URL from multiple input parameters
 * (e.g. add t=titanic if someone gives just a title and y=1998 if someone gives a yaer) */
/* TODO: 2. Seperate sending a request from construction */
/* TODO: Parse the response using QScriptEngine */

OMDbManager::OMDbManager()
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished,
        this, &OMDbManager::replyFinished);
}

OMDbManager::~OMDbManager()
{
    delete m_networkManager;
}

void OMDbManager::fetchData(QString title, double year)
{
    QUrlQuery urlQuery("http://www.omdbapi.com/?");
    urlQuery.addQueryItem("apikey", "8aaa2cd7");
    urlQuery.addQueryItem("t", title);
    urlQuery.addQueryItem("y", QString::number(year));
    m_networkManager->get(QNetworkRequest(QUrl(urlQuery.toString())));
}

void OMDbManager::replyFinished(QNetworkReply* reply)
{
    QString data = static_cast<QString>(reply->readAll());

    qDebug() << data;
}
