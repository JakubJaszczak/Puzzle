#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"


class Player
{
public:
    Player();
    void move(Board* board, int clickedIndex);

private:
    bool isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix);
    bool test(int a, int b, int c){return true;};
};

#endif // PLAYER_H
