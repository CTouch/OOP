/********************************************************************************
** Form generated from reading UI file 'dialogchecktosave.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHECKTOSAVE_H
#define UI_DIALOGCHECKTOSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogChecktoSave
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonSave;
    QPushButton *buttonNottoSave;
    QPushButton *buttonCancel;

    void setupUi(QDialog *DialogChecktoSave)
    {
        if (DialogChecktoSave->objectName().isEmpty())
            DialogChecktoSave->setObjectName(QString::fromUtf8("DialogChecktoSave"));
        DialogChecktoSave->resize(400, 300);
        verticalLayoutWidget = new QWidget(DialogChecktoSave);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(70, 70, 261, 111));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayoutWidget = new QWidget(DialogChecktoSave);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(100, 210, 293, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        buttonSave = new QPushButton(horizontalLayoutWidget);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));

        horizontalLayout->addWidget(buttonSave);

        buttonNottoSave = new QPushButton(horizontalLayoutWidget);
        buttonNottoSave->setObjectName(QString::fromUtf8("buttonNottoSave"));

        horizontalLayout->addWidget(buttonNottoSave);

        buttonCancel = new QPushButton(horizontalLayoutWidget);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        horizontalLayout->addWidget(buttonCancel);


        retranslateUi(DialogChecktoSave);

        QMetaObject::connectSlotsByName(DialogChecktoSave);
    } // setupUi

    void retranslateUi(QDialog *DialogChecktoSave)
    {
        DialogChecktoSave->setWindowTitle(QCoreApplication::translate("DialogChecktoSave", "Note", nullptr));
        label->setText(QCoreApplication::translate("DialogChecktoSave", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600;\">There are unsaved changes</span></p></body></html>", nullptr));
        buttonSave->setText(QCoreApplication::translate("DialogChecktoSave", "Save", nullptr));
        buttonNottoSave->setText(QCoreApplication::translate("DialogChecktoSave", "Not to Save", nullptr));
        buttonCancel->setText(QCoreApplication::translate("DialogChecktoSave", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogChecktoSave: public Ui_DialogChecktoSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHECKTOSAVE_H
