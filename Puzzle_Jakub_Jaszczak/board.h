#ifndef BOARD_H
#define BOARD_H


#include <qpushbutton.h>
class Board
{
public:
    Board();
    std::vector<std::vector<QPushButton*>> getBoard();
    void setboard(std::vector<std::vector<QPushButton*>> baord);
    ~Board();

private:
    std::vector<std::vector<QPushButton*>> board;
};

#endif // BOARD_H
