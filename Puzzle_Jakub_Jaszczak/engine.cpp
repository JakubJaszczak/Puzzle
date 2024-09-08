#include "engine.h"
#include "gamemanager.h"
#include <qdebug.h>



Engine::Engine(int boardSize, GameManager *manager) {
    this->boardSize = boardSize;
    setInitialBoardState();
    this->manager = manager;
}

void Engine::addPlayer(Player *player)
{
    this->player = *player;
}

void Engine::processMove(int clickedIdx)
{
    if (!this->isMoveLegal(clickedIdx, getEmptyTilePosition(), boardSize)){
        return;
    };

    this->player.move(clickedIdx, getEmptyTilePosition());
    std::swap(this->currentBoardState[clickedIdx], this->currentBoardState[getEmptyTilePosition()]);
    if(this->checkWinCondition()){
        manager->setCurrentGameStatus(GameStatus::Gameover);
    };
}

void Engine::setInitialBoardState()
{
    for (int i=1; i < (pow(boardSize,2)); ++i){
        this->currentBoardState.push_back(i);
    }
    this->currentBoardState.push_back(-1);
}
void Engine::reinitializeBoard(int size)
{
    this->currentBoardState.clear();

    for (int i=1; i < (pow(size,2)); ++i){
        this->currentBoardState.push_back(i);
    }
    this->currentBoardState.push_back(-1);
    this->boardSize = size;
}

int Engine::getPlayerMoveCounter()
{
    return this->player.getMoveCount();
}

void Engine::resetPlayerMoveCounter()
{
    this->player.resetMoveCounter();
}

void Engine::undoMove()
{
    std::tuple<int, int> lastMove = this->player.getLastMove();
    std::swap(this->currentBoardState[std::get<0>(lastMove)], this->currentBoardState[std::get<1>(lastMove)]);
    this->player.undoMove();
}

Engine::~Engine()
{
    delete manager;
}


bool Engine::isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix){

    qDebug() << "Button clicked at idx: " << clickedIndex << "  Current Black Button idx:"<< currentEmptyTileIdx ;
    bool legalMoveFlag = true;
    if (clickedIndex == currentEmptyTileIdx){
        legalMoveFlag = false;
    };
    if (!(abs(clickedIndex - currentEmptyTileIdx) == numberbOfTilesPerAsix || (abs(clickedIndex - currentEmptyTileIdx) == 1))){
        legalMoveFlag = false;
    };
    if (abs(clickedIndex - currentEmptyTileIdx) == 1 && clickedIndex / numberbOfTilesPerAsix != currentEmptyTileIdx / numberbOfTilesPerAsix)
    {
        legalMoveFlag = false;
    }
    return legalMoveFlag;
}

bool Engine::checkWinCondition() {
    for (int x =1; x < this->currentBoardState.size(); ++x){
        if(currentBoardState[x] == -1){continue;};
        if(this->currentBoardState[x] - this->currentBoardState[x-1] != 1) {
            return false;
        };
    };
    return true;
}

int Engine::getEmptyTilePosition()
{
    for(int i=0; i<currentBoardState.size(); i++){
        if(currentBoardState[i] == -1){
            return i;
        };
    }

    throw std::logic_error("Board does not have an empty tile");
}

int Engine::getRowNumberFromBelow()
{
    int emptyTileIdx = getEmptyTilePosition();
    return boardSize - emptyTileIdx;
}

void Engine::makePuzzleSolvable()
{
    if(currentBoardState[0] != -1 && currentBoardState[1] != -1){
        std::swap(currentBoardState[0], currentBoardState[1]);
    }
    else{
        std::swap(currentBoardState[currentBoardState.size()-1], currentBoardState[currentBoardState.size()-2]);
    }

}

void Engine::shuffle(int n)
{ for (int i=0; i<n; i++)
    {   int blackButtonIdx = getEmptyTilePosition();
        QVector<int> possibleIndecies{blackButtonIdx+1, blackButtonIdx-1, blackButtonIdx+boardSize,blackButtonIdx-boardSize};
        for (int x =0; x < possibleIndecies.size(); x++){
            if (possibleIndecies[x] > pow(boardSize,2)-1 || possibleIndecies[x]<0){
                possibleIndecies.removeAt(x);
            }
        }
        int clickedIndex = possibleIndecies[rand() % possibleIndecies.size()] ;
        this->processMove(clickedIndex);
    }
}

void Engine::shuffle()
{   srand(time(NULL));
    for(int i=currentBoardState.size()-1; i>0; i--){
        int randomIndex = rand() % i;
        std::swap(this->currentBoardState[i], this->currentBoardState[randomIndex]);
    }

    if(!isSlidePuzzeSolvable()){
        makePuzzleSolvable();
    };
}

int Engine::getNumberInversions()
{
    int emptyTile = -1;
    int numberInversions = 0;

    for (int i=0; i< currentBoardState.size(); ++i){
        if(currentBoardState[i] == emptyTile){
            continue;
        }

        for (int j = i+1; j< currentBoardState.size(); j++){
            if(currentBoardState[j]!= emptyTile && currentBoardState[i] > currentBoardState[j])
            {
                numberInversions++;
            }
        }
    }
    return numberInversions;
}

std::vector<int> Engine::getGameState()
{
    return this->currentBoardState;
}

void Engine::setNewState(std::vector<int> state)
{
    this->currentBoardState = state;
    this->boardSize = sqrt(state.size());
}


bool Engine::isSlidePuzzeSolvable()
{   int numberInverions = getNumberInversions();
    if(boardSize % 2 == 0){
        return (numberInverions % 2 == 0);
    }
    int emptyTileRowNumber = getEmptyTilePosition();
    if (emptyTileRowNumber % 2 != 0){
        return (numberInverions % 2 == 0);
    }
    else {
        return (numberInverions % 2 != 0);}
}
