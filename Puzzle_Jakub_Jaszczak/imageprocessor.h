#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qicon.h"
#include "qpixmap.h"
#include <QString>


class ImageProcessor
{
public:
    ImageProcessor(QString filename);
private:
    QPixmap _image;
    QPixmap cropImage(int _number_of_tiles);
    QIcon createButtonIcon(int _number_of_tiles);
};

#endif // IMAGEPROCESSOR_H
