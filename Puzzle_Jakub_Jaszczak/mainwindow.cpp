#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "player.h"

#include <QFile>
#include <Qstring>
#include <Qstring>

/*!
 * \brief MainWindow::MainWindow MainWindow class constructor
 * Sets default values for ui and creates initial state of the game
 * \param parent Parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GameManager* manager = new GameManager();
    this->mManager = manager;


    ui->comboBox->addItem(QString("Mario"));
    ui->comboBox->addItem(QString("Tiger"));
    ui->shuffleCB->addItem(QString("FisherYates algorithm"));
    ui->shuffleCB->addItem(QString("Random move shuffle"));

    this->currentImage = Images::Mario;

    int defaultBoardSize = ui->sB_numberOfCells->value();
    delete_board_layout();
    createGridLayout(defaultBoardSize);
    ImageProcessor *imageProccessor = new ImageProcessor(this->currentImage, defaultBoardSize);
    Board *board = new Board(this->boardButtons, imageProccessor);
    Engine *gameEngine = new Engine(defaultBoardSize, mManager);
    Player *player = new Player();

    this->engine = gameEngine;
    board->setState(engine->getGameState());
    this->board = board;
    this->engine->addPlayer(player);
    ui->lineEdit->setText(mManager->getGameStatusMsg(mManager->getCurrentGameStatus()));

}


/*!
 * \brief MainWindow::~MainWindow MainWindow class destructor. Calls destructor of dynamically created members.
 */
MainWindow::~MainWindow()
{
    delete board;
    delete engine;
    delete mManager;
    delete ui;
}

/*!
 * \brief MainWindow::on_pB_start_clicked Slot activated on start button click. Sets starting state of the board and the engine. Sets game status to gameplay.
 */
void MainWindow::on_pB_start_clicked()
{
    int currentBoardSize = ui->sB_numberOfCells->value();
    this->engine->reinitializeBoard(currentBoardSize);

    (this->shuffleAlgorithm) ? this->engine->shuffle(50 * currentBoardSize) : this->engine->shuffle();

    this->board->setboard(this->boardButtons);
    this->board->setImageProcessor(new ImageProcessor(this->currentImage, currentBoardSize));
    this->board->setState(engine->getGameState());


    this->mManager->setCurrentGameStatus(GameStatus::Gameplay);


    ui->pB_start->setEnabled(false);
    ui->sB_numberOfCells->setEnabled(false);
    ui->comboBox->setEnabled(false);

    ui->lineEdit->setText(this->mManager->getGameStatusMsg(mManager->getCurrentGameStatus()));


}
/*!
 * \brief MainWindow::createGridLayout Creates a grid layout with buttons. Updates button data of boardButtons member.
 * \param n number of tiles in the grid per axis
 */
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
/*!
 * \brief MainWindow::delete_board_layout Deletes board layout with all its children
 */
void MainWindow::delete_board_layout(){

    qDeleteAll(this->ui->board->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively));
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->board->layout());
    delete layout;
}
/*!
 * \brief MainWindow::on_pB_restart_clicked Restarts the game by setting game status back to setup
 */
void MainWindow::on_pB_restart_clicked()
{
    delete_board_layout();
    createGridLayout(ui->sB_numberOfCells->value());

    this->mManager->setCurrentGameStatus(GameStatus::Setup);
    ui->lineEdit->setText(this->mManager->getGameStatusMsg(mManager->getCurrentGameStatus()));
}

/*!
 * \brief MainWindow::on_sB_numberOfCells_valueChanged Creates new grid of buttons with number of tiles equal to current passed value
 * \param arg1 current value of a spin box.
 */
void MainWindow::on_sB_numberOfCells_valueChanged(int arg1)
{
    delete_board_layout();
    createGridLayout(arg1);
}

/*!
 * \brief MainWindow::on_comboBox_currentIndexChanged Sets current image according to chosen index. Refreshes the board, so the new image is visible.
 * \param index Index of a chosen image
 */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0){this->currentImage = Images::Mario;};
    if (index == 1){this->currentImage = Images::Tiger;};
    delete_board_layout();
    createGridLayout(ui->sB_numberOfCells->value());
}

/*!
 * \brief MainWindow::handleButtonClick Slot responsible for handling click on any button on a board.
 *  Passes index of clicked button to the engine, which proccesses the move further. Updates game status and move counter on the ui.
 */
void MainWindow::handleButtonClick(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QGridLayout *layout = qobject_cast<QGridLayout*>(ui->board->layout());
        int clickedIndex = layout->indexOf(clickedButton);
        engine->processMove(clickedIndex);
        this->board->setState(this->engine->getGameState());
    }
    ui->lineEdit->setText(this->mManager->getGameStatusMsg(mManager->getCurrentGameStatus()));

    ui->moveCounter->setText(QString::number(engine->getPlayerMoveCounter()));
}
/*!
 * \brief MainWindow::on_savePB_clicked Saves current position of the board to a file
 */
void MainWindow::on_savePB_clicked()
{
    std::vector<int> gameState = this->engine->getGameState();
    QString filename = "./save.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for(const int x:gameState){
            stream << x << "\n";
        }
    }
    file.close();
}

/*!
 * \brief MainWindow::on_loadPB_clicked Loades last saved game position from a file.
 *  Update members with loaded game state.
 */
void MainWindow::on_loadPB_clicked()
{
    std::vector<int> loadedState;
    QString filename = "./save.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        while(!file.atEnd()){
            bool ok;
            QString line = file.readLine();
            int singleTileState = line.toInt(&ok);
            if(!ok) {qDebug()<< "failed to load a number" << line;};
            loadedState.push_back(singleTileState);
        }
    }
    file.close();

    int boardSize = sqrt(loadedState.size());
    ui->sB_numberOfCells->setValue(boardSize);
    delete_board_layout();
    createGridLayout(boardSize);
    this->board->setboard(this->boardButtons);
    this->board->setImageProcessor(new ImageProcessor(this->currentImage, boardSize));
    this->board->setState(loadedState);
    this->engine->setNewState(loadedState);

    this->mManager->setCurrentGameStatus(GameStatus::Gameplay);
    ui->lineEdit->setText(this->mManager->getGameStatusMsg(mManager->getCurrentGameStatus()));
}



/*!
 * \brief MainWindow::on_lineEdit_textChanged Enables and disables ui fields based on GameStatus
 * \param arg1 game status message
 */
void MainWindow::on_lineEdit_textChanged(const QString &arg1){
    if (arg1 == QString(mManager->getGameStatusMsg(GameStatus::Setup))){
        ui->pB_start->setEnabled(true);
        ui->sB_numberOfCells->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->moveCounter->setText(QString::number(0));
        this->engine->resetPlayerMoveCounter();
    }
    else if (arg1 == QString(mManager->getGameStatusMsg(GameStatus::Gameplay))){
        ui->pB_start->setEnabled(false);
        ui->sB_numberOfCells->setEnabled(false);
        ui->comboBox->setEnabled(false);
    }
    else if (arg1 == QString(mManager->getGameStatusMsg(GameStatus::Gameover))){
        ui->pB_start->setEnabled(true);
        ui->sB_numberOfCells->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->moveCounter->setText(QString::number(0));
        this->engine->resetPlayerMoveCounter();
        for(int i=0; i< engine->getGameState().size(); ++i){
                this->board->getButton(i)->setEnabled(false);
            }
        }
}
/*!
 * \brief MainWindow::on_undo_clicked Reverts last move
 */
void MainWindow::on_undo_clicked()
{
    this->engine->undoMove();
    this->board->setState(this->engine->getGameState());
    ui->moveCounter->setText(QString::number(engine->getPlayerMoveCounter()));
}

/*!
 * \brief MainWindow::on_shuffleCB_currentIndexChanged Sets current shuffling algorithm
 * \param index Index assosiates with shuffling algorithm:
 * 0- Fisher Yates algorithm
 * 1 - Random move algorithm
 */
void MainWindow::on_shuffleCB_currentIndexChanged(int index)
{
    shuffleAlgorithm = index;
}

