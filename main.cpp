#include "dbmanager.h"
#include "mainwindow.h"
#include "omdbmanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileDevice>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //DbManager db(path);
    //db.addFilm("Friends with Benefits", 2011, 5, 1);
    //auto films = db.readAll();

    //    DbManager::Film film;
    //    foreach (film, films)
    //        qDebug() << film.title;

    return a.exec();
}
