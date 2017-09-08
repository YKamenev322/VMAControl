/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionThanks;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *addressComboBox;
    QPushButton *resetButton;
    QPushButton *eraseButton;
    QPushButton *flashButton;
    QPushButton *gotoappButton;
    QLabel *label;
    QTextEdit *textEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *waitResponseSpinBox;
    QPushButton *refreshSerialButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *baudrateComboBox;
    QPushButton *sendButton;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *requestLabel;
    QLineEdit *requestLineEdit;
    QLabel *statusLabel;
    QLabel *trafficLabel;
    QFrame *line;
    QFrame *line_2;
    QPushButton *cleanButton;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QLabel *addressesLabel2;
    QPushButton *flashAllButton;
    QLabel *addressesLabel;
    QTextEdit *failTextEdit;
    QSlider *vel1Slider;
    QSlider *vel2Slider;
    QLineEdit *timerLineEdit;
    QLabel *label_5;
    QLabel *Vel1Label;
    QLabel *Vel2Label;
    QPushButton *sendVelButton;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *adc1Label;
    QLabel *adc2Label;
    QPushButton *startButton;
    QPushButton *stopButton;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QLabel *valLabel;
    QPushButton *sendMINButton;
    QPushButton *sendNULLButton;
    QPushButton *sendMAXButton;
    QPushButton *reloadHexButton;
    QPushButton *readButton;
    QPushButton *writeButton;
    QLabel *serialPortLabel_2;
    QLineEdit *pageEdit;
    QLabel *serialPortLabel_3;
    QLineEdit *wordsEdit;
    QFrame *line_7;
    QLineEdit *word1hexEdit;
    QLabel *serialPortLabel_4;
    QLabel *serialPortLabel_5;
    QLineEdit *word1decEdit;
    QPushButton *writeAllButton;
    QLabel *serialPortLabel_6;
    QLabel *serialPortLabel_7;
    QLineEdit *word2hexEdit;
    QLineEdit *word2decEdit;
    QLineEdit *word3decEdit;
    QLineEdit *word3hexEdit;
    QLabel *serialPortLabel_8;
    QLabel *serialPortLabel_9;
    QLineEdit *word4hexEdit;
    QLineEdit *word4decEdit;
    QFrame *line_8;
    QFrame *line_9;
    QCheckBox *showCurrentBox;
    QLineEdit *nullSensorEdit;
    QLabel *label_8;
    QPushButton *startAllButton;
    QPushButton *sendMAXButton_2;
    QPushButton *sendMINButton_2;
    QPushButton *sendNULLButton_2;
    QLabel *flagLabel;
    QCheckBox *enableNetworkCheckBox;
    QFrame *line_10;
    QFrame *line_11;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(885, 561);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionThanks = new QAction(MainWindow);
        actionThanks->setObjectName(QStringLiteral("actionThanks"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 81, 157));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        addressComboBox = new QComboBox(verticalLayoutWidget);
        addressComboBox->setObjectName(QStringLiteral("addressComboBox"));
        addressComboBox->setEnabled(true);
        addressComboBox->setSizeIncrement(QSize(0, 0));
        addressComboBox->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(addressComboBox);

        resetButton = new QPushButton(verticalLayoutWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        verticalLayout->addWidget(resetButton);

        eraseButton = new QPushButton(verticalLayoutWidget);
        eraseButton->setObjectName(QStringLiteral("eraseButton"));

        verticalLayout->addWidget(eraseButton);

        flashButton = new QPushButton(verticalLayoutWidget);
        flashButton->setObjectName(QStringLiteral("flashButton"));

        verticalLayout->addWidget(flashButton);

        gotoappButton = new QPushButton(verticalLayoutWidget);
        gotoappButton->setObjectName(QStringLiteral("gotoappButton"));

        verticalLayout->addWidget(gotoappButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 460, 681, 16));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(490, 0, 391, 281));
        textEdit->setMouseTracking(true);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(280, 0, 81, 47));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        serialPortLabel = new QLabel(verticalLayoutWidget_2);
        serialPortLabel->setObjectName(QStringLiteral("serialPortLabel"));

        verticalLayout_2->addWidget(serialPortLabel);

        serialPortComboBox = new QComboBox(verticalLayoutWidget_2);
        serialPortComboBox->setObjectName(QStringLiteral("serialPortComboBox"));

        verticalLayout_2->addWidget(serialPortComboBox);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(280, 140, 151, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        waitResponseSpinBox = new QSpinBox(horizontalLayoutWidget_2);
        waitResponseSpinBox->setObjectName(QStringLiteral("waitResponseSpinBox"));

        horizontalLayout_2->addWidget(waitResponseSpinBox);

        refreshSerialButton = new QPushButton(centralWidget);
        refreshSerialButton->setObjectName(QStringLiteral("refreshSerialButton"));
        refreshSerialButton->setGeometry(QRect(360, 0, 71, 23));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(280, 50, 151, 25));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        baudrateComboBox = new QComboBox(horizontalLayoutWidget);
        baudrateComboBox->setObjectName(QStringLiteral("baudrateComboBox"));

        horizontalLayout->addWidget(baudrateComboBox);

        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(339, 210, 75, 23));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(280, 170, 191, 41));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        requestLabel = new QLabel(verticalLayoutWidget_3);
        requestLabel->setObjectName(QStringLiteral("requestLabel"));

        verticalLayout_3->addWidget(requestLabel);

        requestLineEdit = new QLineEdit(verticalLayoutWidget_3);
        requestLineEdit->setObjectName(QStringLiteral("requestLineEdit"));

        verticalLayout_3->addWidget(requestLineEdit);

        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(10, 230, 411, 16));
        trafficLabel = new QLabel(centralWidget);
        trafficLabel->setObjectName(QStringLiteral("trafficLabel"));
        trafficLabel->setGeometry(QRect(490, 290, 291, 41));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(260, 0, 20, 161));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 150, 271, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        cleanButton = new QPushButton(centralWidget);
        cleanButton->setObjectName(QStringLiteral("cleanButton"));
        cleanButton->setGeometry(QRect(810, 280, 75, 23));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setEnabled(false);
        connectButton->setGeometry(QRect(440, 0, 51, 23));
        connectButton->setAutoFillBackground(false);
        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));
        disconnectButton->setGeometry(QRect(360, 20, 71, 23));
        addressesLabel2 = new QLabel(centralWidget);
        addressesLabel2->setObjectName(QStringLiteral("addressesLabel2"));
        addressesLabel2->setGeometry(QRect(0, 161, 109, 13));
        flashAllButton = new QPushButton(centralWidget);
        flashAllButton->setObjectName(QStringLiteral("flashAllButton"));
        flashAllButton->setGeometry(QRect(0, 200, 82, 23));
        addressesLabel = new QLabel(centralWidget);
        addressesLabel->setObjectName(QStringLiteral("addressesLabel"));
        addressesLabel->setGeometry(QRect(0, 180, 141, 21));
        failTextEdit = new QTextEdit(centralWidget);
        failTextEdit->setObjectName(QStringLiteral("failTextEdit"));
        failTextEdit->setGeometry(QRect(670, 340, 211, 91));
        vel1Slider = new QSlider(centralWidget);
        vel1Slider->setObjectName(QStringLiteral("vel1Slider"));
        vel1Slider->setGeometry(QRect(60, 290, 160, 19));
        vel1Slider->setMouseTracking(false);
        vel1Slider->setAutoFillBackground(true);
        vel1Slider->setMinimum(-127);
        vel1Slider->setMaximum(128);
        vel1Slider->setTracking(true);
        vel1Slider->setOrientation(Qt::Horizontal);
        vel2Slider = new QSlider(centralWidget);
        vel2Slider->setObjectName(QStringLiteral("vel2Slider"));
        vel2Slider->setGeometry(QRect(60, 340, 160, 19));
        vel2Slider->setMinimum(-127);
        vel2Slider->setMaximum(128);
        vel2Slider->setOrientation(Qt::Horizontal);
        timerLineEdit = new QLineEdit(centralWidget);
        timerLineEdit->setObjectName(QStringLiteral("timerLineEdit"));
        timerLineEdit->setGeometry(QRect(100, 380, 41, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 380, 51, 23));
        Vel1Label = new QLabel(centralWidget);
        Vel1Label->setObjectName(QStringLiteral("Vel1Label"));
        Vel1Label->setGeometry(QRect(230, 290, 31, 16));
        Vel2Label = new QLabel(centralWidget);
        Vel2Label->setObjectName(QStringLiteral("Vel2Label"));
        Vel2Label->setGeometry(QRect(230, 340, 31, 16));
        sendVelButton = new QPushButton(centralWidget);
        sendVelButton->setObjectName(QStringLiteral("sendVelButton"));
        sendVelButton->setGeometry(QRect(210, 380, 41, 23));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 290, 41, 23));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 340, 41, 23));
        adc1Label = new QLabel(centralWidget);
        adc1Label->setObjectName(QStringLiteral("adc1Label"));
        adc1Label->setGeometry(QRect(270, 290, 31, 16));
        adc2Label = new QLabel(centralWidget);
        adc2Label->setObjectName(QStringLiteral("adc2Label"));
        adc2Label->setGeometry(QRect(270, 340, 31, 16));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(150, 380, 51, 23));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(150, 410, 51, 23));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 250, 301, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(10, 430, 301, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(0, 260, 20, 181));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(300, 260, 20, 181));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        valLabel = new QLabel(centralWidget);
        valLabel->setObjectName(QStringLiteral("valLabel"));
        valLabel->setGeometry(QRect(260, 410, 31, 16));
        sendMINButton = new QPushButton(centralWidget);
        sendMINButton->setObjectName(QStringLiteral("sendMINButton"));
        sendMINButton->setGeometry(QRect(80, 260, 31, 23));
        sendNULLButton = new QPushButton(centralWidget);
        sendNULLButton->setObjectName(QStringLiteral("sendNULLButton"));
        sendNULLButton->setGeometry(QRect(120, 260, 31, 23));
        sendMAXButton = new QPushButton(centralWidget);
        sendMAXButton->setObjectName(QStringLiteral("sendMAXButton"));
        sendMAXButton->setGeometry(QRect(160, 260, 31, 23));
        reloadHexButton = new QPushButton(centralWidget);
        reloadHexButton->setObjectName(QStringLiteral("reloadHexButton"));
        reloadHexButton->setGeometry(QRect(0, 480, 61, 23));
        readButton = new QPushButton(centralWidget);
        readButton->setObjectName(QStringLiteral("readButton"));
        readButton->setGeometry(QRect(90, 130, 79, 23));
        writeButton = new QPushButton(centralWidget);
        writeButton->setObjectName(QStringLiteral("writeButton"));
        writeButton->setEnabled(false);
        writeButton->setGeometry(QRect(170, 130, 79, 23));
        serialPortLabel_2 = new QLabel(centralWidget);
        serialPortLabel_2->setObjectName(QStringLiteral("serialPortLabel_2"));
        serialPortLabel_2->setGeometry(QRect(90, 0, 31, 19));
        pageEdit = new QLineEdit(centralWidget);
        pageEdit->setObjectName(QStringLiteral("pageEdit"));
        pageEdit->setGeometry(QRect(90, 20, 21, 20));
        serialPortLabel_3 = new QLabel(centralWidget);
        serialPortLabel_3->setObjectName(QStringLiteral("serialPortLabel_3"));
        serialPortLabel_3->setGeometry(QRect(90, 40, 41, 19));
        wordsEdit = new QLineEdit(centralWidget);
        wordsEdit->setObjectName(QStringLiteral("wordsEdit"));
        wordsEdit->setGeometry(QRect(90, 60, 21, 20));
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(120, 0, 20, 111));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        word1hexEdit = new QLineEdit(centralWidget);
        word1hexEdit->setObjectName(QStringLiteral("word1hexEdit"));
        word1hexEdit->setGeometry(QRect(180, 20, 41, 20));
        serialPortLabel_4 = new QLabel(centralWidget);
        serialPortLabel_4->setObjectName(QStringLiteral("serialPortLabel_4"));
        serialPortLabel_4->setGeometry(QRect(190, 0, 31, 19));
        serialPortLabel_5 = new QLabel(centralWidget);
        serialPortLabel_5->setObjectName(QStringLiteral("serialPortLabel_5"));
        serialPortLabel_5->setGeometry(QRect(230, 0, 31, 19));
        word1decEdit = new QLineEdit(centralWidget);
        word1decEdit->setObjectName(QStringLiteral("word1decEdit"));
        word1decEdit->setEnabled(false);
        word1decEdit->setGeometry(QRect(220, 20, 41, 20));
        writeAllButton = new QPushButton(centralWidget);
        writeAllButton->setObjectName(QStringLiteral("writeAllButton"));
        writeAllButton->setEnabled(false);
        writeAllButton->setGeometry(QRect(90, 200, 79, 23));
        serialPortLabel_6 = new QLabel(centralWidget);
        serialPortLabel_6->setObjectName(QStringLiteral("serialPortLabel_6"));
        serialPortLabel_6->setGeometry(QRect(140, 20, 31, 19));
        serialPortLabel_7 = new QLabel(centralWidget);
        serialPortLabel_7->setObjectName(QStringLiteral("serialPortLabel_7"));
        serialPortLabel_7->setGeometry(QRect(140, 40, 31, 19));
        word2hexEdit = new QLineEdit(centralWidget);
        word2hexEdit->setObjectName(QStringLiteral("word2hexEdit"));
        word2hexEdit->setGeometry(QRect(180, 40, 41, 20));
        word2decEdit = new QLineEdit(centralWidget);
        word2decEdit->setObjectName(QStringLiteral("word2decEdit"));
        word2decEdit->setEnabled(false);
        word2decEdit->setGeometry(QRect(220, 40, 41, 20));
        word3decEdit = new QLineEdit(centralWidget);
        word3decEdit->setObjectName(QStringLiteral("word3decEdit"));
        word3decEdit->setEnabled(false);
        word3decEdit->setGeometry(QRect(220, 60, 41, 20));
        word3hexEdit = new QLineEdit(centralWidget);
        word3hexEdit->setObjectName(QStringLiteral("word3hexEdit"));
        word3hexEdit->setGeometry(QRect(180, 60, 41, 20));
        serialPortLabel_8 = new QLabel(centralWidget);
        serialPortLabel_8->setObjectName(QStringLiteral("serialPortLabel_8"));
        serialPortLabel_8->setGeometry(QRect(140, 60, 31, 19));
        serialPortLabel_9 = new QLabel(centralWidget);
        serialPortLabel_9->setObjectName(QStringLiteral("serialPortLabel_9"));
        serialPortLabel_9->setGeometry(QRect(140, 80, 31, 19));
        word4hexEdit = new QLineEdit(centralWidget);
        word4hexEdit->setObjectName(QStringLiteral("word4hexEdit"));
        word4hexEdit->setGeometry(QRect(180, 80, 41, 20));
        word4decEdit = new QLineEdit(centralWidget);
        word4decEdit->setObjectName(QStringLiteral("word4decEdit"));
        word4decEdit->setEnabled(false);
        word4decEdit->setGeometry(QRect(220, 80, 41, 20));
        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(70, 0, 20, 161));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(centralWidget);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(80, 100, 191, 20));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        showCurrentBox = new QCheckBox(centralWidget);
        showCurrentBox->setObjectName(QStringLiteral("showCurrentBox"));
        showCurrentBox->setGeometry(QRect(250, 270, 70, 17));
        showCurrentBox->setChecked(true);
        nullSensorEdit = new QLineEdit(centralWidget);
        nullSensorEdit->setObjectName(QStringLiteral("nullSensorEdit"));
        nullSensorEdit->setGeometry(QRect(100, 410, 41, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 410, 71, 23));
        startAllButton = new QPushButton(centralWidget);
        startAllButton->setObjectName(QStringLiteral("startAllButton"));
        startAllButton->setGeometry(QRect(210, 410, 41, 23));
        sendMAXButton_2 = new QPushButton(centralWidget);
        sendMAXButton_2->setObjectName(QStringLiteral("sendMAXButton_2"));
        sendMAXButton_2->setGeometry(QRect(160, 310, 31, 23));
        sendMINButton_2 = new QPushButton(centralWidget);
        sendMINButton_2->setObjectName(QStringLiteral("sendMINButton_2"));
        sendMINButton_2->setGeometry(QRect(80, 310, 31, 23));
        sendNULLButton_2 = new QPushButton(centralWidget);
        sendNULLButton_2->setObjectName(QStringLiteral("sendNULLButton_2"));
        sendNULLButton_2->setGeometry(QRect(120, 310, 31, 23));
        flagLabel = new QLabel(centralWidget);
        flagLabel->setObjectName(QStringLiteral("flagLabel"));
        flagLabel->setGeometry(QRect(260, 380, 31, 16));
        enableNetworkCheckBox = new QCheckBox(centralWidget);
        enableNetworkCheckBox->setObjectName(QStringLiteral("enableNetworkCheckBox"));
        enableNetworkCheckBox->setGeometry(QRect(280, 100, 91, 17));
        enableNetworkCheckBox->setChecked(false);
        line_10 = new QFrame(centralWidget);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setGeometry(QRect(280, 80, 211, 16));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        line_11 = new QFrame(centralWidget);
        line_11->setObjectName(QStringLiteral("line_11"));
        line_11->setGeometry(QRect(280, 130, 211, 16));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 885, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(vel1Slider, SIGNAL(valueChanged(int)), Vel1Label, SLOT(setNum(int)));
        QObject::connect(vel2Slider, SIGNAL(valueChanged(int)), Vel2Label, SLOT(setNum(int)));

        baudrateComboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionThanks->setText(QApplication::translate("MainWindow", "Thanks..", 0));
        label_2->setText(QApplication::translate("MainWindow", "Slave's address", 0));
        resetButton->setText(QApplication::translate("MainWindow", "Reset in Boot", 0));
        eraseButton->setText(QApplication::translate("MainWindow", "Erase!", 0));
        flashButton->setText(QApplication::translate("MainWindow", "Flash!", 0));
        gotoappButton->setText(QApplication::translate("MainWindow", "GoToApp", 0));
        label->setText(QApplication::translate("MainWindow", "Hex file source..", 0));
        serialPortLabel->setText(QApplication::translate("MainWindow", "Com Port:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Response(ms)", 0));
        refreshSerialButton->setText(QApplication::translate("MainWindow", "Refresh", 0));
        label_4->setText(QApplication::translate("MainWindow", "Baudrate", 0));
        baudrateComboBox->clear();
        baudrateComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", 0)
         << QApplication::translate("MainWindow", "19200", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "115200", 0)
        );
        baudrateComboBox->setCurrentText(QApplication::translate("MainWindow", "57600", 0));
        sendButton->setText(QApplication::translate("MainWindow", "Send", 0));
        requestLabel->setText(QApplication::translate("MainWindow", "Enter request in Hex (01 4f 3a ..):", 0));
        statusLabel->setText(QApplication::translate("MainWindow", "Status:", 0));
        trafficLabel->setText(QApplication::translate("MainWindow", "Traffic...", 0));
        cleanButton->setText(QApplication::translate("MainWindow", "Clean", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Conn", 0));
        disconnectButton->setText(QApplication::translate("MainWindow", "DisConnect", 0));
        addressesLabel2->setText(QApplication::translate("MainWindow", "Slave's addresses:", 0));
        flashAllButton->setText(QApplication::translate("MainWindow", "Flash All!", 0));
        addressesLabel->setText(QApplication::translate("MainWindow", "-", 0));
        timerLineEdit->setText(QApplication::translate("MainWindow", "100", 0));
        label_5->setText(QApplication::translate("MainWindow", "Time, ms", 0));
        Vel1Label->setText(QApplication::translate("MainWindow", "V1", 0));
        Vel2Label->setText(QApplication::translate("MainWindow", "V2", 0));
        sendVelButton->setText(QApplication::translate("MainWindow", "Send", 0));
        label_6->setText(QApplication::translate("MainWindow", "VMA Vel", 0));
        label_7->setText(QApplication::translate("MainWindow", "ADD Vel", 0));
        adc1Label->setText(QApplication::translate("MainWindow", "ADC1", 0));
        adc2Label->setText(QApplication::translate("MainWindow", "ADC2", 0));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        valLabel->setText(QApplication::translate("MainWindow", "Vels", 0));
        sendMINButton->setText(QApplication::translate("MainWindow", "MIN", 0));
        sendNULLButton->setText(QApplication::translate("MainWindow", "NULL", 0));
        sendMAXButton->setText(QApplication::translate("MainWindow", "MAX", 0));
        reloadHexButton->setText(QApplication::translate("MainWindow", "ReloadHex", 0));
        readButton->setText(QApplication::translate("MainWindow", "ReadData", 0));
        writeButton->setText(QApplication::translate("MainWindow", "WriteData", 0));
        serialPortLabel_2->setText(QApplication::translate("MainWindow", "Page:", 0));
        pageEdit->setInputMask(QString());
        pageEdit->setText(QApplication::translate("MainWindow", "24", 0));
        serialPortLabel_3->setText(QApplication::translate("MainWindow", "Words:", 0));
        wordsEdit->setText(QApplication::translate("MainWindow", "4", 0));
        word1hexEdit->setText(QApplication::translate("MainWindow", "0", 0));
        serialPortLabel_4->setText(QApplication::translate("MainWindow", "Hex", 0));
        serialPortLabel_5->setText(QApplication::translate("MainWindow", "Dec", 0));
        word1decEdit->setText(QApplication::translate("MainWindow", "0", 0));
        writeAllButton->setText(QApplication::translate("MainWindow", "Write All!", 0));
        serialPortLabel_6->setText(QApplication::translate("MainWindow", "W1", 0));
        serialPortLabel_7->setText(QApplication::translate("MainWindow", "W2", 0));
        word2hexEdit->setText(QApplication::translate("MainWindow", "0", 0));
        word2decEdit->setText(QApplication::translate("MainWindow", "0", 0));
        word3decEdit->setText(QApplication::translate("MainWindow", "0", 0));
        word3hexEdit->setText(QApplication::translate("MainWindow", "0", 0));
        serialPortLabel_8->setText(QApplication::translate("MainWindow", "W3", 0));
        serialPortLabel_9->setText(QApplication::translate("MainWindow", "W4", 0));
        word4hexEdit->setText(QApplication::translate("MainWindow", "0", 0));
        word4decEdit->setText(QApplication::translate("MainWindow", "0", 0));
        showCurrentBox->setText(QApplication::translate("MainWindow", "Ampers", 0));
        nullSensorEdit->setInputMask(QString());
        nullSensorEdit->setText(QApplication::translate("MainWindow", "3187", 0));
        label_8->setText(QApplication::translate("MainWindow", "NULL ACS712", 0));
        startAllButton->setText(QApplication::translate("MainWindow", "StartAll", 0));
        sendMAXButton_2->setText(QApplication::translate("MainWindow", "MAX", 0));
        sendMINButton_2->setText(QApplication::translate("MainWindow", "MIN", 0));
        sendNULLButton_2->setText(QApplication::translate("MainWindow", "NULL", 0));
        flagLabel->setText(QApplication::translate("MainWindow", "Flag", 0));
        enableNetworkCheckBox->setText(QApplication::translate("MainWindow", "Enable TCP/IP", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
