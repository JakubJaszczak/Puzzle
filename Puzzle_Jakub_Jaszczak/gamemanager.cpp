#include "gamemanager.h"

GameManager::GameManager() {
    this->gameMsg = {
        {GameStatus::Setup, "Setting up"},
        {GameStatus::Gameplay, "The game is on"},
        {GameStatus::Gameover, "You won, Congratulations!"},
    };
    this->currentGameStatus = GameStatus::Setup;
}

const char* GameManager::getGameStatusMsg(GameStatus status)
{
    return this->gameMsg[status];
}

void GameManager::setCurrentGameStatus(GameStatus status)
{
    this->currentGameStatus = status;
}

GameStatus GameManager::getCurrentGameStatus()
{
    return this->currentGameStatus;
}
