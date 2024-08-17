#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"
#include "imageprocessor.h"

#include <Qstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->createGridLayout(ui->sB_numberOfCells->value());
}

void MainWindow::setManager(GameManager &manager)
{
    this->mManager = &manager;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pB_start_clicked()
{
    int sb_value = ui->sB_numberOfCells->value();
    this->mManager->setNumberOfCells(sb_value);
    this->createGridLayout(sb_value);

    // Logging number of cells to be removed
    QString s = QString::number(sb_value);
    ui->l_logger->setText(s);
}

void MainWindow::createGridLayout(int n)
{
    ImageProcessor imageProccessor = ImageProcessor(Images::Mario, n);
    QSize buttonSize = QSize(ui->board->frameSize().width()/n,ui->board->frameSize().width()/n);
    // Board board(n, buttonSize);
    this->boardButtons.resize(n, std::vector<QPushButton*>(n, nullptr));
    QGridLayout *layout = new QGridLayout;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            this->boardButtons[row][col] = new QPushButton();
            QIcon icon = imageProccessor.getIcon(row, col);
            this->boardButtons[row][col]->setFixedSize(buttonSize);
            this->boardButtons[row][col]->setIconSize(buttonSize);
            this->boardButtons[row][col]->setIcon(icon);
            layout->addWidget(this->boardButtons[row][col], row, col);
        }
    }
    ui->board->setLayout(layout);
}

void MainWindow::delete_board_layout(){

    for (std::size_t i = 0; i < this->boardButtons.size(); ++i) {
        for (std::size_t j = 0; j < this->boardButtons[i].size(); ++j) {
            delete this->boardButtons[i][j];
        }
    }
    // qDeleteAll(ui->board->findChildren<QPushButton *>(Qt::FindDirectChildrenOnly));

    if (ui->board->layout() != nullptr){
        delete ui->board->layout();
    }
}

void MainWindow::on_pB_restart_clicked()
{
    int x=0;
}


void MainWindow::on_sB_numberOfCells_valueChanged(int arg1)
{
    // delete_board_layout();
    // createGridLayout(arg1);
}

