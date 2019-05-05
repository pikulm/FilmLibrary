#include "mainwindow.h"
#include "dbmanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

static const QString path = "/Users/magdalenapikul/Documents/Studia/4 semestr/"
                            "Programowanie Obiektowe/Projekt/FilmLibrary/databaseFilmLibrary.db";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DbManager db(path);
    db.addFilm("Friends with Benefits", 2011, 5, 1);

return a.exec();
}
