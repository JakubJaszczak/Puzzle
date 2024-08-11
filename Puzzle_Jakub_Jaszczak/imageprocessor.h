#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qicon.h"
#include "qpixmap.h"
#include <QString>


class ImageProcessor
{
public:
    ImageProcessor(QString filename, int _numer_of_tiles);
    QIcon getIcon(int _number_of_tiles);
    QSize getButtonSize();


private:
    QPixmap _image;
    QSize buttonSize;
    void setButtonSize(int _number_of_tiles);
    QPixmap cropImage(int _number_of_tiles);
    QIcon createButtonIcon(int _number_of_tiles);
};

#endif // IMAGEPROCESSOR_H
