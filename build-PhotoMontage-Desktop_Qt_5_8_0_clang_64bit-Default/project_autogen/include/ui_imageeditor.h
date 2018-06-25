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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageEditor
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *plusBtn;
    QPushButton *minusBtn;
    QPushButton *colorBtn;
    QPushButton *clearBtn;
    QPushButton *saveBtn;

    void setupUi(QWidget *ImageEditor)
    {
        if (ImageEditor->objectName().isEmpty())
            ImageEditor->setObjectName(QStringLiteral("ImageEditor"));
        ImageEditor->setEnabled(true);
        ImageEditor->resize(394, 356);
        horizontalLayoutWidget = new QWidget(ImageEditor);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 191, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        plusBtn = new QPushButton(horizontalLayoutWidget);
        plusBtn->setObjectName(QStringLiteral("plusBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plusBtn->sizePolicy().hasHeightForWidth());
        plusBtn->setSizePolicy(sizePolicy);
        plusBtn->setMinimumSize(QSize(28, 28));
        plusBtn->setMaximumSize(QSize(28, 28));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(10);
        plusBtn->setFont(font);
        plusBtn->setStyleSheet(QStringLiteral("font: 87 18pt \"Arial\";"));

        horizontalLayout->addWidget(plusBtn);

        minusBtn = new QPushButton(horizontalLayoutWidget);
        minusBtn->setObjectName(QStringLiteral("minusBtn"));
        sizePolicy.setHeightForWidth(minusBtn->sizePolicy().hasHeightForWidth());
        minusBtn->setSizePolicy(sizePolicy);
        minusBtn->setMinimumSize(QSize(28, 28));
        minusBtn->setMaximumSize(QSize(28, 28));
        minusBtn->setStyleSheet(QStringLiteral("font: 18pt \"Arial\";"));

        horizontalLayout->addWidget(minusBtn);

        colorBtn = new QPushButton(horizontalLayoutWidget);
        colorBtn->setObjectName(QStringLiteral("colorBtn"));
        sizePolicy.setHeightForWidth(colorBtn->sizePolicy().hasHeightForWidth());
        colorBtn->setSizePolicy(sizePolicy);
        colorBtn->setMinimumSize(QSize(28, 28));
        colorBtn->setMaximumSize(QSize(28, 28));

        horizontalLayout->addWidget(colorBtn);

        clearBtn = new QPushButton(horizontalLayoutWidget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMinimumSize(QSize(40, 28));
        clearBtn->setMaximumSize(QSize(40, 28));

        horizontalLayout->addWidget(clearBtn);

        saveBtn = new QPushButton(horizontalLayoutWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setMinimumSize(QSize(40, 28));
        saveBtn->setMaximumSize(QSize(40, 28));

        horizontalLayout->addWidget(saveBtn);


        retranslateUi(ImageEditor);

        QMetaObject::connectSlotsByName(ImageEditor);
    } // setupUi

    void retranslateUi(QWidget *ImageEditor)
    {
        ImageEditor->setWindowTitle(QApplication::translate("ImageEditor", "\347\274\226\350\276\221\345\231\250", Q_NULLPTR));
        plusBtn->setText(QApplication::translate("ImageEditor", "+", Q_NULLPTR));
        minusBtn->setText(QApplication::translate("ImageEditor", "-", Q_NULLPTR));
        colorBtn->setText(QString());
        clearBtn->setText(QApplication::translate("ImageEditor", "\351\207\215\347\275\256", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("ImageEditor", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageEditor: public Ui_ImageEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEEDITOR_H
