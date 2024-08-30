#include "player.h"

Player::Player() {}

bool Player::isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix){
    //
    qDebug() << "Button clicked at idx: " << clickedIndex << "  Current Black Button idx:"<< currentEmptyTileIdx ;
    bool legalMoveFlag = true;
    if (clickedIndex == currentEmptyTileIdx){
        qDebug() << "clicked black button";
        legalMoveFlag = false;
    };
    if (!(abs(clickedIndex - currentEmptyTileIdx) == numberbOfTilesPerAsix || (abs(clickedIndex - currentEmptyTileIdx) == 1))){
        qDebug() << "Buttons not in the same column or row";
        legalMoveFlag = false;
    };
    // if (!(abs(clickedIndex - currentEmptyTileIdx) == 1)){
    //     qDebug() << "Buttons not in the same row";
    //     legalMoveFlag = false;
    // };
    return legalMoveFlag;
}

void Player::move(Board* board, int clickedIndex)
{
    if (this->isMoveLegal(clickedIndex, board->getCurrentBlackButtonIdx(), board->getNumberOfTiles())){
        QIcon clickedIcon = board->getButton(clickedIndex)->icon();
        board->setBlackButton(clickedIndex);
        board->getButton(board->getCurrentBlackButtonIdx())->setIcon(clickedIcon);
        board->setCurrentBlackButtonIdx(clickedIndex);
    };
}


