/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
    QAction *generate;
    QAction *helper;
    QAction *aboutUs;
    QAction *remove;
    QAction *removeAll;
    QAction *mode0;
    QAction *mode1;
    QAction *mode2;
    QAction *mode3;
    QAction *mode4;
    QAction *mode5;
    QAction *mode6;
    QAction *mode7;
    QAction *mode8;
    QAction *changeBase;
    QAction *viewResult;
    QAction *saveResult;
    QAction *inputParam;
    QWidget *centralWidget;
    QLabel *compositeImage;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *help;
    QMenu *mode;
    QMenu *menu;
    QMenu *adjParam;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        openFile = new QAction(MainWindow);
        openFile->setObjectName(QStringLiteral("openFile"));
        openFile->setEnabled(true);
        generate = new QAction(MainWindow);
        generate->setObjectName(QStringLiteral("generate"));
        helper = new QAction(MainWindow);
        helper->setObjectName(QStringLiteral("helper"));
        aboutUs = new QAction(MainWindow);
        aboutUs->setObjectName(QStringLiteral("aboutUs"));
        remove = new QAction(MainWindow);
        remove->setObjectName(QStringLiteral("remove"));
        removeAll = new QAction(MainWindow);
        removeAll->setObjectName(QStringLiteral("removeAll"));
        mode0 = new QAction(MainWindow);
        mode0->setObjectName(QStringLiteral("mode0"));
        mode1 = new QAction(MainWindow);
        mode1->setObjectName(QStringLiteral("mode1"));
        mode2 = new QAction(MainWindow);
        mode2->setObjectName(QStringLiteral("mode2"));
        mode3 = new QAction(MainWindow);
        mode3->setObjectName(QStringLiteral("mode3"));
        mode4 = new QAction(MainWindow);
        mode4->setObjectName(QStringLiteral("mode4"));
        mode5 = new QAction(MainWindow);
        mode5->setObjectName(QStringLiteral("mode5"));
        mode6 = new QAction(MainWindow);
        mode6->setObjectName(QStringLiteral("mode6"));
        mode7 = new QAction(MainWindow);
        mode7->setObjectName(QStringLiteral("mode7"));
        mode8 = new QAction(MainWindow);
        mode8->setObjectName(QStringLiteral("mode8"));
        changeBase = new QAction(MainWindow);
        changeBase->setObjectName(QStringLiteral("changeBase"));
        viewResult = new QAction(MainWindow);
        viewResult->setObjectName(QStringLiteral("viewResult"));
        saveResult = new QAction(MainWindow);
        saveResult->setObjectName(QStringLiteral("saveResult"));
        inputParam = new QAction(MainWindow);
        inputParam->setObjectName(QStringLiteral("inputParam"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        compositeImage = new QLabel(centralWidget);
        compositeImage->setObjectName(QStringLiteral("compositeImage"));
        compositeImage->setGeometry(QRect(120, 20, 560, 320));
        compositeImage->setAutoFillBackground(false);
        compositeImage->setStyleSheet(QStringLiteral("border-top-color: rgb(255, 0, 0);"));
        compositeImage->setFrameShape(QFrame::Panel);
        compositeImage->setFrameShadow(QFrame::Sunken);
        compositeImage->setLineWidth(4);
        compositeImage->setMidLineWidth(2);
        compositeImage->setAlignment(Qt::AlignCenter);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 359, 760, 201));
        scrollArea->setFrameShape(QFrame::Panel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setLineWidth(3);
        scrollArea->setMidLineWidth(1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 754, 195));
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        file = new QMenu(menuBar);
        file->setObjectName(QStringLiteral("file"));
        help = new QMenu(menuBar);
        help->setObjectName(QStringLiteral("help"));
        mode = new QMenu(menuBar);
        mode->setObjectName(QStringLiteral("mode"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        adjParam = new QMenu(menuBar);
        adjParam->setObjectName(QStringLiteral("adjParam"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(file->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(mode->menuAction());
        menuBar->addAction(adjParam->menuAction());
        menuBar->addAction(help->menuAction());
        file->addAction(openFile);
        file->addAction(remove);
        file->addAction(removeAll);
        help->addAction(helper);
        help->addAction(aboutUs);
        mode->addAction(mode0);
        mode->addAction(mode1);
        mode->addAction(mode2);
        mode->addAction(mode3);
        mode->addAction(mode4);
        mode->addAction(mode5);
        mode->addAction(mode6);
        mode->addAction(mode7);
        mode->addAction(mode8);
        menu->addAction(generate);
        menu->addAction(viewResult);
        menu->addAction(saveResult);
        adjParam->addAction(inputParam);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\244\344\272\222\345\274\217\346\225\260\345\255\227\350\222\231\345\244\252\345\245\207", Q_NULLPTR));
        openFile->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\345\233\276\347\211\207", Q_NULLPTR));
        generate->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\345\233\276\345\203\217", Q_NULLPTR));
        helper->setText(QApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", Q_NULLPTR));
        aboutUs->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216\346\210\221\344\273\254", Q_NULLPTR));
        remove->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\233\276\347\211\207", Q_NULLPTR));
        removeAll->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\205\250\351\203\250", Q_NULLPTR));
        mode0->setText(QApplication::translate("MainWindow", "USER_SPECIFY", Q_NULLPTR));
        mode1->setText(QApplication::translate("MainWindow", "MAX_LUMIN", Q_NULLPTR));
        mode2->setText(QApplication::translate("MainWindow", "MIN_LUMIN", Q_NULLPTR));
        mode3->setText(QApplication::translate("MainWindow", "ERASE", Q_NULLPTR));
        mode4->setText(QApplication::translate("MainWindow", "MAX_LIKEHOOD", Q_NULLPTR));
        mode5->setText(QApplication::translate("MainWindow", "MIN_LIKEHOOD", Q_NULLPTR));
        mode6->setText(QApplication::translate("MainWindow", "CONTRAST", Q_NULLPTR));
        mode7->setText(QApplication::translate("MainWindow", "MAX_DIFF", Q_NULLPTR));
        mode8->setText(QApplication::translate("MainWindow", "USER_SPECIFY_P", Q_NULLPTR));
        changeBase->setText(QApplication::translate("MainWindow", "\346\233\264\346\215\242\345\272\225\345\233\276", Q_NULLPTR));
        viewResult->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\347\273\223\346\236\234", Q_NULLPTR));
        saveResult->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\347\273\223\346\236\234", Q_NULLPTR));
        inputParam->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\217\202\346\225\260", Q_NULLPTR));
        file->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        mode->setTitle(QApplication::translate("MainWindow", "\346\250\241\345\274\217", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", Q_NULLPTR));
        adjParam->setTitle(QApplication::translate("MainWindow", "\350\260\203\345\217\202", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
