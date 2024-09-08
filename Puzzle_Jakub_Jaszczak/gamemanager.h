#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <map>

enum class GameStatus {
    Setup,
    Gameplay,
    Gameover,
};

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
