#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QToolButton>
#include <QPixmap>
#include "image.h"

namespace Ui {
class ImageEditor;
}

class ImageEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ImageEditor(QWidget *parent = 0);
    ~ImageEditor();
    void setImage(QPixmap *);
    void setColor(QColor c);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void disableEdit();

private:
    Ui::ImageEditor *ui;
    QPixmap *pix;
    QPixmap *img;
    QPoint startPos;
    QColor color;
    int weight;
    QPoint origin=QPoint(0,0);
    bool enableEdit;

signals:
    void sendEdit(QPixmap *);

public slots:
    void ShowColor();
    void setWidth(int);
    void clear();
    void saveEdit();
};

#endif // IMAGEEDITOR_H
