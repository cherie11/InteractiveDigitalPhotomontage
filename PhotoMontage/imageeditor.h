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
    void setImageOnEditor(Image);
    void setColor(QColor c);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
	void closeEvent(QCloseEvent *event);
    void disableEdit();

private:
    Ui::ImageEditor *ui;
	QCursor cursor;
	Image image;
    QPoint startPos;
	QColor color;
    int weight;
    bool enableEdit;
	bool startPainting;

signals:
	void sendEdit(QPixmap *, QPixmap *);
	void editorClosed();

public slots:
    void ShowColor();
	void increaseWidth();
	void decreaseWidth();
    void clear();
    void saveEdit();
};

#endif // IMAGEEDITOR_H
