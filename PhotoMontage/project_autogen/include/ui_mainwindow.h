/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openFile;
    QAction *saveFile;
    QAction *saveAll;
    QAction *generate;
    QAction *helper;
    QAction *aboutUs;
    QAction *deleteEdit;
    QAction *deleteAllEdit;
    QAction *remove;
    QAction *removeAll;
    QAction *startEdit;
    QAction *viewEdit;
    QAction *outputEdit;
    QAction *action1;
    QAction *mode0;
    QAction *mode1;
    QAction *mode2;
    QWidget *centralWidget;
    QLabel *curImage;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *mode;
    QMenu *edit;
    QMenu *help;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QStringLiteral("openFile"));
        openFile->setEnabled(true);
        saveFile = new QAction(MainWindow);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        saveFile->setCheckable(false);
        saveFile->setEnabled(true);
        saveAll = new QAction(MainWindow);
        saveAll->setObjectName(QStringLiteral("saveAll"));
        generate = new QAction(MainWindow);
        generate->setObjectName(QStringLiteral("generate"));
        helper = new QAction(MainWindow);
        helper->setObjectName(QStringLiteral("helper"));
        aboutUs = new QAction(MainWindow);
        aboutUs->setObjectName(QStringLiteral("aboutUs"));
        deleteEdit = new QAction(MainWindow);
        deleteEdit->setObjectName(QStringLiteral("deleteEdit"));
        deleteAllEdit = new QAction(MainWindow);
        deleteAllEdit->setObjectName(QStringLiteral("deleteAllEdit"));
        remove = new QAction(MainWindow);
        remove->setObjectName(QStringLiteral("remove"));
        removeAll = new QAction(MainWindow);
        removeAll->setObjectName(QStringLiteral("removeAll"));
        startEdit = new QAction(MainWindow);
        startEdit->setObjectName(QStringLiteral("startEdit"));
        viewEdit = new QAction(MainWindow);
        viewEdit->setObjectName(QStringLiteral("viewEdit"));
        outputEdit = new QAction(MainWindow);
        outputEdit->setObjectName(QStringLiteral("outputEdit"));
        action1 = new QAction(MainWindow);
        action1->setObjectName(QStringLiteral("action1"));
        mode0 = new QAction(MainWindow);
        mode0->setObjectName(QStringLiteral("mode0"));
        mode1 = new QAction(MainWindow);
        mode1->setObjectName(QStringLiteral("mode1"));
        mode2 = new QAction(MainWindow);
        mode2->setObjectName(QStringLiteral("mode2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        curImage = new QLabel(centralWidget);
        curImage->setObjectName(QStringLiteral("curImage"));
        curImage->setGeometry(QRect(120, 20, 560, 315));
        curImage->setAutoFillBackground(false);
        curImage->setStyleSheet(QStringLiteral("border-top-color: rgb(255, 0, 0);"));
        curImage->setFrameShape(QFrame::Panel);
        curImage->setFrameShadow(QFrame::Sunken);
        curImage->setLineWidth(4);
        curImage->setMidLineWidth(2);
        curImage->setAlignment(Qt::AlignCenter);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 360, 760, 200));
        scrollArea->setFrameShape(QFrame::Panel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setLineWidth(3);
        scrollArea->setMidLineWidth(1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 754, 194));
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        file = new QMenu(menuBar);
        file->setObjectName(QStringLiteral("file"));
        mode = new QMenu(file);
        mode->setObjectName(QStringLiteral("mode"));
        edit = new QMenu(menuBar);
        edit->setObjectName(QStringLiteral("edit"));
        help = new QMenu(menuBar);
        help->setObjectName(QStringLiteral("help"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(file->menuAction());
        menuBar->addAction(edit->menuAction());
        menuBar->addAction(help->menuAction());
        file->addAction(openFile);
        file->addAction(remove);
        file->addAction(removeAll);
        file->addSeparator();
        file->addAction(mode->menuAction());
        file->addAction(generate);
        mode->addAction(mode0);
        mode->addAction(mode1);
        mode->addAction(mode2);
        edit->addAction(startEdit);
        edit->addAction(viewEdit);
        edit->addAction(deleteEdit);
        edit->addAction(deleteAllEdit);
        edit->addSeparator();
        edit->addAction(outputEdit);
        help->addAction(helper);
        help->addAction(aboutUs);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\263\212\346\235\276\345\233\276\345\203\217\347\274\226\350\276\221", Q_NULLPTR));
        openFile->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\345\233\276\347\211\207", Q_NULLPTR));
        saveFile->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", Q_NULLPTR));
        saveAll->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\205\250\351\203\250", Q_NULLPTR));
        generate->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\345\233\276\345\203\217", Q_NULLPTR));
        helper->setText(QApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", Q_NULLPTR));
        aboutUs->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216\346\210\221\344\273\254", Q_NULLPTR));
        deleteEdit->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\274\226\350\276\221", Q_NULLPTR));
        deleteAllEdit->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\205\250\351\203\250", Q_NULLPTR));
        remove->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\233\276\347\211\207", Q_NULLPTR));
        removeAll->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\205\250\351\203\250", Q_NULLPTR));
        startEdit->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\347\274\226\350\276\221", Q_NULLPTR));
        viewEdit->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\347\274\226\350\276\221", Q_NULLPTR));
        outputEdit->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\274\226\350\276\221", Q_NULLPTR));
        action1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        mode0->setText(QApplication::translate("MainWindow", "USER_SPECIFY", Q_NULLPTR));
        mode1->setText(QApplication::translate("MainWindow", "MAX_LUMIN", Q_NULLPTR));
        mode2->setText(QApplication::translate("MainWindow", "ERASE", Q_NULLPTR));
        curImage->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:24pt;\">\350\257\267\345\257\274\345\205\245\345\233\276\347\211\207</span></p></body></html>", Q_NULLPTR));
        file->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        mode->setTitle(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\250\241\345\274\217", Q_NULLPTR));
        edit->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", Q_NULLPTR));
        help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
