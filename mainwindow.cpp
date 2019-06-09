#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->searchButton->setStyleSheet("QPushButton {color: #df0ac9}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::doWhenSearchButtonPressed ask the OMDb API for details
 * about a film specified by a title and, opionally, year of release.
 *
 * Read the title from the "titleEdit" button and, optionally, the year of
 * release from the "yearEdit" button. Then, connect with the OMDb API and
 * fetch the data.
 *
 * @param checked true if the button is checked, or false if the button is unchecked
 */
void MainWindow::doWhenSearchButtonPressed()
{
    QString title = ui->titleEdit->text();
    ui->resultText->setText(title);
}
