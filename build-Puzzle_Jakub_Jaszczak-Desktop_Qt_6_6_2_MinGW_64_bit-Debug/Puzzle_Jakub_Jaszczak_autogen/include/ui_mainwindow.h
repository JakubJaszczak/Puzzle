/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *numberOfCells_label;
    QSpinBox *sB_numberOfCells;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *l_logger_label;
    QLabel *l_logger;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(610, 30, 160, 201));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 0, 10, 0);
        numberOfCells_label = new QLabel(verticalLayoutWidget);
        numberOfCells_label->setObjectName("numberOfCells_label");
        numberOfCells_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(numberOfCells_label);

        sB_numberOfCells = new QSpinBox(verticalLayoutWidget);
        sB_numberOfCells->setObjectName("sB_numberOfCells");
        sB_numberOfCells->setMinimum(3);
        sB_numberOfCells->setMaximum(9);

        verticalLayout->addWidget(sB_numberOfCells);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        l_logger_label = new QLabel(verticalLayoutWidget);
        l_logger_label->setObjectName("l_logger_label");

        verticalLayout->addWidget(l_logger_label);

        l_logger = new QLabel(verticalLayoutWidget);
        l_logger->setObjectName("l_logger");

        verticalLayout->addWidget(l_logger);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        numberOfCells_label->setText(QCoreApplication::translate("MainWindow", "Number of cells: n", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        l_logger_label->setText(QCoreApplication::translate("MainWindow", "Logger:", nullptr));
        l_logger->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
