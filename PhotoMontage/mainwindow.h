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
#include <QTimer>

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
	void moveEvent(QMoveEvent *);
	void closeEvent(QCloseEvent *);

private:
	// Variables
    Ui::MainWindow *ui;
    ImageEditor *iedit;
	ImageEditor *viewer;
    vector<Image> imgs;
	QPixmap imgResult;
    int curId;
	int mode;
    bool isEdit;
	bool editorOpened;
    QTimer *timer;
	const int timeSlot = 2000;
    const QString directory = "../build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/";
	//const QString directory = "C:/Study/tmp/";
	const QString logName = "finish.txt";
    const QString imgResultName = "compositeimage.png";
	// Functions
	void init();
	Mat difference(Mat m1, Mat m2);
	Mat read(string path);
	void deleteTempFiles();

public slots:
     void setParam();
    void openEditor();
	void openImages();
    void removeCurrentImage();
    void removeAllImages();
	void receiveEdit(QPixmap *, QPixmap *);
    void showUserHelp();
    void showAboutUs();
    void generatePoisson();
	void checkGenerateImage();
	void setMode();
	void setEditorClosed();
	void openImageResult();
	void saveImageResult();
};

#endif // MAINWINDOW_H
