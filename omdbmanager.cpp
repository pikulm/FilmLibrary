#include "omdbmanager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QTest>
#include <QUrlQuery>

/* TODO: 1. Create request URL from multiple input parameters
 * (e.g. add t=titanic if someone gives just a title and y=1998 if someone gives a yaer) */
/* TODO: 2. Seperate sending a request from construction */
/* TODO: Parse the response using QScriptEngine */

OMDbManager::OMDbManager()
    : m_isNotReady(true)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished,
        this, &OMDbManager::replyFinished);
}

OMDbManager::~OMDbManager()
{
    delete m_networkManager;
}

/**
 * @brief OMDbManager::fetchData fetches data from OMDb API about a movie specified.
 *
 * It returns a structure including information such as: title, year of release and
 * imdb rating.
 *
 * @param title a title of a movie to fetch information for
 * @param year (optional) a year of a release of a movie to fetch information for
 */
OMDbManager::Answear OMDbManager::fetchData(QString title, double year)
{
    QUrlQuery urlQuery("http://www.omdbapi.com/?");
    urlQuery.addQueryItem("apikey", "8aaa2cd7");
    urlQuery.addQueryItem("t", title);
    if (year != 0) {
        urlQuery.addQueryItem("y", QString::number(year));
    }
    m_networkManager->get(QNetworkRequest(QUrl(urlQuery.toString())));

    /* TODO: 3. wait for getting an answear */
    /* get & process data */
    while (m_isNotReady) {
        QTest::qWait(100);
    }

    OMDbManager::Answear answear;
    answear.title = m_title;
    answear.year = m_year;
    answear.imdbRating = m_imdbRating;

    qDebug() << answear.title;
    qDebug() << answear.year;
    qDebug() << answear.imdbRating;

    return answear;
}

void OMDbManager::replyFinished(QNetworkReply* reply)
{
    auto replyJson = QJsonDocument::fromJson(reply->readAll());
    auto isJsonNull = replyJson.isNull();

    qDebug() << "JSON from the reply:" << replyJson;
    qDebug() << "Was JSON improperly parsed:" << isJsonNull;
    qDebug() << "The title of the movie is:" << replyJson["Title"].toString();
    qDebug() << "The imdb rating of the movie is:" << replyJson["imdbRating"].toString();
    qDebug() << "The value of internet movie database rating of the movie is:" << replyJson["Ratings"][0]["Value"].toString();

    m_title = replyJson["Title"].toString();
    m_year = replyJson["Year"].toString();
    m_imdbRating = replyJson["imdbRating"].toString();
    m_isNotReady = isJsonNull;
}
