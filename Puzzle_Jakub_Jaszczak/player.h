#ifndef PLAYER_H
#define PLAYER_H

#include <tuple>
/*!
 * \brief The Player class contains data about player moves. Counts number of moves of a player and stores last performed move/
 */
class Player
{
public:
    Player();
    std::tuple<int, int> getLastMove();
    void move(int clickedIdx, int blackButtonIdx);
    int getMoveCount();
    void resetMoveCounter();
    void undoMove();

private:
    int moveCount = 0;
    std::tuple<int, int> lastMove;
    bool allowUndo = false;
};

#endif // PLAYER_H
