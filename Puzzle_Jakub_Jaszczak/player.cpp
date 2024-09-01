#include "player.h"

Player::Player() {}



bool Player::gameWon()
{   std:: list<std :: list <int>> iconIndecies;

    return true;
}

void Player::move(Board* board, int clickedIndex)
{
    QIcon clickedIcon = board->getButton(clickedIndex)->icon();
    board->setBlackButton(clickedIndex);
    board->getButton(board->getCurrentBlackButtonIdx())->setIcon(clickedIcon);
    board->setCurrentBlackButtonIdx(clickedIndex);
    this->moveCount++;
}




