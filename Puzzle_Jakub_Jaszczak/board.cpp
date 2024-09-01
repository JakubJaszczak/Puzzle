#include "board.h"

Board::Board(std::vector<std::vector<QPushButton*>> buttonsArr, ImageProcessor *imageProcessor)
{   this->imageProcessor = imageProcessor;
    this->board = buttonsArr;
    this->number_of_tiles = this->board.size();
    this->currentBlackButtonIdx = pow(this->number_of_tiles, 2) -1;
    this->setBlackButton(this->currentBlackButtonIdx);
    this->buttonSize = this->board[0][0]->size();
}


QPushButton *Board::getButton(int idx)
{
    int col = idx % this->number_of_tiles;
    int row = idx / this->number_of_tiles;

    return this->board[row][col];
}

QPushButton *Board::getButton(int row, int col)
{
    return this->board[col][row];
}

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

int Board::getCurrentBlackButtonIdx()
{
    return this->currentBlackButtonIdx;
}

int Board::getNumberOfTiles()
{
    return this->board.size();
}

ImageProcessor Board::getImageProcessor()
{
    return *this->imageProcessor;
}

void Board::setCurrentBlackButtonIdx(int idx)
{
    this->currentBlackButtonIdx = idx;
}

Board::~Board()
{

}
