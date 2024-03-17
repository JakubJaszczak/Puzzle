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

void MainWindow::on_pushButton_clicked()
{
    int sb_value = ui->sB_numberOfCells->value();
    this->mManager->setNumberOfCells(sb_value);
    QString s = QString::number(sb_value);
    ui->logger->setText(s);
}

