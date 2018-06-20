#include "imageeditor.h"
#include "ui_imageeditor.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

void ImageEditor::ShowColor(){
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if(color.isValid())
    {
        this->color=color;
        QPixmap p(28,28);
        p.fill(color);
        ui->colorBtn->setIcon(QIcon(p));
    }
}

void ImageEditor::setImage(QPixmap *p){
    img=p;
    *pix=*img;
    this->setMinimumSize(pix->size());
    this->setMaximumSize(pix->size());
}

ImageEditor::ImageEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditor)
{
    ui->setupUi(this);

    QPixmap pixmap(28,28);
    pixmap.fill(Qt::black);
    ui->colorBtn->setIcon(QIcon(pixmap));
    connect(ui->colorBtn,SIGNAL(clicked()),this,SLOT(ShowColor()));
    connect(ui->clearBtn,SIGNAL(clicked()),this,SLOT(clear()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(saveEdit()));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setWidth(int)));

    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    img=new QPixmap;
    pix=new QPixmap(size());
    pix->fill(Qt::white);
    color=Qt::black;
    ui->widthSpinBox->setValue(8);
    weight=ui->widthSpinBox->value();
    enableEdit=true;
}

ImageEditor::~ImageEditor()
{
    delete ui;
}

void ImageEditor::setWidth(int w)
{
    weight=w;
}

void ImageEditor::setColor(QColor c)
{
    color=c;
}

void ImageEditor::mousePressEvent(QMouseEvent *e)
{
    startPos = e->pos();
}

void ImageEditor::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(weight);
    pen.setColor(color);
    painter->begin(pix);
    painter->setPen(pen);
    if(enableEdit){
        painter->drawLine(startPos, e->pos());
    }
    painter->end();
    startPos = e->pos();
    this->update();
}

void ImageEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*pix);
}


void ImageEditor::clear(){
    *pix=*img;
    this->update();
}

void ImageEditor::saveEdit(){
    emit sendEdit(pix);
}

void ImageEditor::disableEdit(){
    ui->colorBtn->setVisible(false);
    ui->clearBtn->setVisible(false);
    ui->saveBtn->setVisible(false);
    ui->widthSpinBox->setVisible(false);
    enableEdit=false;
}
