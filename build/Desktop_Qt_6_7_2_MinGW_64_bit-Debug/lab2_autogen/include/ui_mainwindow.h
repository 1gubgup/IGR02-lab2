/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *ColorLabel;
    QPushButton *redButton;
    QPushButton *blueButton;
    QPushButton *greenButton;
    QPushButton *yellowButton;
    QLabel *thicknessLabel;
    QSlider *thicknessSlider;
    QLabel *styleLabel;
    QRadioButton *solidButton;
    QRadioButton *dashButton;
    QRadioButton *dotButton;
    QLabel *shapeLabel;
    QRadioButton *lineButton;
    QRadioButton *rectangleButton;
    QRadioButton *ellipseButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setMinimumSize(QSize(120, 400));
        dockWidget->setMaximumSize(QSize(120, 1000));
        dockWidget->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::DockWidgetArea::NoDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(dockWidgetContents);
        widget->setObjectName("widget");
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 91, 417));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ColorLabel = new QLabel(verticalLayoutWidget);
        ColorLabel->setObjectName("ColorLabel");
        QFont font;
        font.setPointSize(9);
        ColorLabel->setFont(font);
        ColorLabel->setLineWidth(1);
        ColorLabel->setMidLineWidth(0);

        verticalLayout->addWidget(ColorLabel);

        redButton = new QPushButton(verticalLayoutWidget);
        redButton->setObjectName("redButton");
        redButton->setMinimumSize(QSize(45, 20));
        redButton->setMaximumSize(QSize(45, 20));
        redButton->setStyleSheet(QString::fromUtf8(""));
        redButton->setCheckable(true);
        redButton->setChecked(true);

        verticalLayout->addWidget(redButton);

        blueButton = new QPushButton(verticalLayoutWidget);
        blueButton->setObjectName("blueButton");
        blueButton->setMinimumSize(QSize(45, 20));
        blueButton->setMaximumSize(QSize(45, 20));
        blueButton->setStyleSheet(QString::fromUtf8(""));
        blueButton->setCheckable(true);

        verticalLayout->addWidget(blueButton);

        greenButton = new QPushButton(verticalLayoutWidget);
        greenButton->setObjectName("greenButton");
        greenButton->setMinimumSize(QSize(45, 20));
        greenButton->setMaximumSize(QSize(45, 20));
        greenButton->setStyleSheet(QString::fromUtf8(""));
        greenButton->setCheckable(true);

        verticalLayout->addWidget(greenButton);

        yellowButton = new QPushButton(verticalLayoutWidget);
        yellowButton->setObjectName("yellowButton");
        yellowButton->setMinimumSize(QSize(45, 20));
        yellowButton->setMaximumSize(QSize(45, 20));
        yellowButton->setStyleSheet(QString::fromUtf8(""));
        yellowButton->setCheckable(true);

        verticalLayout->addWidget(yellowButton);

        thicknessLabel = new QLabel(verticalLayoutWidget);
        thicknessLabel->setObjectName("thicknessLabel");
        thicknessLabel->setFont(font);

        verticalLayout->addWidget(thicknessLabel);

        thicknessSlider = new QSlider(verticalLayoutWidget);
        thicknessSlider->setObjectName("thicknessSlider");
        thicknessSlider->setMinimum(5);
        thicknessSlider->setMaximum(15);
        thicknessSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout->addWidget(thicknessSlider);

        styleLabel = new QLabel(verticalLayoutWidget);
        styleLabel->setObjectName("styleLabel");
        styleLabel->setFont(font);

        verticalLayout->addWidget(styleLabel);

        solidButton = new QRadioButton(verticalLayoutWidget);
        solidButton->setObjectName("solidButton");
        solidButton->setChecked(false);

        verticalLayout->addWidget(solidButton);

        dashButton = new QRadioButton(verticalLayoutWidget);
        dashButton->setObjectName("dashButton");

        verticalLayout->addWidget(dashButton);

        dotButton = new QRadioButton(verticalLayoutWidget);
        dotButton->setObjectName("dotButton");

        verticalLayout->addWidget(dotButton);

        shapeLabel = new QLabel(verticalLayoutWidget);
        shapeLabel->setObjectName("shapeLabel");

        verticalLayout->addWidget(shapeLabel);

        lineButton = new QRadioButton(verticalLayoutWidget);
        lineButton->setObjectName("lineButton");
        lineButton->setFont(font);
        lineButton->setChecked(true);

        verticalLayout->addWidget(lineButton);

        rectangleButton = new QRadioButton(verticalLayoutWidget);
        rectangleButton->setObjectName("rectangleButton");

        verticalLayout->addWidget(rectangleButton);

        ellipseButton = new QRadioButton(verticalLayoutWidget);
        ellipseButton->setObjectName("ellipseButton");

        verticalLayout->addWidget(ellipseButton);


        horizontalLayout->addWidget(widget);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Drawing Tools", nullptr));
        ColorLabel->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        redButton->setText(QCoreApplication::translate("MainWindow", "red", nullptr));
        blueButton->setText(QCoreApplication::translate("MainWindow", "blue", nullptr));
        greenButton->setText(QCoreApplication::translate("MainWindow", "green", nullptr));
        yellowButton->setText(QCoreApplication::translate("MainWindow", "yellow", nullptr));
        thicknessLabel->setText(QCoreApplication::translate("MainWindow", "Thickness", nullptr));
        styleLabel->setText(QCoreApplication::translate("MainWindow", "Style", nullptr));
        solidButton->setText(QCoreApplication::translate("MainWindow", "Solid Line", nullptr));
        dashButton->setText(QCoreApplication::translate("MainWindow", "Dash Line", nullptr));
        dotButton->setText(QCoreApplication::translate("MainWindow", "Dot Line", nullptr));
        shapeLabel->setText(QCoreApplication::translate("MainWindow", "Shape", nullptr));
        lineButton->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        rectangleButton->setText(QCoreApplication::translate("MainWindow", "Rectangle", nullptr));
        ellipseButton->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
