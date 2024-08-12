#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qicon.h"
#include "qpixmap.h"
#include <QString>
#include <map>

enum class Images {Lena,Mario,};

class ImageProcessor
{
public:
    ImageProcessor(Images image, int _numer_of_tiles);
    QIcon getIcon(int _row, int _col);
    QSize getButtonSize();
    std::map<Images, const char*> imagesFilePaths;

private:
    QPixmap _image;
    QSize buttonSize;
    void setButtonSize(int _number_of_tiles);
    QPixmap cropImage(int _row, int _col);
    QIcon createButtonIcon(int _row, int _col);
};

#endif // IMAGEPROCESSOR_H
