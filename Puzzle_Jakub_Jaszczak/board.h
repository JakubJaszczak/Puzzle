#ifndef BOARD_H
#define BOARD_H


#include <qpushbutton.h>
class Board  : public QObject
{
    Q_OBJECT

public:
    Board(std::vector<std::vector<QPushButton*>> buttonsArr);

    std::vector<std::vector<QPushButton*>> getBoard();
    QPushButton* getButton(int idx);
    QPushButton* getButton(int row, int col);
    int getCurrentBlackButtonIdx();
    int getNumberOfTiles();

    void setboard(std::vector<std::vector<QPushButton*>> baord);
    void setBlackButton(int idx);
    void setCurrentBlackButtonIdx(int idx);
    void setBlackButton(int row, int col);

    ~Board();

private:
    std::vector<std::vector<QPushButton*>> board;
    QSize buttonSize;
    int number_of_tiles;
    int currentBlackButtonIdx;

};

#endif // BOARD_H
