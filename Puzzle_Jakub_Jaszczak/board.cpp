#include "board.h"
/*!
 * \brief Board::Board Board class constuctor. Sets initial state of board, buttonSize and number of tiles.
 * \param buttonsArr Starting board
 * \param imageProcessor imageProcessor heleper class
 */
Board::Board(std::vector<std::vector<QPushButton*>> buttonsArr, ImageProcessor *imageProcessor)
{   this->imageProcessor = imageProcessor;
    this->board = buttonsArr;
    this->number_of_tiles = this->board.size();
    this->buttonSize = this->board[0][0]->size();
}

/*!
 * \brief Board::getButton Gets a button with given idx from board array
 * \param idx Idx of requested button
 * \return
 */
QPushButton *Board::getButton(int idx)
{
    int col = idx % this->number_of_tiles;
    int row = idx / this->number_of_tiles;

    return this->board[row][col];
}

/*!
 * \brief Board::getButton Gets a button with given row and column from board array
 * \param row Row coordinate of a requested button
 * \param col Column coordinate of a requested button
 * \return
 */
QPushButton *Board::getButton(int row, int col)
{
    return this->board[col][row];
}


/*!
 * \brief Board::setBlackButton Disables icon of a button and sets its background to black. Black button represents empty tile on the board
 * \param idx Index of a button
 */
void Board::setBlackButton(int idx)
{
    QPushButton *blackButton = this->getButton(idx);
    blackButton->setIcon(QIcon());
    QPalette pal = blackButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    blackButton->setAutoFillBackground(true);
    blackButton->setPalette(pal);
    blackButton->update();
}
/*!
 * \brief Board::setBlackButton Disables icon of a button and sets its background to black. Black button represents empty tile on the board
 * \param row Row coordinate of a button
 * \param col Column coordinate of a button
 */
void Board::setBlackButton(int row, int col)
{
    QPushButton *blackButton = this->getButton(row,col);
    blackButton->setIcon(QIcon());
    QPalette pal = blackButton->palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    blackButton->setAutoFillBackground(true);
    blackButton->setPalette(pal);
    blackButton->update();
}

/*!
 * \brief Board::setState Sets icons of board buttons according to a vector of icon indecies.
 * \param boardState Vector of icon indiecies for consecuitive buttons
 */
void Board::setState(std::vector<int> boardState)
{
    for(int i=0; i<boardState.size(); i++){
        if(boardState[i] == -1){
            this->setBlackButton(i);
            continue;
        }
        this->getButton(i)->setIcon(imageProcessor->getIcon(boardState[i]-1));
    }
}

/*!
 * \brief Board::setImageProcessor Updates image processor member. Update is required when board changes size.
 * \param newImgProc new image precessor.
 */

void Board::setImageProcessor(ImageProcessor *newImgProc)
{
    this->imageProcessor = newImgProc;
}

/*!
 * \brief Board::getNumberOfTiles Board size getter
 * \return Number of tiles on the board in one axis.
 */
int Board::getNumberOfTiles()
{
    return this->board.size();
}
/*!
 * \brief Board::getImageProcessor Image processor getter
 * \return current image processor
 */
ImageProcessor Board::getImageProcessor()
{
    return *this->imageProcessor;
}
/*!
 * \brief Board::setboard Updates board buttons with new board buttons
 * \param newBoard 2D array of buttons
 */
void Board::setboard(std::vector<std::vector<QPushButton *> > newBoard)
{
    this->board = newBoard;
    this->number_of_tiles = newBoard.size();
}

/*!
 * \brief Board::~Board Board class destructor
 */
Board::~Board()
{
    delete imageProcessor;
}
