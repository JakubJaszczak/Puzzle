#include "imageprocessor.h"
/*!
 * \brief ImageProcessor::ImageProcessor Class constructor. Initializes a 2D array of icons. Array size and icon size depend on number of tiles on the board.
 * \param image Image of the board
 * \param _number_of_tiles Size of the board in one axis
 */
ImageProcessor::ImageProcessor(Images image, int _number_of_tiles) {
    this->imagesFilePaths = {
        {Images::Tiger, ":/resources/tiger.jpg"},
        {Images::Mario, ":/resources/Mario.png"}
};
    QPixmap fullImage(this->imagesFilePaths[image]);
    this->_image = fullImage;
    this->setButtonSize(_number_of_tiles);
    this->_number_of_tiles = _number_of_tiles;

    this->boardIcons.resize(_number_of_tiles);
    for (int row = 0; row<_number_of_tiles; ++row) {
        this->boardIcons[row].resize(_number_of_tiles);
        for (int col = 0; col<_number_of_tiles; ++col) {
            QIcon icon = createButtonIcon(row, col);
            this->boardIcons[row][col] = icon;
        }
    }
}
/*!
 * \brief ImageProcessor::getIcon Getter of a single icon from boardIcons array.
 * \param _row Row coordinate of array of icons.
 * \param _col Column coordinate of array of icons.
 * \return QIcon icon
 */
QIcon ImageProcessor::getIcon(int _row, int _col){return this->boardIcons[_row][_col];}
/*!
 * \brief ImageProcessor::getIcon Getter of a single icon from boardIcons array.
 * \param idx Index of a button
 * \return QIcon icon
 */
QIcon ImageProcessor::getIcon(int idx){
    int col = idx % this->_number_of_tiles;
    int row = idx / this->_number_of_tiles;
    return this->boardIcons[row][col];
}

/*!
 * \brief ImageProcessor::getButtonSize ButtonSize getter
 * \return QSize Size of a button in pixels.
 */
QSize ImageProcessor::getButtonSize(){return this->buttonSize;}

/*!
 * \brief ImageProcessor::setButtonSize ButtonSize setter
 * \param _number_of_tiles Size of the board in one axis
 */
void ImageProcessor::setButtonSize(int _number_of_tiles){this->buttonSize = QSize(floor(this->_image.width()/_number_of_tiles), floor(this->_image.height()/_number_of_tiles));}

/*!
 * \brief ImageProcessor::createButtonIcon Creates a single icon for a button with given row and column number
 * \param _row Row number
 * \param _col Col Number
 * \return Qicon icon
 */
QIcon ImageProcessor::createButtonIcon(int _row, int _col)
{
    QIcon icon(cropImage(_row,_col));
    return icon;
}

/*!
 * \brief ImageProcessor::cropImage Crops image(QPixmap) icon for a button with given row and column number
 * \param _row Row number of a button
 * \param _col Row number of a button
 * \return Cropped QPixmap
 */
QPixmap ImageProcessor::cropImage(int _row, int _col)
{
    QRect cropRect = QRect(_col*this->buttonSize.width(),_row*this->buttonSize.width(),this->buttonSize.width() -5, this->buttonSize.height()-5);
    return this->_image.copy(cropRect);
}

