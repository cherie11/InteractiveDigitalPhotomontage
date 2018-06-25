#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <opencv2/opencv.hpp>
using namespace cv;

class Image
{
public:
	Image();
    Image(QPixmap *);
    QPixmap *img;
    QPixmap *imgEdit;
	QPixmap *imgLabel;
    bool isEdited();
	void setImage(QPixmap *);
    void setImageEdit(QPixmap *, QPixmap *);
    void deleteImageEdit();
};

#endif // IMAGE_H
