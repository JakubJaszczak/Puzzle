#include "imageprocessor.h"

ImageProcessor::ImageProcessor(Images image, int _number_of_tiles) {
    this->imagesFilePaths = {
        {Images::Lena, ":/resources/Lena.png"},
        {Images::Mario, ":/resources/Mario.png"}
};
    QPixmap fullImage(this->imagesFilePaths[image]);
    this->_image = fullImage;
    this->setButtonSize(_number_of_tiles);
}

QIcon ImageProcessor::getIcon(int _row, int _col){return this->createButtonIcon(_row, _col);}

QSize ImageProcessor::getButtonSize(){return this->buttonSize;}

void ImageProcessor::setButtonSize(int _number_of_tiles){this->buttonSize = QSize(floor(this->_image.width()/_number_of_tiles), floor(this->_image.height()/_number_of_tiles));}

QIcon ImageProcessor::createButtonIcon(int _row, int _col)
{
    QIcon icon(cropImage(_row,_col));
    return icon;
}

QPixmap ImageProcessor::cropImage(int _row, int _col)
{   int width = this->_image.width();
    int height = this ->_image.height();
    QRect cropRect = QRect(_row*width,_col*height,this->buttonSize.width(), this->buttonSize.height());
    return this->_image.copy(cropRect);
}

