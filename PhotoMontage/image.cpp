#include "image.h"

Image::Image() {
	img = new QPixmap;
	imgEdit = new QPixmap;
	imgLabel = new QPixmap;
}

Image::Image(QPixmap *pix){
	img = new QPixmap;
	*img = *pix;
	imgEdit = new QPixmap;
	*imgEdit = *pix;
	imgLabel = new QPixmap(img->size());
	imgLabel->fill(Qt::black);
}

bool Image::isEdited(){
	return img->cacheKey() != imgEdit->cacheKey();
}

void Image::setImage(QPixmap *pix) {
	*img = *pix;
	*imgEdit = *pix;
	imgLabel = new QPixmap(img->size());
	imgLabel->fill(Qt::black);
}

void Image::setImageEdit(QPixmap *edit, QPixmap *label){
	*imgEdit = *edit;
	*imgLabel = *label;
}

void Image::deleteImageEdit(){
	imgEdit = new QPixmap;
	*imgEdit = *img;
	imgLabel = new QPixmap(img->size());
	imgLabel->fill(Qt::black);
}
