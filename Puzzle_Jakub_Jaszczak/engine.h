#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"


class Engine
{
public:
    Engine();
    void addPlayer(Player *player);
    void processMove(Board *board, int clickedIdx);
    void setInitialBoardState(int number_of_tiles);
    void shuffle(Board *board, int n);


private:
    Player player; // One player game
    bool isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix);
    bool  checkWinCondition();
    std:: vector<int> currentBoardState;
};

#endif // ENGINE_H
