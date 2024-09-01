#include "gamemanager.h"

GameManager::GameManager() {

}

void GameManager::setNumberOfCells(int _n)
{
    this->numberOfCells = _n;
}

int GameManager::getNumberOfCells() const
{
    return numberOfCells;
}
