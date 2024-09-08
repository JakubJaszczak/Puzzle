#include "engine.h"
#include "gamemanager.h"
#include <qdebug.h>


/*!
 * \brief Engine::Engine Engine class costructor. Sets initial values for boardSize and game manager.
 * \param boardSize Number of tiles in one axis on a board.
 * \param manager GameManager object
 */
Engine::Engine(int boardSize, GameManager *manager) {
    this->boardSize = boardSize;
    setInitialBoardState();
    this->manager = manager;
}
/*!
 * \brief Engine::addPlayer Sets a player. Game is single player, therefore there can be only one active player.
 * \param player Current Player
 */
void Engine::addPlayer(Player *player)
{
    this->player = *player;
}

/*!
 * \brief Engine::processMove Handles a move based on index of clicked button on the board.
 *  Performes move if its legal and checks win condition after performed move.
 * \param clickedIdx Index of a clicked board tile
 */
void Engine::processMove(int clickedIdx)
{
    if (!this->isMoveLegal(clickedIdx, getEmptyTilePosition(), boardSize)){
        return;
    };

    this->player.move(clickedIdx, getEmptyTilePosition());
    std::swap(this->currentBoardState[clickedIdx], this->currentBoardState[getEmptyTilePosition()]);
    if(manager->getCurrentGameStatus() == GameStatus::Setup){return;};
    if(this->checkWinCondition()){
        manager->setCurrentGameStatus(GameStatus::Gameover);
    };
}
/*!
 * \brief Engine::setInitialBoardState Sets initial board state, which is a arranged puzzle with a black tile on the bottom left.
 */
void Engine::setInitialBoardState()
{
    for (int i=1; i < (pow(boardSize,2)); ++i){
        this->currentBoardState.push_back(i);
    }
    this->currentBoardState.push_back(-1);
}

/*!
 * \brief Engine::reinitializeBoard Updates a new initial state for a board of different size.
 * \param size New size of a board
 */
void Engine::reinitializeBoard(int size)
{
    this->currentBoardState.clear();

    for (int i=1; i < (pow(size,2)); ++i){
        this->currentBoardState.push_back(i);
    }
    this->currentBoardState.push_back(-1);
    this->boardSize = size;
}

/*!
 * \brief Engine::getPlayerMoveCounter Gets a move counter of the active player
 * \return int Number of moves in current game
 */
int Engine::getPlayerMoveCounter()
{
    return this->player.getMoveCount();
}

/*!
 * \brief Engine::resetPlayerMoveCounter Player resets its move counter.
 */
void Engine::resetPlayerMoveCounter()
{
    this->player.resetMoveCounter();
}

/*!
 * \brief Engine::undoMove Reverts last performed move on the board
 */
void Engine::undoMove()
{
    std::tuple<int, int> lastMove = this->player.getLastMove();
    std::swap(this->currentBoardState[std::get<0>(lastMove)], this->currentBoardState[std::get<1>(lastMove)]);
    this->player.undoMove();
}
/*!
 * \brief Engine::~Engine class destructor. Frees memory.
 */
Engine::~Engine()
{
    delete manager;
}

/*!
 * \brief Engine::isMoveLegal Checks if a move is legal.
 * Checks following conditions:
 * - the clicked tile is not the empty tile
 * - the clicked tile is directly next to a empty tile
 * - the clicked tile is in the same row as empty tile, when clicked tile is on the left or right of the empty tile
 * \param clickedIndex Index of the clicked tile on the board
 * \param currentEmptyTileIdx Index of the empty tile
 * \param numberbOfTilesPerAsix Number of tiles on the board in one axis
 * \return True if the move is legal, otherwise false
 */
bool Engine::isMoveLegal(int clickedIndex, int currentEmptyTileIdx, int numberbOfTilesPerAsix){

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
/*!
 * \brief Engine::checkWinCondition Checks if tiles are properly arranged.
 * \return True if game condition has been met, otherwise false
 */
bool Engine::checkWinCondition() {
    for (int x =1; x < this->currentBoardState.size(); ++x){
        if(currentBoardState[x] == -1){continue;};
        if(this->currentBoardState[x] - this->currentBoardState[x-1] != 1) {
            return false;
        };
    };
    return true;
}

/*!
 * \brief Engine::getEmptyTilePosition Gets an index of the empty tile.
 * Raises std:: logic_error if there is no empty tile on the board
 * \return int Index of an empty tile.
 */
int Engine::getEmptyTilePosition()
{
    for(int i=0; i<currentBoardState.size(); i++){
        if(currentBoardState[i] == -1){
            return i;
        };
    }

    throw std::logic_error("Board does not have an empty tile");
}
/*!
 * \brief Engine::getRowNumberFromBelow Calculates row number of the empty tile counting from the bottom of the board.
 * \return int Row number counted from the bottom
 */
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
/*!
 * \brief Engine::shuffle Performes n random moves on the board
 * \param n Number of moves
 */
void Engine::shuffle(int n)
{   for (int i=0; i<n; i++)
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
/*!
 * \brief Engine::shuffle Fisher Yates array shuffling algorithm.
 * @see https://developerslogblog.wordpress.com/2020/04/01/how-to-shuffle-an-slide-puzzle/
 */
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

/*!
 * \brief Engine::getNumberInversions Calculates number of inversions in the current board to determin if the puzzle is solvable.
 * \return Number of inversions
 */
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

/*!
 * \brief Engine::getGameState Current game state getter.
 * \return currentBoardState
 */
std::vector<int> Engine::getGameState()
{
    return this->currentBoardState;
}

/*!
 * \brief Engine::setNewState currentBoardState setter
 * \param state New game state
 */
void Engine::setNewState(std::vector<int> state)
{
    this->currentBoardState = state;
    this->boardSize = sqrt(state.size());
}

/*!
 * \brief Engine::isSlidePuzzeSolvable Determins whether the puzzle is solvable.
 * \return True if game is solvable, otherwise false
 */
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
