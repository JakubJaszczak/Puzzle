#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QString filename, int _number_of_tiles) {
    QPixmap fullImage(filename);
    this->_image = fullImage;
    this->setButtonSize(_number_of_tiles);
}

QIcon ImageProcessor::getIcon(int _number_of_tiles)
{
    return this->createButtonIcon(_number_of_tiles);
}

QSize ImageProcessor::getButtonSize()
{
    return this->buttonSize;
}

void ImageProcessor::setButtonSize(int _number_of_tiles)
{
    this->buttonSize = QSize(floor(this->_image.width()/_number_of_tiles), floor(this->_image.height()/_number_of_tiles));
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

