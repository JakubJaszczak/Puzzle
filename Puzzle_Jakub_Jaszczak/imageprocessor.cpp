#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QString filename) {
    QPixmap fullImage(filename);
    this->_image = fullImage;
}

QIcon ImageProcessor::createButtonIcon(int _number_of_tiles)
{
    QIcon icon(cropImage(_number_of_tiles));
    return icon;
}

QPixmap ImageProcessor::cropImage(int _number_of_tiles)
{
    int width = this->_image.width()/_number_of_tiles;
    int height = this->_image.height()/_number_of_tiles;
    QRect cropRect = QRect(_number_of_tiles * width, _number_of_tiles * height, width, height);
    return this->_image.copy(cropRect);
}

