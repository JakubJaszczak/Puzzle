#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qicon.h"
#include "qpixmap.h"
#include <QString>
#include <map>

enum class Images {Tiger,Mario,};

class ImageProcessor
{
public:
    ImageProcessor(Images image, int _numer_of_tiles);
    QIcon getIcon(int _row, int _col);
    QIcon getIcon(int idx);
    QSize getButtonSize();
    void setBoardIcons(QSize boardSize);

private:
    QPixmap _image;
    QSize buttonSize;
    void setButtonSize(int _number_of_tiles);
    QPixmap cropImage(int _row, int _col);
    QIcon createButtonIcon(int _row, int _col);
    std::map<Images, const char*> imagesFilePaths;
    std::vector<std::vector<QIcon>> boardIcons;
    int _number_of_tiles;

};

#endif // IMAGEPROCESSOR_H
