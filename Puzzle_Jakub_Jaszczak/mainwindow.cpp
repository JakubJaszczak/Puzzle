#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <Qstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setManager(GameManager &manager)
{
    this->mManager = &manager;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_pushButton_clicked()
{
    int sb_value = ui->sB_numberOfCells->value();
    this->mManager->setNumberOfCells(sb_value);

    // Logging number of cells to be removed
    QString s = QString::number(sb_value);
    ui->l_logger->setText(s);
}

void MainWindow::createGridLayout()
{
    QGridLayout *layout = new QGridLayout;

}

