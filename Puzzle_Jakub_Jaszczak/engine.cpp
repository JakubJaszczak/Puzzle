#include "engine.h"



Engine::Engine(int boardSize) {
    this->boardSize = boardSize;
    setInitialBoardState();
}

void Engine::addPlayer(Player *player)
{
    this->player = *player;
}

void Engine::processMove(Board *board, int clickedIdx)
{
    if (!this->isMoveLegal(clickedIdx, board->getCurrentBlackButtonIdx(), boardSize)){
        qDebug() << "Illegal move";
        return;
    };

    std::swap(this->currentBoardState[clickedIdx], this->currentBoardState[board->getCurrentBlackButtonIdx()]);
    this->player.move(board, clickedIdx);

    if(this->checkWinCondition()){
        qDebug() << "Game won";
    };
}

void Engine::setInitialBoardState()
{
    for (int i=1; i < (pow(boardSize,2)); ++i){
        this->currentBoardState.push_back(i);
    }
    this->currentBoardState.push_back(-1);
    qDebug() << "Initial state" << currentBoardState;
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
{   qDebug() <<"Before"<< isSlidePuzzeSolvable();
    if(currentBoardState[0] != -1 && currentBoardState[1] != -1){
        std::swap(currentBoardState[0], currentBoardState[1]);
    }
    else{
        std::swap(currentBoardState[currentBoardState.size()-1], currentBoardState[currentBoardState.size()-2]);
    }
    qDebug() <<"After"<< isSlidePuzzeSolvable();

}

void Engine::shuffle(Board *board, int n)
{ for (int i=0; i<n; i++)
    {   int blackButtonIdx = board->getCurrentBlackButtonIdx();
        QVector<int> possibleIndecies{blackButtonIdx+1, blackButtonIdx-1, blackButtonIdx+boardSize,blackButtonIdx-boardSize};
        for (int x =0; x < possibleIndecies.size(); x++){
            if (possibleIndecies[x] > pow(boardSize,2)-1 || possibleIndecies[x]<0){
                possibleIndecies.removeAt(x);
            }
        }
        int clickedIndex = possibleIndecies[rand() % possibleIndecies.size()] ;
        this->processMove(board,clickedIndex);
    }
}

void Engine::shuffle()
{   srand(time(NULL));
    for(int i=currentBoardState.size()-1; i>0; i--){
        int randomIndex = rand() % i;
        std::swap(this->currentBoardState[i], this->currentBoardState[randomIndex]);
    }
    qDebug() <<"After shuffle" << currentBoardState;

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
    qDebug() <<"Number of inversions:" << numberInversions;

    return numberInversions;
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
