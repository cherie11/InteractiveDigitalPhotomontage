#include "image.h"

Image::Image()
{
    img=new QPixmap;
    imgEdit=new QPixmap;
    edited=false;
}

Image::Image(QPixmap *pix){
    img=new QPixmap;
    *img=*pix;
    imgEdit=new QPixmap;
    edited=false;
}

bool Image::isEdited(){
    return edited;
}

void Image::setImageEdit(QPixmap *pix){
    *imgEdit=*pix;
    edited=true;
}

void Image::deleteImageEdit(){
    imgEdit=new QPixmap;
    edited=false;
}
