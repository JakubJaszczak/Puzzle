#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qicon.h"
#include "qpixmap.h"
#include <QString>


class ImageProcessor
{
public:
    ImageProcessor(QString filename);
    QIcon createButtonIcon(QPixmap &_image);
private:
    QPixmap _image;
    QPixmap cropImage(int x,int y, int width, int height);
};

#endif // IMAGEPROCESSOR_H
