#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include "imageeditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayImages();

private:
    Ui::MainWindow *ui;
    ImageEditor *iedit;
    vector<Image> imgs;
    int curId;
    bool isEdit;
    void init();
    void setUIImageEditActionsDisabled(bool);
    Mat difference(Mat m1, Mat m2);
    Mat read(string path);
    int mode;
    QTimer *timer;
    const int timeSlot=5000;

public slots:
    void openEditor();
    void openImage();
    void showImage();
    void removeCurrentImage();
    void removeAllImages();
    void receiveEdit(QPixmap *);
    void viewEdit();
    void deleteCurrentImageEdit();
    void deleteAllImageEdits();
    void saveImageEdit();
    void showUserHelp();
    void showAboutUs();
    void generatePoisson();
    void checkGenerateImage();
    void setMode();
};

#endif // MAINWINDOW_H
