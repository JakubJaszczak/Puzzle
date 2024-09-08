#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <map>
/*!
 * \brief The GameStatus enum defines possible game statuses.
 */
enum class GameStatus {
    Setup,
    Gameplay,
    Gameover,
};

/*!
 * \brief The GameManager class stores data about current game status and messages for each game state.
 */
class GameManager
{
public:
    GameManager();


    const char* getGameStatusMsg(GameStatus status);
    void setCurrentGameStatus(GameStatus status);
    GameStatus getCurrentGameStatus();

private:
    GameStatus currentGameStatus;
    std::map<GameStatus, const char*> gameMsg;
};

#endif // GAMEMANAGER_H
