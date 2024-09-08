#include "player.h"

/*!
 * \brief Player::Player Player class constructor
 */
Player::Player() {}

/*!
 * \brief Player::getLastMove lastMove getter
 * \return tuple containing last performed move
 */
std::tuple<int, int> Player::getLastMove()
{
    return this->lastMove;
}

/*!
 * \brief Player::move Update player data after a legal move
 * \param clickedIdx Index of clicked button
 * \param blackButtonIdx Current index of empty tile
 */

void Player::move(int clickedIdx, int blackButtonIdx)
{
    moveCount++;
    this->lastMove = {clickedIdx, blackButtonIdx};
    this->allowUndo = true;
}

/*!
 * \brief Player::getMoveCount
 * \return number of moves in current game
 */
int Player::getMoveCount()
{
    return this->moveCount;
}

/*!
 * \brief Player::resetMoveCounter Reset player's move counter
 */
void Player::resetMoveCounter()
{
    this->moveCount = 0;
}

/*!
 * \brief Player::undoMove Revert last move data
 */
void Player::undoMove()
{   if(allowUndo){
        this->moveCount--;
        this->allowUndo = false;
    }
}








