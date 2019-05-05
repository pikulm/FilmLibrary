#include "mainwindow.h"
#include "dbmanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

static const QString path = "databaseFilmLibrary.db";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DbManager db(path);

    return a.exec();
}
