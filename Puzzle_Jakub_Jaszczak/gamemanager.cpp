#include "gamemanager.h"

/*!
 * \brief GameManager::GameManager GameManager class constructor. Maps a game status on messages.
 * Sets initial gameStatus to setup.
 */

GameManager::GameManager() {
    this->gameMsg = {
        {GameStatus::Setup, "Setting up"},
        {GameStatus::Gameplay, "The game is on"},
        {GameStatus::Gameover, "You won, Congratulations!"},
    };
    this->currentGameStatus = GameStatus::Setup;
}
/*!
 * \brief GameManager::getGameStatusMsg Gets a requested game message according to a status
 * \param status GameStatus
 * \return Requested message
 */
const char* GameManager::getGameStatusMsg(GameStatus status)
{
    return this->gameMsg[status];
}
/*!
 * \brief GameManager::setCurrentGameStatus currentGameStatus setter
 * \param status GameStatus
 */
void GameManager::setCurrentGameStatus(GameStatus status)
{
    this->currentGameStatus = status;
}
/*!
 * \brief GameManager::getCurrentGameStatus currentGameStatus getter
 * \return currentGameStatus
 */
GameStatus GameManager::getCurrentGameStatus()
{
    return this->currentGameStatus;
}
