#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QPixmap>
#include <QStackedWidget>
#include <QTableWidget>

static const QString path = "database.db";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , omdb()
    , db(path)
{
    ui->setupUi(this);
    ui->searchButton->setStyleSheet("QPushButton {color: #df0ac9}");
    ui->addButton->setStyleSheet("QPushButton {color: #df0ac9}");
    ui->addSelfButton->setStyleSheet("QPushButton {color: #df0ac9}");

    ui->comboBox->addItem("Add film from OMDb");
    ui->comboBox->addItem("Add own film");
    ui->comboBox->addItem("View all");

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated),
        ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    //TODO: fill the table with films //

    auto filmVector = db.readAll();

    DbManager::Film film;
    foreach (film, filmVector)
        qDebug() << film.title;

    auto vectorLenght = filmVector.size();
    qDebug() << vectorLenght;

    ui->tableWidget->setRowCount(vectorLenght);

    int rowId = 0;
    foreach (film, filmVector) {
        ui->tableWidget->setItem(rowId, ID, new QTableWidgetItem(QString::number(rowId + 1)));
        ui->tableWidget->setItem(rowId, TITLE, new QTableWidgetItem(film.title));
        ui->tableWidget->setItem(rowId, YEAR, new QTableWidgetItem(QString::number(film.year)));
        ui->tableWidget->setItem(rowId, IMDBRATING, new QTableWidgetItem(QString::number(film.imdbRating)));
        ui->tableWidget->setItem(rowId, USERRATING, new QTableWidgetItem(QString::number(film.userRating)));
        ui->tableWidget->setItem(rowId, IFWATCHED, new QTableWidgetItem(QString::number(film.ifWatched)));

        rowId += 1;
    }
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
    double year = ui->yearEdit->text().toDouble();

    this->m_answ = omdb.fetchData(title, year);

    this->ui->resultText->setText("title: " + m_answ.title + "\n" + "year: " + m_answ.year + "\n" + "imdb rating: " + m_answ.imdbRating);

    /* TODO: check what omdb returns */
}
/**
 * @brief MainWindow::doWhenAddButtonPressed adds searched film to the database
 *
 * Reads the title, year and imdbRating from search result. Optionally adds user rating and option ifWatched to query
 */
void MainWindow::doWhenAddButtonPressed()
{
    QString title = m_answ.title;
    int year = m_answ.year.toInt();
    double userRating = ui->ratingBox->value();
    bool ifWatched = ui->ifYesBox->isChecked();

    bool isSuccessfullyAdded = this->db.addFilm(title, year, userRating, ifWatched);

    if (isSuccessfullyAdded) {
        this->ui->statusBar->showMessage("Film successfully added", 3000);
    } else {
        this->ui->statusBar->showMessage("Film not added", 3000);
    }

    //TODO: reading imdbRating from search result & adding it to db.addFilm function
}

void MainWindow::doWhenAddSelfButtonPressed()
{
    QString title = ui->selfTitleEdit->text();
    int year = ui->selfYearEdit->text().toInt();
    double userRating = ui->selfRatingBox->value();
    bool ifWatched = ui->selfYesBox->isChecked();

    bool isSuccessfullyAdded = this->db.addFilm(title, year, userRating, ifWatched);

    if (isSuccessfullyAdded) {
        this->ui->statusBar->showMessage("Film successfully added", 3000);
    } else {
        this->ui->statusBar->showMessage("Film not added", 3000);
    }
}
