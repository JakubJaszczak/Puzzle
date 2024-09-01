#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"


class Player
{
public:
    Player();
    void move(Board* board, int clickedIndex);

private:
    bool gameWon();
    int moveCount = 0;
};

#endif // PLAYER_H
