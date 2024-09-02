#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "player.h"

#include <Qstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem(QString("Mario"));
    ui->comboBox->addItem(QString("Lena"));
    this->currentImage = Images::Mario;
    createGridLayout(3);
}

void MainWindow::setManager(GameManager &manager)
{
    this->mManager = &manager;
}

MainWindow::~MainWindow()
{
    delete board;
    delete ui;
}

void MainWindow::on_pB_start_clicked()
{
    int sb_value = ui->sB_numberOfCells->value();
    delete_board_layout();
    createGridLayout(sb_value);
    ImageProcessor *imageProccessor = new ImageProcessor(this->currentImage, sb_value);
    Board *board = new Board(this->boardButtons, imageProccessor);
    Engine *gameEngine = new Engine(sb_value);
    Player *player = new Player();

    this->engine = gameEngine;
    this->engine->addPlayer(player);
    // this->engine->shuffle(board, 50 * sb_value);
    this->engine->shuffle();
    this->board = board;

    // Logging number of cells to be removed
    QString s = QString::number(sb_value);
    ui->l_logger->setText(s);
    ui->pB_start->setEnabled(false);
    ui->sB_numberOfCells->setEnabled(false);
    ui->comboBox->setEnabled(false);

}

void MainWindow::createGridLayout(int n)
{
    QSize buttonSize = QSize(ui->board->frameSize().width()/n,ui->board->frameSize().width()/n);
    ImageProcessor tempImageProccessor = ImageProcessor(this->currentImage, n);

    this->boardButtons.resize(n);

    QGridLayout *layout = new QGridLayout;
    for (int row = 0; row < n; ++row) {
        this->boardButtons[row].resize(n);
        for (int col = 0; col < n; ++col) {
            this->boardButtons[row][col] = new QPushButton();
            QIcon icon = tempImageProccessor.getIcon(row, col);
            this->boardButtons[row][col]->setFixedSize(buttonSize);
            this->boardButtons[row][col]->setIconSize(buttonSize);
            this->boardButtons[row][col]->setIcon(icon);
            layout->addWidget(this->boardButtons[row][col], row, col);
            connect(this->boardButtons[row][col], &QPushButton::clicked, this, &MainWindow::handleButtonClick);
        }
    }
    ui->board->setLayout(layout);
}

void MainWindow::delete_board_layout(){

    qDeleteAll(this->ui->board->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively));
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->board->layout());
    delete layout;
}

void MainWindow::on_pB_restart_clicked()
{
    delete_board_layout();
    ui->pB_start->setEnabled(true);
    ui->sB_numberOfCells->setEnabled(true);
    ui->comboBox->setEnabled(true);

}


void MainWindow::on_sB_numberOfCells_valueChanged(int arg1)
{
    delete_board_layout();
    createGridLayout(arg1);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0){this->currentImage = Images::Mario;};
    if (index == 1){this->currentImage = Images::Lena;};
    delete_board_layout();
    createGridLayout(ui->sB_numberOfCells->value());
}


void MainWindow::handleButtonClick(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QGridLayout *layout = qobject_cast<QGridLayout*>(ui->board->layout());
        int clickedIndex = layout->indexOf(clickedButton);
        engine->processMove(this->board, clickedIndex);
    }

}

