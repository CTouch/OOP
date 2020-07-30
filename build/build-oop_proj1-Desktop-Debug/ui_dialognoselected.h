/********************************************************************************
** Form generated from reading UI file 'dialognoselected.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNOSELECTED_H
#define UI_DIALOGNOSELECTED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogNoSelected
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QDialog *DialogNoSelected)
    {
        if (DialogNoSelected->objectName().isEmpty())
            DialogNoSelected->setObjectName(QString::fromUtf8("DialogNoSelected"));
        DialogNoSelected->resize(400, 300);
        buttonBox = new QDialogButtonBox(DialogNoSelected);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(DialogNoSelected);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 90, 382, 29));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(DialogNoSelected);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogNoSelected, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogNoSelected, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogNoSelected);
    } // setupUi

    void retranslateUi(QDialog *DialogNoSelected)
    {
        DialogNoSelected->setWindowTitle(QCoreApplication::translate("DialogNoSelected", "Error", nullptr));
        label->setText(QCoreApplication::translate("DialogNoSelected", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:600;\">You have not selected any layer!</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogNoSelected: public Ui_DialogNoSelected {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNOSELECTED_H
