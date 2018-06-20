#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::setUIImageEditActionsDisabled(bool b){
ui->viewEdit->setDisabled(b);
ui->deleteEdit->setDisabled(b);
ui->deleteAllEdit->setDisabled(b);
ui->outputEdit->setDisabled(b);
}

void MainWindow::setMode(){
QAction * sa = (QAction*)sender() ;
QString   modeName = sa->objectName();
QString index=modeName.right(1);
int ID=index.toInt();

if( ID == 0 ){
    mode =0;
    ui->mode0->setText("USER_SPECIFY *");
    ui->mode1->setText("MAX_LUMIN");
    ui->mode2->setText("ERASE");
}
else if( ID == 1 )
{
    mode = 1;
    ui->mode0->setText("USER_SPECIFY");
    ui->mode1->setText("MAX_LUMIN *");
    ui->mode2->setText("ERASE");
}
else{
    mode = 2;
    ui->mode0->setText("USER_SPECIFY");
    ui->mode1->setText("MAX_LUMIN");
    ui->mode2->setText("ERASE *");
}


}

void MainWindow::init(){
imgs.clear();
curId=-1;
mode = 0;
isEdit=false;
ui->setupUi(this);
connect(ui->openFile,SIGNAL(triggered()),this,SLOT(openImage()));
connect(ui->remove,SIGNAL(triggered()),this,SLOT(removeCurrentImage()));
connect(ui->removeAll,SIGNAL(triggered()),this,SLOT(removeAllImages()));
connect(ui->generate,SIGNAL(triggered()),this,SLOT(generatePoisson()));
connect(ui->startEdit,SIGNAL(triggered()),this,SLOT(openEditor()));
connect(ui->viewEdit,SIGNAL(triggered()),this,SLOT(viewEdit()));
connect(ui->deleteEdit,SIGNAL(triggered()),this,SLOT(deleteCurrentImageEdit()));
connect(ui->deleteAllEdit,SIGNAL(triggered()),this,SLOT(deleteAllImageEdits()));
connect(ui->outputEdit,SIGNAL(triggered()),this,SLOT(saveImageEdit()));
connect(ui->helper,SIGNAL(triggered()),this,SLOT(showUserHelp()));
connect(ui->aboutUs,SIGNAL(triggered()),this,SLOT(showAboutUs()));
connect(ui->mode0,SIGNAL(triggered()),this,SLOT(setMode()));
connect(ui->mode1,SIGNAL(triggered()),this,SLOT(setMode()));
connect(ui->mode2,SIGNAL(triggered()),this,SLOT(setMode()));
ui->mode0->setText("USER_SPECIFY *");
ui->remove->setDisabled(true);
ui->removeAll->setDisabled(true);
//ui->generate->setDisabled(true);
ui->startEdit->setDisabled(true);
setUIImageEditActionsDisabled(true);
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

void MainWindow::openEditor(){
iedit=new ImageEditor();
if(imgs[curId].isEdited()){
    iedit->setImage(imgs[curId].imgEdit);
}else{
    iedit->setImage(imgs[curId].img);
}
connect(iedit,SIGNAL(sendEdit(QPixmap*)),this,SLOT(receiveEdit(QPixmap*)));
iedit->show();
}

void MainWindow::showImage(){
QPushButton *btn=(QPushButton*)sender();
QString btnName = btn->objectName();
QString index=btnName.right(1);
curId=index.toInt();
if(curId>=0&&(unsigned int)curId<imgs.size()){
    if(isEdit){
        QPixmap scaledPixmap=imgs[curId].imgEdit->scaled(QSize(560,315),Qt::KeepAspectRatio);
        ui->curImage->setPixmap(scaledPixmap);
    }else{
        QPixmap scaledPixmap=imgs[curId].img->scaled(QSize(560,315),Qt::KeepAspectRatio);
        ui->curImage->setPixmap(scaledPixmap);
    }

}
}

void MainWindow::displayImages(){
QHBoxLayout *l=new QHBoxLayout;
QPushButton* pushButton;
QString str("pushButton %1");
QWidget *widget=new QWidget(this);
for (unsigned int i=0; i<imgs.size(); i++){
    pushButton = new QPushButton(widget);
    pushButton->setMinimumSize(256,144);
    pushButton->setMaximumSize(256,144);
    pushButton->setObjectName(str.arg(i));
    QPixmap scaledPixmap=imgs[i].img->scaled(QSize(256,144),Qt::KeepAspectRatio);
    pushButton->setIcon(QIcon(scaledPixmap));
    pushButton->setIconSize(QSize(240,135));
    connect(pushButton,SIGNAL(clicked()),this,SLOT(showImage()));
    l->addWidget(pushButton);
}
widget->setLayout(l);
ui->scrollArea->setWidget(widget);
}

void MainWindow::openImage(){
QString filename;
filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
if(filename.isEmpty()){
    return;
}
else{
    QImage *img=new QImage;
    if(! ( img->load(filename) ) ){
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        delete img;
        return;
    }
    QPixmap pix=QPixmap::fromImage(*img);
    Image newImg(&pix);
    imgs.push_back(newImg);
    QPixmap scaledPixmap=pix.scaled(QSize(560,315),Qt::KeepAspectRatio);
    ui->curImage->setPixmap(scaledPixmap);
    curId=imgs.size()-1;
    displayImages();
    ui->remove->setDisabled(false);
    ui->removeAll->setDisabled(false);
    ui->generate->setDisabled(false);
    ui->startEdit->setDisabled(false);
}
}

void MainWindow::receiveEdit(QPixmap *p){
if(p->cacheKey()!=imgs[curId].img->cacheKey()){
    imgs[curId].setImageEdit(p);
    setUIImageEditActionsDisabled(false);
}else{
    if(imgs[curId].isEdited()){
        deleteCurrentImageEdit();
    }
}
}

void MainWindow::viewEdit(){
if(isEdit){
   ui->viewEdit->setText(tr("查看编辑"));
   isEdit=false;
   QPixmap scaledPixmap=imgs[curId].img->scaled(QSize(560,315),Qt::KeepAspectRatio);
   ui->curImage->setPixmap(scaledPixmap);
}else{
    ui->viewEdit->setText(tr("退出查看n"));
    isEdit=true;
    QPixmap scaledPixmap=imgs[curId].imgEdit->scaled(QSize(560,315),Qt::KeepAspectRatio);
    ui->curImage->setPixmap(scaledPixmap);
}
}

void MainWindow::deleteCurrentImageEdit(){
imgs[curId].deleteImageEdit();
isEdit=false;
ui->viewEdit->setText(tr("查看编辑"));
QPixmap scaledPixmap=imgs[curId].img->scaled(QSize(560,315),Qt::KeepAspectRatio);
ui->curImage->setPixmap(scaledPixmap);
int count=0;
for(unsigned int i=0;i<imgs.size();i++){
    if(imgs[i].isEdited()){
        count++;
    }
}
if(count==0){
    setUIImageEditActionsDisabled(true);
}
}

void MainWindow::deleteAllImageEdits(){
isEdit=false;
ui->viewEdit->setText(tr("查看编辑"));
QPixmap scaledPixmap=imgs[curId].img->scaled(QSize(560,315),Qt::KeepAspectRatio);
ui->curImage->setPixmap(scaledPixmap);
setUIImageEditActionsDisabled(true);
for(unsigned int i=0;i<imgs.size();i++){
    imgs[i].deleteImageEdit();
}
}

void MainWindow::removeCurrentImage(){
imgs.erase(imgs.begin()+curId);
if((unsigned int)curId>=imgs.size()){
    curId--;
}
if(curId<0){
    init();
    return;
}
if(isEdit){
    QPixmap scaledPixmap=imgs[curId].imgEdit->scaled(QSize(560,315),Qt::KeepAspectRatio);
    ui->curImage->setPixmap(scaledPixmap);
}else{
    QPixmap scaledPixmap=imgs[curId].img->scaled(QSize(560,315),Qt::KeepAspectRatio);
    ui->curImage->setPixmap(scaledPixmap);
}
displayImages();
}

void MainWindow::removeAllImages(){
init();
}

void MainWindow::saveImageEdit(){
QString filename;
filename=QFileDialog::getSaveFileName(this,tr("Save files"),"",tr("Images (*.png *.bmp *.jpg)"));
if (filename.isEmpty()) {
    return;
}
else {
    imgs[curId].imgEdit->save(filename);
}
}

void MainWindow::showUserHelp(){
QMessageBox::information(this,tr("使用说明"),tr("应用开发中，请耐心等待."));
}

void MainWindow::showAboutUs(){
QMessageBox::information(this,tr("关于我们"),tr("作者：wxw,lz,wzh"));
}

Mat MainWindow::difference(Mat m1, Mat m2) {
if (m1.rows != m2.rows || m1.cols != m2.cols || m1.channels() != m2.channels()) {
    return Mat();
}
Mat result(m1.rows, m1.cols, CV_8UC1);
result.setTo(0);
int thres = 0;
for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.cols; j++) {
        int diff = 0;
        for (int c = 0; c < m1.channels(); c++) {
            diff += abs(m1.at<uchar>(i, j*m1.channels() + c) - m2.at<uchar>(i, j*m2.channels() + c));
        }
        if (diff > thres) {
            result.at<uchar>(i, j) = 255;
        }
    }
}
return result;
}

Mat MainWindow::read(string path) {
Mat res = imread(path);
Mat out;
cv::resize(res, out, Size(res.cols/2, res.rows/2), INTER_AREA);
return out;
}

void MainWindow::checkGenerateImage(){
/*
 * input you file name first,
 * set up a special simbol for checking whether process finished,
 * if the process does not finish then wait,
 * if the process finishes then read the image result and stop the timer.
 *
 */
QString path = "/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/";
    QString logName(path+"finish.txt");
    QString imgResultName(path+"compositeimage.png");

    FILE *fp = fopen(logName.toStdString().c_str(), "r");
    if(fp==NULL){
        printf("Cannot open file!\n");
        printf("no detect\n");
        return;
    }

    // Get file content

    if( /*finished condition*/ true ){
        QImage *img=new QImage;
        printf("detect\n");
        if(! ( img->load(imgResultName) ) ){
            QMessageBox::information(this,tr("Fatal Error"),tr("Can not open image result!"));
            delete img;
            return;
        }
        QPixmap pix=QPixmap::fromImage(*img);
        iedit=new ImageEditor();
        iedit->setImage(&pix);
        iedit->disableEdit();
        iedit->show();
        timer->stop();
        cout << "Timer stops" << endl;
    }
}

void MainWindow::generatePoisson(){
//    QString imgname("*_tmp.jpg");
//    QString editname("*_edit.jpg");
//    Mat MatImages[imgs.size()];
//    for(unsigned int i=0;i<imgs.size();i++){
//        QString num=QString::number(i+1,10);
//        imgname.replace(0,1,num);
//        editname.replace(0,1,num);
//         imgs[i].img->save("/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/PhotoMontage/PhotoMontage"+imgname);
//         imgs[i].imgEdit->save("/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/PhotoMontage/PhotoMontage"+editname);

//        imgs[i].img->save(imgname);
//        imgs[i].imgEdit->save(editname);
//    }
QString imgname("*_tmp.jpg");
QString editname("*_edit.jpg");
QString labelName("*_label.bmp");
QString directory("/Users/apple/Desktop/计算摄影学/qt_montage/build-PhotoMontage-Desktop_Qt_5_8_0_clang_64bit-Default/");
QString param1,param2;
for(unsigned int i=0;i<imgs.size();i++){
    QString num=QString::number(i+1,10);
    imgname.replace(0,1,num);
    editname.replace(0,1,num);
    labelName.replace(0,1,num);
    param1 += " "+imgname;
    param2 += " "+param2;
    labelName.replace(0,1,num);
    imgs[i].img->save(directory+imgname);
    imgs[i].imgEdit->save(directory+editname);
    Mat cvImg=read((directory+imgname).toStdString());
    Mat cvEdit=read((directory+editname).toStdString());
    Mat cvLabel=difference(cvImg,cvEdit);
    imwrite((directory+labelName).toStdString(),cvLabel);
}
timer->start(timeSlot);
cout << "Timer starts" << endl;

QProcess::startDetached(directory+"project_cml "+param1+param2);
}

//    vector<Mat> images;
//    vector<Mat> labels;
//    QString preimagename = "*.JPG";
//    QString preeditname = "*.bmp";
//    for (unsigned int i = 0; i < imgs.size(); i++) {
//        QString num = QString::number(i + 1, 10);
//        imgname.replace(0, 1, num);
//        editname.replace(0, 1, num);
//        Mat src = read(imgname.toStdString());
//        Mat edit = read(editname.toStdString());
//        Mat dst = difference(src, edit);
//        images.push_back(src);
//        labels.push_back(dst);
    /*
    QString number = QString::number(i, 10);
    preimagename.replace(0, 1, number);
    preeditname.replace(0, 1, number);
    Mat preimage = read(preimagename.toStdString());
    Mat preedit = read(preeditname.toStdString());
    images.push_back(preimage);
    labels.push_back(preedit);*/
//    }

// Output labels
//  QString diffname = "*_diff.jpg";
//  for (unsigned int i = 0; i < labels.size(); i++) {
//      QString num = QString::number(i + 1, 10);
//      diffname.replace(0, 1, num);
//      imwrite(diffname.toStdString(), labels[i]);
//  }
//    cout<<"asdasd"<<endl;
//    Mat label(images[0].rows, images[0].cols, CV_8SC1);
//    label.setTo(PhotoMontage::undefined);
//    int height = images[0].rows;
//    int width = images[0].cols;
//     for (unsigned int i = 0; i < imgs.size(); i++) {
//        QString num = QString::number(i + 1, 10);
//        imgname.replace(0, 1, num);
//        editname.replace(0, 1, num);
//        remove(imgname.toStdString().c_str());
//        remove(editname.toStdString().c_str());
//    }

//    for (int labelIdx = 0; labelIdx < images.size(); labelIdx++) {
//        for (int y = 0; y < height; y++) {
//            for (int x = 0; x < width; x++) {
//                if (/*labels[labelIdx].at<uchar>(y, x) > 0*/
//                    labels[labelIdx].at<Vec3b>(y, x)(0) > 0) {
//                    label.at<uchar>(y, x) = labelIdx;
//                }
//            }
//        }
//    }


//    PhotoMontage PM;
//    PM.Run(images, label,mode);
//    for (unsigned int i = 0; i < imgs.size(); i++) {
//        QString num = QString::number(i + 1, 10);
//        imgname.replace(0, 1, num);
//        editname.replace(0, 1, num);
//        remove(imgname.toStdString().c_str());
//        remove(editname.toStdString().c_str());
//    }
//}

