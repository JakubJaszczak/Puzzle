#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include <Qvector>
#include <Random>


class Engine
{
public:
    Engine(int boardSize);
    void addPlayer(Player *player);
    void processMove(Board *board, int clickedIdx);
    void setInitialBoardState();
    void shuffle(Board *board, int n);
    void shuffle();
    bool isSlidePuzzeSolvable();
    int getNumberInversions();


private:
    Player player; // One player game
    bool isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix);
    bool  checkWinCondition();
    std:: vector<int> currentBoardState;
    int boardSize;
    int getEmptyTilePosition();
    int getRowNumberFromBelow();
    void makePuzzleSolvable();
};

#endif // ENGINE_H
