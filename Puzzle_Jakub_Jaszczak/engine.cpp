#include "engine.h"

#include <Qvector>

Engine::Engine() {}

void Engine::addPlayer(Player *player)
{
    this->player = *player;
}

void Engine::processMove(Board *board, int clickedIdx)
{
    if (!this->isMoveLegal(clickedIdx, board->getCurrentBlackButtonIdx(), board->getNumberOfTiles())){
        qDebug() << "Illegal move";
        return;
    };

    std::swap(this->currentBoardState[clickedIdx], this->currentBoardState[board->getCurrentBlackButtonIdx()]);
    this->player.move(board, clickedIdx);

    if(this->checkWinCondition()){
        qDebug() << "Game won";
    };
}

void Engine::setInitialBoardState(int number_of_tiles)
{
    for (int i=0; i < (pow(number_of_tiles,2)); ++i){
        this->currentBoardState.push_back(i);
    }
}

bool Engine::isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix){

    qDebug() << "Button clicked at idx: " << clickedIndex << "  Current Black Button idx:"<< currentEmptyTileIdx ;
    bool legalMoveFlag = true;
    if (clickedIndex == currentEmptyTileIdx){
        qDebug() << "clicked black button";
        legalMoveFlag = false;
    };
    if (!(abs(clickedIndex - currentEmptyTileIdx) == numberbOfTilesPerAsix || (abs(clickedIndex - currentEmptyTileIdx) == 1))){
        qDebug() << "Buttons not in the same column or row";
        legalMoveFlag = false;
    };
    // Check button on the edge
    if (abs(clickedIndex - currentEmptyTileIdx) == 1 && clickedIndex / numberbOfTilesPerAsix != currentEmptyTileIdx / numberbOfTilesPerAsix)
    {
        qDebug() << "Black tile on the edge. Clicked tile in the next row";
        legalMoveFlag = false;
    }
    return legalMoveFlag;
}

bool Engine::checkWinCondition() {
    for (int x =1; x < this->currentBoardState.size(); ++x){
        if(this->currentBoardState[x] - this->currentBoardState[x-1] != 1) {
            return false;
        };
    };
    return true;
}

void Engine::shuffle(Board *board, int n)
{ for (int i=0; i<n; i++)
    {   int blackButtonIdx = board->getCurrentBlackButtonIdx();
        int numberOfTiles = board->getNumberOfTiles();
        QVector<int> possibleIndecies{blackButtonIdx+1, blackButtonIdx-1, blackButtonIdx+numberOfTiles,blackButtonIdx-numberOfTiles};
        for (int x =0; x < possibleIndecies.size(); x++){
            if (possibleIndecies[x] > pow(numberOfTiles,2)-1 || possibleIndecies[x]<0){
                possibleIndecies.removeAt(x);
            }
        }
        int clickedIndex = possibleIndecies[rand() % possibleIndecies.size()] ;
        this->processMove(board,clickedIndex);
    }
}


