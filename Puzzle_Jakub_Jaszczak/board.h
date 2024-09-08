#ifndef BOARD_H
#define BOARD_H


#include "imageprocessor.h"

#include <qpushbutton.h>
class Board  : public QObject
{
    Q_OBJECT

public:
    Board(std::vector<std::vector<QPushButton*>> buttonsArr, ImageProcessor *imageProcessor);

    QPushButton* getButton(int idx);
    QPushButton* getButton(int row, int col);
    int getNumberOfTiles();
    ImageProcessor getImageProcessor();

    void setboard(std::vector<std::vector<QPushButton*>> newBoard);
    void setBlackButton(int idx);
    void setBlackButton(int row, int col);
    void setState(std::vector<int> boardState);
    void setImageProcessor(ImageProcessor *newImgProc);

    ~Board();

private:
    std::vector<std::vector<QPushButton*>> board;
    QSize buttonSize;
    int number_of_tiles;
    // int currentBlackButtonIdx;
    ImageProcessor *imageProcessor;

};

#endif // BOARD_H
