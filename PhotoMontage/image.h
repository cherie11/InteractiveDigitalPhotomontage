#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>

class Image
{
public:
    Image();
    Image(QPixmap *);
    QPixmap *img;
    QPixmap *imgEdit;
    bool isEdited();
    void setImageEdit(QPixmap *);
    void deleteImageEdit();
private:
    bool edited;
};

#endif // IMAGE_H
