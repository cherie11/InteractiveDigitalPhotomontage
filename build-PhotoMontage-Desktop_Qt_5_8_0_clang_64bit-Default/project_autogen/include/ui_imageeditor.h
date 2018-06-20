/********************************************************************************
** Form generated from reading UI file 'imageeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEEDITOR_H
#define UI_IMAGEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageEditor
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveBtn;
    QPushButton *clearBtn;
    QPushButton *colorBtn;
    QLabel *label;
    QSpinBox *widthSpinBox;

    void setupUi(QWidget *ImageEditor)
    {
        if (ImageEditor->objectName().isEmpty())
            ImageEditor->setObjectName(QStringLiteral("ImageEditor"));
        ImageEditor->setEnabled(true);
        ImageEditor->resize(394, 356);
        horizontalLayoutWidget = new QWidget(ImageEditor);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 193, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        saveBtn = new QPushButton(horizontalLayoutWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setMinimumSize(QSize(28, 28));
        saveBtn->setMaximumSize(QSize(28, 28));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/src/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveBtn->setIcon(icon);

        horizontalLayout->addWidget(saveBtn);

        clearBtn = new QPushButton(horizontalLayoutWidget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMinimumSize(QSize(28, 28));
        clearBtn->setMaximumSize(QSize(28, 28));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/src/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearBtn->setIcon(icon1);

        horizontalLayout->addWidget(clearBtn);

        colorBtn = new QPushButton(horizontalLayoutWidget);
        colorBtn->setObjectName(QStringLiteral("colorBtn"));
        colorBtn->setMinimumSize(QSize(28, 28));
        colorBtn->setMaximumSize(QSize(28, 28));

        horizontalLayout->addWidget(colorBtn);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(39, 28));
        label->setMaximumSize(QSize(39, 28));
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        widthSpinBox = new QSpinBox(horizontalLayoutWidget);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setMinimumSize(QSize(40, 22));
        widthSpinBox->setMaximumSize(QSize(40, 22));
        widthSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widthSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        widthSpinBox->setMinimum(1);
        widthSpinBox->setMaximum(30);
        widthSpinBox->setValue(8);

        horizontalLayout->addWidget(widthSpinBox);


        retranslateUi(ImageEditor);

        QMetaObject::connectSlotsByName(ImageEditor);
    } // setupUi

    void retranslateUi(QWidget *ImageEditor)
    {
        ImageEditor->setWindowTitle(QApplication::translate("ImageEditor", "\347\274\226\350\276\221\345\231\250", Q_NULLPTR));
        saveBtn->setText(QString());
        clearBtn->setText(QString());
        colorBtn->setText(QString());
        label->setText(QApplication::translate("ImageEditor", "\347\272\277\345\256\275\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageEditor: public Ui_ImageEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEEDITOR_H
