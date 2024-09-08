#ifndef ENGINE_H
#define ENGINE_H

#include "gamemanager.h"
#include "player.h"
#include <Qvector>
#include <Random>


class Engine
{
public:
    Engine(int boardSize, GameManager *manager);
    void addPlayer(Player *player);
    void processMove(int clickedIdx);
    void setInitialBoardState();
    void shuffle(int n);
    void shuffle();
    bool isSlidePuzzeSolvable();
    int getNumberInversions();
    std::vector<int> getGameState();
    void setNewState(std::vector<int> state);
    void reinitializeBoard(int size);
    int getPlayerMoveCounter();
    void resetPlayerMoveCounter();
    void undoMove();

    ~Engine();
private:
    Player player; // One player game
    bool isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix);
    bool  checkWinCondition();
    std:: vector<int> currentBoardState;
    int boardSize;
    int getEmptyTilePosition();
    int getRowNumberFromBelow();
    void makePuzzleSolvable();
    GameManager *manager;
};

#endif // ENGINE_H
