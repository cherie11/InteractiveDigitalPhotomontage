#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QString>
#include <QTimer>
#include <cstdio>
#include <QProcess>
#include <iostream>
#include <QDebug>
QString param_text = " 0 ";
void MainWindow::setMode(){
    QAction *sa = (QAction*)sender();
    QString modeName = sa->objectName();
    QString index = modeName.right(1);
    mode = index.toInt();
    QString modeText[] = {
        "USER_SPECIFY",
        "MAX_LUMIN",
        "MIN_LUMIN",
        "ERASE",
        "MAX_LIKEHOOD",
        "MIN_LIKEHOOD",
        "CONTRAST",
        "MAX_DIFF",
        "USER_SPECIFY_P"
    };
    modeText[mode].append(" *");
    ui->mode0->setText(modeText[0]);
    ui->mode1->setText(modeText[1]);
    ui->mode2->setText(modeText[2]);
    ui->mode3->setText(modeText[3]);
    ui->mode4->setText(modeText[4]);
    ui->mode5->setText(modeText[5]);
    ui->mode6->setText(modeText[6]);
    ui->mode7->setText(modeText[7]);
    ui->mode8->setText(modeText[8]);
}

void MainWindow::setParam(){
    bool isOK;
    param_text = QInputDialog::getText(NULL, "输入参数",
                                                   "",
                                                   QLineEdit::Normal,
                                                   "",
                                                   &isOK);
    if(isOK) {

    /*do what you want*/
    }
}

void MainWindow::init(){
    imgs.clear();
    curId=-1;
    mode = 0;
    isEdit=false;
    editorOpened = false;
    ui->setupUi(this);
    connect(ui->openFile,SIGNAL(triggered()),this,SLOT(openImages()));
    connect(ui->remove,SIGNAL(triggered()),this,SLOT(removeCurrentImage()));
    connect(ui->removeAll,SIGNAL(triggered()),this,SLOT(removeAllImages()));
    connect(ui->generate,SIGNAL(triggered()),this,SLOT(generatePoisson()));
	connect(ui->viewResult, SIGNAL(triggered()), this, SLOT(openImageResult()));
	connect(ui->saveResult, SIGNAL(triggered()), this, SLOT(saveImageResult()));
    connect(ui->helper,SIGNAL(triggered()),this,SLOT(showUserHelp()));
    connect(ui->aboutUs,SIGNAL(triggered()),this,SLOT(showAboutUs()));
    connect(ui->mode0, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode1, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode2, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode3, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode4, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode5, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode6, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode7, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->mode8, SIGNAL(triggered()), this, SLOT(setMode()));
    connect(ui->inputParam,SIGNAL(triggered()),this,SLOT(setParam()));
    // Keyboard shortcuts
    ui->mode0->setShortcut(Qt::Key_0);
    ui->mode1->setShortcut(Qt::Key_1);
    ui->mode2->setShortcut(Qt::Key_2);
    ui->mode3->setShortcut(Qt::Key_3);
    ui->mode4->setShortcut(Qt::Key_4);
    ui->mode5->setShortcut(Qt::Key_5);
    ui->mode6->setShortcut(Qt::Key_6);
    ui->mode7->setShortcut(Qt::Key_7);
    ui->mode8->setShortcut(Qt::Key_8);
    ui->generate->setShortcut(Qt::Key_G);
    ui->openFile->setShortcut(Qt::Key_O);
    ui->remove->setShortcut(QKeySequence::Delete);
	ui->viewResult->setShortcut(Qt::Key_V);
	ui->saveResult->setShortcut(QKeySequence::Save);

    ui->mode0->setText("USER_SPECIFY *");
    ui->remove->setDisabled(true);
    ui->removeAll->setDisabled(true);
    ui->generate->setDisabled(true);
	ui->viewResult->setDisabled(true);
	ui->saveResult->setDisabled(true);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkGenerateImage()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveEvent(QMoveEvent *) {
    if (editorOpened) {
        iedit->move(this->pos().x() + 800, this->pos().y());
    }
}

void MainWindow::openEditor(){
    QPushButton *btn = (QPushButton*)sender();
    QString btnName = btn->objectName();
    QString index = btnName.right(1);
    curId = index.toInt();
    if (!editorOpened) {
        iedit = new ImageEditor();
        iedit->move(this->pos().x() + 800, this->pos().y());
        editorOpened = true;
        connect(iedit, SIGNAL(sendEdit(QPixmap*, QPixmap*)), this, SLOT(receiveEdit(QPixmap*, QPixmap*)));
        connect(iedit, SIGNAL(editorClosed()), this, SLOT(setEditorClosed()));
    }
	iedit->setImageOnEditor(imgs[curId]);
    iedit->show();
}

void MainWindow::setEditorClosed() {
    editorOpened = false;
}

void MainWindow::displayImages(){
    QHBoxLayout *l = new QHBoxLayout;
    QPushButton *pushButton;
    QString str("pushButton %1");
    QWidget *widget = new QWidget(this);
    for (unsigned int i = 0; i < imgs.size(); i++) {
        pushButton = new QPushButton(widget);
        pushButton->setMinimumSize(256, 144);
        pushButton->setMaximumSize(256, 144);
        pushButton->setObjectName(str.arg(i));
        QPixmap scaledPixmap = imgs[i].img->scaled(QSize(256, 144), Qt::KeepAspectRatio);
        pushButton->setIcon(QIcon(scaledPixmap));
        pushButton->setIconSize(QSize(240, 135));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(openEditor()));
        l->addWidget(pushButton);
    }
    widget->setLayout(l);
    ui->scrollArea->setWidget(widget);
	if (!imgResult.isNull()) {
		QPixmap scaledPixmap = imgResult.scaled(QSize(560, 315), Qt::KeepAspectRatio);
		ui->compositeImage->setPixmap(scaledPixmap);
	}
}

void MainWindow::openImages() {
    QStringList filenames;
    filenames = QFileDialog::getOpenFileNames(this, tr("选择图像"), "", tr("Images (*.png *.bmp *.jpg)"));
    if (filenames.isEmpty()) {
        return;
    }
    for(int i=0;i<filenames.size();i++){
        QImage *img = new QImage;
        if (!(img->load(filenames[i]))) {
            cout << "Cannot open " << filenames[i].toStdString() << "." << endl;
            delete img;
            continue;
        }
        QPixmap pix = QPixmap::fromImage(*img);
        Image newImg(&pix);
        imgs.push_back(newImg);
    }
	displayImages();
	ui->remove->setDisabled(false);
	ui->removeAll->setDisabled(false);
	ui->generate->setDisabled(false);
	ui->changeBase->setDisabled(false);
    deleteTempFiles();
}

void MainWindow::removeCurrentImage(){
	if (imgs.size() == 1) {
		init();
		return;
	}
	if (editorOpened) {
		iedit->close();
	}
    imgs.erase(imgs.begin()+curId);
    if((unsigned int)curId>=imgs.size()){
        curId--;
    }
    displayImages();
}

void MainWindow::removeAllImages(){
    init();
}

void MainWindow::showUserHelp(){
    QMessageBox::information(this,tr("使用说明"),tr("应用开发中，请耐心等待."));
}

void MainWindow::showAboutUs(){
    QMessageBox::information(this,tr("关于我们"),tr("作者：wxw,lz,wzh"));
}

void MainWindow::openImageResult() {
	if (!imgResult.isNull()) {
		viewer = new ImageEditor();
		Image tmp = Image(&imgResult);
		viewer->setImageOnEditor(tmp);
		viewer->disableEdit();
		viewer->show();
	}
}

void MainWindow::saveImageResult() {
	if (imgResult.isNull()) {
		return;
	}
	QString filename;
	filename = QFileDialog::getSaveFileName(this, tr("保存图像"), "", tr("Images (*.png *.bmp *.jpg)"));
	if (filename.isEmpty()) {
		return;
	}
	imgResult.save(filename);
}

void MainWindow::closeEvent(QCloseEvent *) {
    if (editorOpened) {
        iedit->close();
    }
}

Mat MainWindow::read(string path) {
    Mat res = imread(path);
    Mat out;
    int ratio = 1;
    cv::resize(res, out, Size(res.cols / ratio, res.rows / ratio), INTER_AREA);
    return out;
}
void MainWindow::deleteTempFiles() {
    if (!remove((directory + logName).toStdString().c_str())) {
        cout << "Remove file " << (directory + logName).toStdString() << endl;
    }
    if (!remove((directory + imgResultName).toStdString().c_str())) {
        cout << "Remove file " << (directory + imgResultName).toStdString() << endl;
    }
    QString imgNameTmpl("*_tmp.jpg");
    QString editNameTmpl("*_edit.jpg");
    QString labelNameTmpl("*_label.bmp");
    for (int i = 0; i < 100; i++) {
        QString num = QString::number(i, 10);
        QString imgName = imgNameTmpl;
        QString editName = editNameTmpl;
        QString labelName= labelNameTmpl;
        imgName.replace(0, 1, num);
        editName.replace(0, 1, num);
        labelName.replace(0, 1, num);
        if (!remove((directory + imgName).toStdString().c_str())) {
            cout << "Remove file " << (directory + imgName).toStdString() << endl;
        }
        if (!remove((directory + editName).toStdString().c_str())) {
            cout << "Remove file " << (directory + editName).toStdString() << endl;
        }
        if (!remove((directory + labelName).toStdString().c_str())) {
            cout << "Remove file " << (directory + labelName).toStdString() << endl;
        }
    }
}

void MainWindow::receiveEdit(QPixmap *edit, QPixmap *label) {
    if (edit->cacheKey() != imgs[curId].imgEdit->cacheKey()) {
		imgs[curId].setImageEdit(edit, label);
    }
}

void MainWindow::checkGenerateImage(){
	FILE *fp = fopen((directory + logName).toStdString().c_str(), "r");
    if(fp==NULL){
        printf("no detect\n");
        return;
    }

    // Get file content

    if( /*finished condition*/ true ){
        QImage *img = new QImage;
        printf("detect\n");
        if(! ( img->load(directory+imgResultName) ) ){
//            QMessageBox::information(this,tr("Fatal Error"),tr("Can not open image result!"));
            delete img;
            return;
        }
		imgResult = QPixmap::fromImage(*img);
        QPixmap scaledPixmap = imgResult.scaled(QSize(560, 315), Qt::KeepAspectRatio);
        ui->compositeImage->setPixmap(scaledPixmap);
		ui->saveResult->setDisabled(false);
		ui->viewResult->setDisabled(false);
        timer->stop();
        cout << "Timer stops" << endl;
    }
}

void MainWindow::generatePoisson(){
    deleteTempFiles();
	if (editorOpened) {
		iedit->close();
	}
    QString filePath = "/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/";
    QString imgnametmpl("*_tmp.jpg");
    QString editnametmpl("*_edit.jpg");
    QString labelnametmpl("*_label.bmp");
    for(int i=0;i<imgs.size();i++){
            QString num=QString::number(i, 10);
            QString imgname = imgnametmpl;
            imgname.replace(0,1,num);
            imgs[i].img->save(directory+imgname);
            if(imgs[i].isEdited()){
                QString editname = editnametmpl;
                QString labelname = labelnametmpl;
                editname.replace(0,1,num);
                labelname.replace(0,1,num);
                imgs[i].imgEdit->save(directory + editname);
                imgs[i].imgLabel->save(directory + labelname);
            }
        }

    QString param1, param2,param3;
	param3 = QString::number(mode, 10);
    if(mode == 0 || mode == 8){
		for (int i = 0; i < imgs.size(); i++) {

                param1 += " " + directory + QString::number(i, 10) + "_tmp.jpg";
                param2 += " " + directory + QString::number(i, 10) + "_label.bmp ";
        }
    }
    else if(mode == 3){
        for (int i = 0; i < imgs.size(); i++) {
                param1 += " " + directory + QString::number(i, 10) + "_tmp.jpg";
                if(imgs[i].isEdited()){
                    param2 += " " + directory + QString::number(i, 10) + "_label.bmp ";
                }
                else{
                    param2 += " PLATE ";
                }
        }
    }
    else {
        cout<<"qt in mode 6"<<endl;
        for (int i = 0; i < imgs.size(); i++) {
                param1 += " " + directory + QString::number(i, 10) + "_tmp.jpg";
        }
    }
    timer->start(timeSlot);
    cout << "Timer starts" << endl;
    cout<<param1.toStdString()<<endl;
    cout<<param2.toStdString()<<endl;
	cout << "param3 = " << param3.toStdString() << endl;
    if(param_text.size() == 0){
        param_text = "0";
    }
    cout<<"user coefficient:"<<param_text.toStdString()<<endl;
    QProcess::startDetached(directory+"project_cml "+" "+ param_text+" "+param3+" "+param1+" "+param2);
    //QProcess::startDetached("/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/project_cml "+param1+param2);
}
