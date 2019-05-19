#ifndef OMDBMANAGER_H
#define OMDBMANAGER_H

#include <QNetworkReply>
#include <QObject>

class OMDbManager : public QObject {
    Q_OBJECT

public:
    OMDbManager();

public slots:
    void replyFinished(QNetworkReply* reply);
};

#endif // OMDBMANAGER_H
