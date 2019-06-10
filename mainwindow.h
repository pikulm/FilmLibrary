#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include "omdbmanager.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    OMDbManager omdb;
    DbManager db;
    OMDbManager::Answear m_answ;

private slots:
    void doWhenSearchButtonPressed();
    void doWhenAddButtonPressed();
    void doWhenAddSelfButtonPressed();
};

#endif // MAINWINDOW_H
