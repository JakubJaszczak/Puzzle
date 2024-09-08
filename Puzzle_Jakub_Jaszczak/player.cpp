#include "player.h"

Player::Player() {}

std::tuple<int, int> Player::getLastMove()
{
    return this->lastMove;
}

void Player::move(int clickedIdx, int blackButtonIdx)
{
    moveCount++;
    this->lastMove = {clickedIdx, blackButtonIdx};
    this->allowUndo = true;
}

int Player::getMoveCount()
{
    return this->moveCount;
}

void Player::resetMoveCounter()
{
    this->moveCount = 0;
}

void Player::undoMove()
{   if(allowUndo){
        this->moveCount--;
        this->allowUndo = false;
    }
}








