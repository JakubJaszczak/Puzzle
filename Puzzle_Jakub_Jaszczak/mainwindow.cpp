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
    ui->comboBox->addItem(QString("Lena"));
    ui->comboBox->addItem(QString("Mario"));
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
    Board board;
    board.setboard(this->boardButtons);

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

            connect(this->boardButtons[row][col], &QPushButton::clicked, this, &MainWindow::handleButtonClick);
        }
    }

    QPushButton *blackButton = this->boardButtons[n-1][n-1];
    blackButton->setIcon(QIcon());
    QPalette pal = blackButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    blackButton->setAutoFillBackground(true);
    blackButton->setPalette(pal);
    blackButton->update();


    ui->board->setLayout(layout);
}

void MainWindow::delete_board_layout(){

    QLayout* layout = ui->board->layout();
    qDeleteAll(ui->board->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete layout;
}

void MainWindow::on_pB_restart_clicked()
{
    delete_board_layout();
}


void MainWindow::on_sB_numberOfCells_valueChanged(int arg1)
{
    // delete_board_layout();
    // createGridLayout(arg1);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->l_logger->setText(QString::number(index));
}


void MainWindow::handleButtonClick(){

    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QGridLayout *layout = qobject_cast<QGridLayout*>(ui->board->layout());
        int row, column, rowSpan, columnSpan;
        layout->getItemPosition(layout->indexOf(clickedButton), &column, &row, &rowSpan, &columnSpan);

        // DEBUG- REMOVE LATER !
        qDebug() << "Button clicked at row:" << row << "column:" << column << "idx: " << layout->indexOf(clickedButton);
    }
}

