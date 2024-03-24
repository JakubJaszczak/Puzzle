#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QString filename) {
    QPixmap fullImage(filename);
    this->_image = fullImage;
}

QIcon ImageProcessor::createButtonIcon(QPixmap &_image)
{   QIcon icon(_image);
    return icon;
}

QPixmap ImageProcessor::cropImage(int _x,int _y, int _width, int _height)
{
    QRect cropRect(_x, _y, _width, _height);
    return this->_image.copy(cropRect);
}

