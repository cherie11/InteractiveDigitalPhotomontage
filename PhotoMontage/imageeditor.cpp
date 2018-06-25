#include "imageeditor.h"
#include "ui_imageeditor.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
using namespace std;

void ImageEditor::ShowColor(){
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if(color.isValid())
    {
        this->color=color;
        QPixmap p(28,28);
        p.fill(color);
        ui->colorBtn->setIcon(QIcon(p));
		QPixmap pix(weight, weight);
		pix.fill(color);
		cursor = QCursor(pix, -1, -1);
		setCursor(cursor);
    }
}

void ImageEditor::setImageOnEditor(Image i){
	image = i;
	this->setMinimumSize(image.img->size());
	this->setMaximumSize(image.img->size());
	this->update();
}

ImageEditor::ImageEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditor)
{
    ui->setupUi(this);
	setMouseTracking(true);
	startPainting = false;
	enableEdit = true;
	color = Qt::yellow;
	weight = 8;
    QPixmap pixmap(28,28);
    pixmap.fill(color);
    ui->colorBtn->setIcon(QIcon(pixmap));
    connect(ui->colorBtn,SIGNAL(clicked()),this,SLOT(ShowColor()));
    connect(ui->clearBtn,SIGNAL(clicked()),this,SLOT(clear()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(saveEdit()));
	connect(ui->plusBtn, SIGNAL(clicked()), this, SLOT(increaseWidth()));
	connect(ui->minusBtn, SIGNAL(clicked()), this, SLOT(decreaseWidth()));
	ui->saveBtn->setShortcut(QKeySequence::Save);
	ui->clearBtn->setShortcut(QKeySequence::Delete);
	ui->colorBtn->setShortcut(Qt::Key_C);
	ui->plusBtn->setShortcut(Qt::Key_Equal);
	ui->minusBtn->setShortcut(45);
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
	QPixmap pix = QPixmap(size());
	pix.fill(Qt::white);
	image = Image(&pix);
	QPixmap p(weight, weight);
	p.fill(color);
	cursor = QCursor(p, -1, -1);
	setCursor(cursor);
}

ImageEditor::~ImageEditor()
{
    delete ui;
}

void ImageEditor::increaseWidth() {
	if (weight < 30) {
		weight++;
	}
	QPixmap p(weight, weight);
	p.fill(color);
	cursor = QCursor(p, -1, -1);
	setCursor(cursor);
}

void ImageEditor::decreaseWidth() {
	if (weight >= 3) {
		weight--;
	}
	QPixmap p(weight, weight);
	p.fill(color);
	cursor = QCursor(p, -1, -1);
	setCursor(cursor);
}

void ImageEditor::setColor(QColor c)
{
    color=c;
}

void ImageEditor::mousePressEvent(QMouseEvent *e)
{
    startPos = e->pos();
	startPainting = true;
}

void ImageEditor::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(weight);
    pen.setColor(color);
    painter->begin(image.imgEdit);
    painter->setPen(pen);
    if(enableEdit&&startPainting){
        painter->drawLine(startPos, e->pos());
    }
    painter->end();
	QPainter *labelPainter = new QPainter;
	QPen labelPen;
	labelPen.setStyle(Qt::SolidLine);
	labelPen.setWidth(weight);
	labelPen.setColor(Qt::white);
	labelPainter->begin(image.imgLabel);
	labelPainter->setPen(labelPen);
	if (enableEdit&&startPainting) {
		labelPainter->drawLine(startPos, e->pos());
	}
	labelPainter->end();
    startPos = e->pos();
    this->update();
	QSize toolBarSize;
	toolBarSize.setWidth(ui->horizontalLayoutWidget->size().width() + 5);
	toolBarSize.setHeight(ui->horizontalLayoutWidget->size().height() + 5);
	QRect clearBtnRect = QRect(ui->horizontalLayoutWidget->pos(), toolBarSize);
	if (clearBtnRect.contains(e->pos())) {
		setCursor(Qt::ArrowCursor);
	}
	else {
		QPixmap p(weight, weight);
		p.fill(color);
		cursor = QCursor(p, -1, -1);
		setCursor(cursor);
	}
}

void ImageEditor::mouseReleaseEvent(QMouseEvent *) {
	startPainting = false;
}

void ImageEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*image.imgEdit);
}

void ImageEditor::closeEvent(QCloseEvent *) {
	emit sendEdit(image.imgEdit, image.imgLabel);
	emit editorClosed();
}

void ImageEditor::clear(){
	image.deleteImageEdit();
    this->update();
}

void ImageEditor::saveEdit(){
	emit sendEdit(image.imgEdit, image.imgLabel);
}

void ImageEditor::disableEdit(){
    ui->colorBtn->setVisible(false);
    ui->clearBtn->setVisible(false);
    ui->saveBtn->setVisible(false);
	ui->minusBtn->setVisible(false);
	ui->plusBtn->setVisible(false);
    enableEdit=false;
}
