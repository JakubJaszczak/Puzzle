#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessor.h"

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
{  /* ImageProcessor imageProccessor = ImageProcessor("./../resources/Mario.png", n);
    QGridLayout *layout = new QGridLayout(ui->board_frame);
    for (int row=0; row < n; row++)
    {
        for (int col=0; col < n; col++)
        {   QPushButton *button = new QPushButton;
            QIcon buttonIcon = imageProccessor.getIcon(n);
            button->setFixedSize(imageProccessor.getButtonSize());
            button->setIcon(buttonIcon);
            button->setIconSize(imageProccessor.getButtonSize());
            layout->addWidget(button, row, col, Qt::AlignCenter);
        };
    };
    ui->board_frame->setLayout(layout);*/

    ImageProcessor imageProccessor = ImageProcessor(Images::Lena, n);
    QSize buttonSize = imageProccessor.getButtonSize();

    QGridLayout *layout = new QGridLayout;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            QPushButton *button = new QPushButton();
            QIcon buttonIcon = imageProccessor.getIcon(row, col);
            button->setIcon(buttonIcon);
            button->setFixedSize(buttonSize);
            button->setIconSize(buttonSize);
            layout->addWidget(button, row, col);
        }
    }
    ui->board->setLayout(layout);
}


void MainWindow::on_pB_restart_clicked()
{
    int x=0;
}

