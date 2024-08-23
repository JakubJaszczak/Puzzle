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
{
    QRect cropRect = QRect(_col*this->buttonSize.width(),_row*this->buttonSize.width(),this->buttonSize.width() -5, this->buttonSize.height()-5);
    return this->_image.copy(cropRect);
}

