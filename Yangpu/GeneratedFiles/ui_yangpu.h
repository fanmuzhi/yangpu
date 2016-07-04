/********************************************************************************
** Form generated from reading UI file 'yangpu.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YANGPU_H
#define UI_YANGPU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_YangpuClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionSave;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QGroupBox *BasicInfoGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *SerialNumberLabel;
    QLineEdit *SerialNumberLineEdit;
    QLabel *SoftwareVersionLabel;
    QLineEdit *SoftwareVersionLineEdit;
    QLabel *ConfigFileLabel;
    QLineEdit *ConfigFileLineEdit;
    QTextBrowser *textBrowser;
    QGroupBox *SignalGroupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *SNRTagLabel;
    QLabel *Zone1NameLabel;
    QLabel *Zone2NameLabel;
    QLabel *Zone3NameLabel;
    QLabel *Zone4NameLabel;
    QLabel *Zone5NameLabel;
    QLabel *Zone6NameLabel;
    QLabel *ZoneOverAllNameLabel;
    QVBoxLayout *verticalLayout_4;
    QLabel *SignalLabel;
    QLabel *SignalZone1ValueLabel;
    QLabel *SignalZone2ValueLabel;
    QLabel *SignalZone3ValueLabel;
    QLabel *SignalZone4ValueLabel;
    QLabel *SignalZone5ValueLabel;
    QLabel *SignalZone6ValueLabel;
    QLabel *SignalOverAllValueLabel;
    QVBoxLayout *verticalLayout_3;
    QLabel *NoiseLabel;
    QLabel *NoiseZone1ValueLabel;
    QLabel *NoiseZone2ValueLabel;
    QLabel *NoiseZone3ValueLabel;
    QLabel *NoiseZone4ValueLabel;
    QLabel *NoiseZone5ValueLabel;
    QLabel *NoiseZone6ValueLabel;
    QLabel *NoiseOverAllValueLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *SNRLabel;
    QLabel *SNRZone1ValueLabel;
    QLabel *SNRZone2ValueLabel;
    QLabel *SNRZone3ValueLabel;
    QLabel *SNRZone4ValueLabel;
    QLabel *SNRZone5ValueLabel;
    QLabel *SNRZone6ValueLabel;
    QLabel *SNROverAllValueLabel;
    QGroupBox *SharpnessGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *SharpnesZone1Label;
    QLabel *SharpnesZone1ValueLabel;
    QLabel *SharpnesZone2Label;
    QLabel *SharpnesZone2ValueLabel;
    QLabel *SharpnesZone3Label;
    QLabel *SharpnesZone3ValueLabel;
    QLabel *SharpnesOverAllLabel;
    QLabel *SharpnesOverAllValueLabel;
    QGroupBox *SCMWOFGroupBox;
    QGridLayout *gridLayout_8;
    QLabel *SCMWOFLabel;
    QLabel *SCMWOFNoFingerLabel;
    QLabel *SCMWOFWithFingerLabel;
    QLabel *SCMWOFGainLabel;
    QLabel *SCMWOFDeltaLabel;
    QLabel *SCMWOFZone0Label;
    QLabel *SCMWOFZone1Label;
    QLabel *SCMWOFZone0NoFingerLabel;
    QLabel *SCMWOFZone0WithFingerLabel;
    QLabel *SCMWOFZone0GainLabel;
    QLabel *SCMWOFZone0DeltaLabel;
    QLabel *SCMWOFZone1NoFingerLabel;
    QLabel *SCMWOFZone1WithFingerLabel;
    QLabel *SCMWOFZone1GainLabel;
    QLabel *SCMWOFZone1DeltaLabel;
    QGroupBox *FakeFingerGroupBox;
    QGridLayout *gridLayout_7;
    QLabel *FakeFingerLabel;
    QGroupBox *WOFGroupBox;
    QGridLayout *gridLayout_4;
    QLabel *WOFTagLabel;
    QLabel *WOFNoFingerLabel;
    QLabel *WOFWithFingerLabel;
    QLabel *WOFGainLabel;
    QLabel *WOFDeltaLabel;
    QLabel *WOFZone0FDLabel;
    QLabel *WOFZone0FDNoFingerLabel;
    QLabel *WOFZone0FDWithFingerLabel;
    QLabel *WOFZone0FDGainLabel;
    QLabel *WOFZone0FDDeltaLabel;
    QLabel *WOFZone0FULabel;
    QLabel *WOFZone0FUNoFingerLabel;
    QLabel *WOFZone0FUWithFingerLabel;
    QLabel *WOFZone0FUGainLabel;
    QLabel *WOFZone0FUDeltaLabel;
    QLabel *WOFZone1FDLabel;
    QLabel *WOFZone1FDNoFingerLabel;
    QLabel *WOFZone1FDWithFingerLabel;
    QLabel *WOFZone1FDGainLabel;
    QLabel *WOFZone1FDDeltaLabel;
    QLabel *WOFZone1FULabel;
    QLabel *WOFZone1FUNoFingerLabel;
    QLabel *WOFZone1FUWithFingerLabel;
    QLabel *WOFZone1FUGainLabel;
    QLabel *WOFZone1FUDeltaLabel;
    QGroupBox *NoFingerGroupBox;
    QGridLayout *gridLayout_6;
    QLabel *NoFingerLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *YangpuClass)
    {
        if (YangpuClass->objectName().isEmpty())
            YangpuClass->setObjectName(QStringLiteral("YangpuClass"));
        YangpuClass->resize(885, 854);
        actionOpen = new QAction(YangpuClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(YangpuClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(YangpuClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(YangpuClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        BasicInfoGroupBox = new QGroupBox(tab);
        BasicInfoGroupBox->setObjectName(QStringLiteral("BasicInfoGroupBox"));
        gridLayout_2 = new QGridLayout(BasicInfoGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        SerialNumberLabel = new QLabel(BasicInfoGroupBox);
        SerialNumberLabel->setObjectName(QStringLiteral("SerialNumberLabel"));

        gridLayout_2->addWidget(SerialNumberLabel, 0, 0, 1, 1);

        SerialNumberLineEdit = new QLineEdit(BasicInfoGroupBox);
        SerialNumberLineEdit->setObjectName(QStringLiteral("SerialNumberLineEdit"));

        gridLayout_2->addWidget(SerialNumberLineEdit, 0, 1, 1, 1);

        SoftwareVersionLabel = new QLabel(BasicInfoGroupBox);
        SoftwareVersionLabel->setObjectName(QStringLiteral("SoftwareVersionLabel"));

        gridLayout_2->addWidget(SoftwareVersionLabel, 1, 0, 1, 1);

        SoftwareVersionLineEdit = new QLineEdit(BasicInfoGroupBox);
        SoftwareVersionLineEdit->setObjectName(QStringLiteral("SoftwareVersionLineEdit"));

        gridLayout_2->addWidget(SoftwareVersionLineEdit, 1, 1, 1, 1);

        ConfigFileLabel = new QLabel(BasicInfoGroupBox);
        ConfigFileLabel->setObjectName(QStringLiteral("ConfigFileLabel"));

        gridLayout_2->addWidget(ConfigFileLabel, 2, 0, 1, 1);

        ConfigFileLineEdit = new QLineEdit(BasicInfoGroupBox);
        ConfigFileLineEdit->setObjectName(QStringLiteral("ConfigFileLineEdit"));

        gridLayout_2->addWidget(ConfigFileLineEdit, 2, 1, 1, 1);

        textBrowser = new QTextBrowser(BasicInfoGroupBox);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_2->addWidget(textBrowser, 3, 0, 1, 2);


        gridLayout_5->addWidget(BasicInfoGroupBox, 0, 0, 2, 1);

        SignalGroupBox = new QGroupBox(tab);
        SignalGroupBox->setObjectName(QStringLiteral("SignalGroupBox"));
        horizontalLayout = new QHBoxLayout(SignalGroupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SNRTagLabel = new QLabel(SignalGroupBox);
        SNRTagLabel->setObjectName(QStringLiteral("SNRTagLabel"));
        SNRTagLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(SNRTagLabel);

        Zone1NameLabel = new QLabel(SignalGroupBox);
        Zone1NameLabel->setObjectName(QStringLiteral("Zone1NameLabel"));

        verticalLayout->addWidget(Zone1NameLabel);

        Zone2NameLabel = new QLabel(SignalGroupBox);
        Zone2NameLabel->setObjectName(QStringLiteral("Zone2NameLabel"));

        verticalLayout->addWidget(Zone2NameLabel);

        Zone3NameLabel = new QLabel(SignalGroupBox);
        Zone3NameLabel->setObjectName(QStringLiteral("Zone3NameLabel"));

        verticalLayout->addWidget(Zone3NameLabel);

        Zone4NameLabel = new QLabel(SignalGroupBox);
        Zone4NameLabel->setObjectName(QStringLiteral("Zone4NameLabel"));

        verticalLayout->addWidget(Zone4NameLabel);

        Zone5NameLabel = new QLabel(SignalGroupBox);
        Zone5NameLabel->setObjectName(QStringLiteral("Zone5NameLabel"));

        verticalLayout->addWidget(Zone5NameLabel);

        Zone6NameLabel = new QLabel(SignalGroupBox);
        Zone6NameLabel->setObjectName(QStringLiteral("Zone6NameLabel"));

        verticalLayout->addWidget(Zone6NameLabel);

        ZoneOverAllNameLabel = new QLabel(SignalGroupBox);
        ZoneOverAllNameLabel->setObjectName(QStringLiteral("ZoneOverAllNameLabel"));

        verticalLayout->addWidget(ZoneOverAllNameLabel);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        SignalLabel = new QLabel(SignalGroupBox);
        SignalLabel->setObjectName(QStringLiteral("SignalLabel"));
        SignalLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalLabel);

        SignalZone1ValueLabel = new QLabel(SignalGroupBox);
        SignalZone1ValueLabel->setObjectName(QStringLiteral("SignalZone1ValueLabel"));
        SignalZone1ValueLabel->setLineWidth(0);
        SignalZone1ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone1ValueLabel);

        SignalZone2ValueLabel = new QLabel(SignalGroupBox);
        SignalZone2ValueLabel->setObjectName(QStringLiteral("SignalZone2ValueLabel"));
        SignalZone2ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone2ValueLabel);

        SignalZone3ValueLabel = new QLabel(SignalGroupBox);
        SignalZone3ValueLabel->setObjectName(QStringLiteral("SignalZone3ValueLabel"));
        SignalZone3ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone3ValueLabel);

        SignalZone4ValueLabel = new QLabel(SignalGroupBox);
        SignalZone4ValueLabel->setObjectName(QStringLiteral("SignalZone4ValueLabel"));
        SignalZone4ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone4ValueLabel);

        SignalZone5ValueLabel = new QLabel(SignalGroupBox);
        SignalZone5ValueLabel->setObjectName(QStringLiteral("SignalZone5ValueLabel"));
        SignalZone5ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone5ValueLabel);

        SignalZone6ValueLabel = new QLabel(SignalGroupBox);
        SignalZone6ValueLabel->setObjectName(QStringLiteral("SignalZone6ValueLabel"));
        SignalZone6ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalZone6ValueLabel);

        SignalOverAllValueLabel = new QLabel(SignalGroupBox);
        SignalOverAllValueLabel->setObjectName(QStringLiteral("SignalOverAllValueLabel"));
        SignalOverAllValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(SignalOverAllValueLabel);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        NoiseLabel = new QLabel(SignalGroupBox);
        NoiseLabel->setObjectName(QStringLiteral("NoiseLabel"));
        NoiseLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseLabel);

        NoiseZone1ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone1ValueLabel->setObjectName(QStringLiteral("NoiseZone1ValueLabel"));
        NoiseZone1ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone1ValueLabel);

        NoiseZone2ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone2ValueLabel->setObjectName(QStringLiteral("NoiseZone2ValueLabel"));
        NoiseZone2ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone2ValueLabel);

        NoiseZone3ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone3ValueLabel->setObjectName(QStringLiteral("NoiseZone3ValueLabel"));
        NoiseZone3ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone3ValueLabel);

        NoiseZone4ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone4ValueLabel->setObjectName(QStringLiteral("NoiseZone4ValueLabel"));
        NoiseZone4ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone4ValueLabel);

        NoiseZone5ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone5ValueLabel->setObjectName(QStringLiteral("NoiseZone5ValueLabel"));
        NoiseZone5ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone5ValueLabel);

        NoiseZone6ValueLabel = new QLabel(SignalGroupBox);
        NoiseZone6ValueLabel->setObjectName(QStringLiteral("NoiseZone6ValueLabel"));
        NoiseZone6ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseZone6ValueLabel);

        NoiseOverAllValueLabel = new QLabel(SignalGroupBox);
        NoiseOverAllValueLabel->setObjectName(QStringLiteral("NoiseOverAllValueLabel"));
        NoiseOverAllValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(NoiseOverAllValueLabel);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        SNRLabel = new QLabel(SignalGroupBox);
        SNRLabel->setObjectName(QStringLiteral("SNRLabel"));
        SNRLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRLabel);

        SNRZone1ValueLabel = new QLabel(SignalGroupBox);
        SNRZone1ValueLabel->setObjectName(QStringLiteral("SNRZone1ValueLabel"));
        SNRZone1ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone1ValueLabel);

        SNRZone2ValueLabel = new QLabel(SignalGroupBox);
        SNRZone2ValueLabel->setObjectName(QStringLiteral("SNRZone2ValueLabel"));
        SNRZone2ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone2ValueLabel);

        SNRZone3ValueLabel = new QLabel(SignalGroupBox);
        SNRZone3ValueLabel->setObjectName(QStringLiteral("SNRZone3ValueLabel"));
        SNRZone3ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone3ValueLabel);

        SNRZone4ValueLabel = new QLabel(SignalGroupBox);
        SNRZone4ValueLabel->setObjectName(QStringLiteral("SNRZone4ValueLabel"));
        SNRZone4ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone4ValueLabel);

        SNRZone5ValueLabel = new QLabel(SignalGroupBox);
        SNRZone5ValueLabel->setObjectName(QStringLiteral("SNRZone5ValueLabel"));
        SNRZone5ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone5ValueLabel);

        SNRZone6ValueLabel = new QLabel(SignalGroupBox);
        SNRZone6ValueLabel->setObjectName(QStringLiteral("SNRZone6ValueLabel"));
        SNRZone6ValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNRZone6ValueLabel);

        SNROverAllValueLabel = new QLabel(SignalGroupBox);
        SNROverAllValueLabel->setObjectName(QStringLiteral("SNROverAllValueLabel"));
        SNROverAllValueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SNROverAllValueLabel);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout_5->addWidget(SignalGroupBox, 0, 1, 1, 1);

        SharpnessGroupBox = new QGroupBox(tab);
        SharpnessGroupBox->setObjectName(QStringLiteral("SharpnessGroupBox"));
        gridLayout_3 = new QGridLayout(SharpnessGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        SharpnesZone1Label = new QLabel(SharpnessGroupBox);
        SharpnesZone1Label->setObjectName(QStringLiteral("SharpnesZone1Label"));

        gridLayout_3->addWidget(SharpnesZone1Label, 0, 0, 1, 1);

        SharpnesZone1ValueLabel = new QLabel(SharpnessGroupBox);
        SharpnesZone1ValueLabel->setObjectName(QStringLiteral("SharpnesZone1ValueLabel"));
        SharpnesZone1ValueLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(SharpnesZone1ValueLabel, 0, 1, 1, 1);

        SharpnesZone2Label = new QLabel(SharpnessGroupBox);
        SharpnesZone2Label->setObjectName(QStringLiteral("SharpnesZone2Label"));

        gridLayout_3->addWidget(SharpnesZone2Label, 1, 0, 1, 1);

        SharpnesZone2ValueLabel = new QLabel(SharpnessGroupBox);
        SharpnesZone2ValueLabel->setObjectName(QStringLiteral("SharpnesZone2ValueLabel"));
        SharpnesZone2ValueLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(SharpnesZone2ValueLabel, 1, 1, 1, 1);

        SharpnesZone3Label = new QLabel(SharpnessGroupBox);
        SharpnesZone3Label->setObjectName(QStringLiteral("SharpnesZone3Label"));

        gridLayout_3->addWidget(SharpnesZone3Label, 2, 0, 1, 1);

        SharpnesZone3ValueLabel = new QLabel(SharpnessGroupBox);
        SharpnesZone3ValueLabel->setObjectName(QStringLiteral("SharpnesZone3ValueLabel"));
        SharpnesZone3ValueLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(SharpnesZone3ValueLabel, 2, 1, 1, 1);

        SharpnesOverAllLabel = new QLabel(SharpnessGroupBox);
        SharpnesOverAllLabel->setObjectName(QStringLiteral("SharpnesOverAllLabel"));

        gridLayout_3->addWidget(SharpnesOverAllLabel, 3, 0, 1, 1);

        SharpnesOverAllValueLabel = new QLabel(SharpnessGroupBox);
        SharpnesOverAllValueLabel->setObjectName(QStringLiteral("SharpnesOverAllValueLabel"));
        SharpnesOverAllValueLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(SharpnesOverAllValueLabel, 3, 1, 1, 1);


        gridLayout_5->addWidget(SharpnessGroupBox, 1, 1, 1, 1);

        SCMWOFGroupBox = new QGroupBox(tab);
        SCMWOFGroupBox->setObjectName(QStringLiteral("SCMWOFGroupBox"));
        gridLayout_8 = new QGridLayout(SCMWOFGroupBox);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        SCMWOFLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFLabel->setObjectName(QStringLiteral("SCMWOFLabel"));

        gridLayout_8->addWidget(SCMWOFLabel, 0, 0, 1, 1);

        SCMWOFNoFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFNoFingerLabel->setObjectName(QStringLiteral("SCMWOFNoFingerLabel"));
        SCMWOFNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFNoFingerLabel, 0, 1, 1, 1);

        SCMWOFWithFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFWithFingerLabel->setObjectName(QStringLiteral("SCMWOFWithFingerLabel"));
        SCMWOFWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFWithFingerLabel, 0, 2, 1, 1);

        SCMWOFGainLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFGainLabel->setObjectName(QStringLiteral("SCMWOFGainLabel"));
        SCMWOFGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFGainLabel, 0, 3, 1, 1);

        SCMWOFDeltaLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFDeltaLabel->setObjectName(QStringLiteral("SCMWOFDeltaLabel"));
        SCMWOFDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFDeltaLabel, 0, 4, 1, 1);

        SCMWOFZone0Label = new QLabel(SCMWOFGroupBox);
        SCMWOFZone0Label->setObjectName(QStringLiteral("SCMWOFZone0Label"));

        gridLayout_8->addWidget(SCMWOFZone0Label, 1, 0, 1, 1);

        SCMWOFZone1Label = new QLabel(SCMWOFGroupBox);
        SCMWOFZone1Label->setObjectName(QStringLiteral("SCMWOFZone1Label"));

        gridLayout_8->addWidget(SCMWOFZone1Label, 2, 0, 1, 1);

        SCMWOFZone0NoFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone0NoFingerLabel->setObjectName(QStringLiteral("SCMWOFZone0NoFingerLabel"));
        SCMWOFZone0NoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone0NoFingerLabel, 1, 1, 1, 1);

        SCMWOFZone0WithFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone0WithFingerLabel->setObjectName(QStringLiteral("SCMWOFZone0WithFingerLabel"));
        SCMWOFZone0WithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone0WithFingerLabel, 1, 2, 1, 1);

        SCMWOFZone0GainLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone0GainLabel->setObjectName(QStringLiteral("SCMWOFZone0GainLabel"));
        SCMWOFZone0GainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone0GainLabel, 1, 3, 1, 1);

        SCMWOFZone0DeltaLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone0DeltaLabel->setObjectName(QStringLiteral("SCMWOFZone0DeltaLabel"));
        SCMWOFZone0DeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone0DeltaLabel, 1, 4, 1, 1);

        SCMWOFZone1NoFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone1NoFingerLabel->setObjectName(QStringLiteral("SCMWOFZone1NoFingerLabel"));
        SCMWOFZone1NoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone1NoFingerLabel, 2, 1, 1, 1);

        SCMWOFZone1WithFingerLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone1WithFingerLabel->setObjectName(QStringLiteral("SCMWOFZone1WithFingerLabel"));
        SCMWOFZone1WithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone1WithFingerLabel, 2, 2, 1, 1);

        SCMWOFZone1GainLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone1GainLabel->setObjectName(QStringLiteral("SCMWOFZone1GainLabel"));
        SCMWOFZone1GainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone1GainLabel, 2, 3, 1, 1);

        SCMWOFZone1DeltaLabel = new QLabel(SCMWOFGroupBox);
        SCMWOFZone1DeltaLabel->setObjectName(QStringLiteral("SCMWOFZone1DeltaLabel"));
        SCMWOFZone1DeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(SCMWOFZone1DeltaLabel, 2, 4, 1, 1);


        gridLayout_5->addWidget(SCMWOFGroupBox, 1, 2, 1, 1);

        FakeFingerGroupBox = new QGroupBox(tab);
        FakeFingerGroupBox->setObjectName(QStringLiteral("FakeFingerGroupBox"));
        gridLayout_7 = new QGridLayout(FakeFingerGroupBox);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        FakeFingerLabel = new QLabel(FakeFingerGroupBox);
        FakeFingerLabel->setObjectName(QStringLiteral("FakeFingerLabel"));
        FakeFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(FakeFingerLabel, 0, 0, 1, 1);


        gridLayout_5->addWidget(FakeFingerGroupBox, 1, 3, 1, 2);

        WOFGroupBox = new QGroupBox(tab);
        WOFGroupBox->setObjectName(QStringLiteral("WOFGroupBox"));
        gridLayout_4 = new QGridLayout(WOFGroupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        WOFTagLabel = new QLabel(WOFGroupBox);
        WOFTagLabel->setObjectName(QStringLiteral("WOFTagLabel"));

        gridLayout_4->addWidget(WOFTagLabel, 0, 0, 1, 1);

        WOFNoFingerLabel = new QLabel(WOFGroupBox);
        WOFNoFingerLabel->setObjectName(QStringLiteral("WOFNoFingerLabel"));
        WOFNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFNoFingerLabel, 0, 1, 1, 1);

        WOFWithFingerLabel = new QLabel(WOFGroupBox);
        WOFWithFingerLabel->setObjectName(QStringLiteral("WOFWithFingerLabel"));
        WOFWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFWithFingerLabel, 0, 2, 1, 1);

        WOFGainLabel = new QLabel(WOFGroupBox);
        WOFGainLabel->setObjectName(QStringLiteral("WOFGainLabel"));
        WOFGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFGainLabel, 0, 3, 1, 1);

        WOFDeltaLabel = new QLabel(WOFGroupBox);
        WOFDeltaLabel->setObjectName(QStringLiteral("WOFDeltaLabel"));
        WOFDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFDeltaLabel, 0, 4, 1, 1);

        WOFZone0FDLabel = new QLabel(WOFGroupBox);
        WOFZone0FDLabel->setObjectName(QStringLiteral("WOFZone0FDLabel"));

        gridLayout_4->addWidget(WOFZone0FDLabel, 1, 0, 1, 1);

        WOFZone0FDNoFingerLabel = new QLabel(WOFGroupBox);
        WOFZone0FDNoFingerLabel->setObjectName(QStringLiteral("WOFZone0FDNoFingerLabel"));
        WOFZone0FDNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FDNoFingerLabel, 1, 1, 1, 1);

        WOFZone0FDWithFingerLabel = new QLabel(WOFGroupBox);
        WOFZone0FDWithFingerLabel->setObjectName(QStringLiteral("WOFZone0FDWithFingerLabel"));
        WOFZone0FDWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FDWithFingerLabel, 1, 2, 1, 1);

        WOFZone0FDGainLabel = new QLabel(WOFGroupBox);
        WOFZone0FDGainLabel->setObjectName(QStringLiteral("WOFZone0FDGainLabel"));
        WOFZone0FDGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FDGainLabel, 1, 3, 1, 1);

        WOFZone0FDDeltaLabel = new QLabel(WOFGroupBox);
        WOFZone0FDDeltaLabel->setObjectName(QStringLiteral("WOFZone0FDDeltaLabel"));
        WOFZone0FDDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FDDeltaLabel, 1, 4, 1, 1);

        WOFZone0FULabel = new QLabel(WOFGroupBox);
        WOFZone0FULabel->setObjectName(QStringLiteral("WOFZone0FULabel"));

        gridLayout_4->addWidget(WOFZone0FULabel, 2, 0, 1, 1);

        WOFZone0FUNoFingerLabel = new QLabel(WOFGroupBox);
        WOFZone0FUNoFingerLabel->setObjectName(QStringLiteral("WOFZone0FUNoFingerLabel"));
        WOFZone0FUNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FUNoFingerLabel, 2, 1, 1, 1);

        WOFZone0FUWithFingerLabel = new QLabel(WOFGroupBox);
        WOFZone0FUWithFingerLabel->setObjectName(QStringLiteral("WOFZone0FUWithFingerLabel"));
        WOFZone0FUWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FUWithFingerLabel, 2, 2, 1, 1);

        WOFZone0FUGainLabel = new QLabel(WOFGroupBox);
        WOFZone0FUGainLabel->setObjectName(QStringLiteral("WOFZone0FUGainLabel"));
        WOFZone0FUGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FUGainLabel, 2, 3, 1, 1);

        WOFZone0FUDeltaLabel = new QLabel(WOFGroupBox);
        WOFZone0FUDeltaLabel->setObjectName(QStringLiteral("WOFZone0FUDeltaLabel"));
        WOFZone0FUDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone0FUDeltaLabel, 2, 4, 1, 1);

        WOFZone1FDLabel = new QLabel(WOFGroupBox);
        WOFZone1FDLabel->setObjectName(QStringLiteral("WOFZone1FDLabel"));

        gridLayout_4->addWidget(WOFZone1FDLabel, 3, 0, 1, 1);

        WOFZone1FDNoFingerLabel = new QLabel(WOFGroupBox);
        WOFZone1FDNoFingerLabel->setObjectName(QStringLiteral("WOFZone1FDNoFingerLabel"));
        WOFZone1FDNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FDNoFingerLabel, 3, 1, 1, 1);

        WOFZone1FDWithFingerLabel = new QLabel(WOFGroupBox);
        WOFZone1FDWithFingerLabel->setObjectName(QStringLiteral("WOFZone1FDWithFingerLabel"));
        WOFZone1FDWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FDWithFingerLabel, 3, 2, 1, 1);

        WOFZone1FDGainLabel = new QLabel(WOFGroupBox);
        WOFZone1FDGainLabel->setObjectName(QStringLiteral("WOFZone1FDGainLabel"));
        WOFZone1FDGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FDGainLabel, 3, 3, 1, 1);

        WOFZone1FDDeltaLabel = new QLabel(WOFGroupBox);
        WOFZone1FDDeltaLabel->setObjectName(QStringLiteral("WOFZone1FDDeltaLabel"));
        WOFZone1FDDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FDDeltaLabel, 3, 4, 1, 1);

        WOFZone1FULabel = new QLabel(WOFGroupBox);
        WOFZone1FULabel->setObjectName(QStringLiteral("WOFZone1FULabel"));

        gridLayout_4->addWidget(WOFZone1FULabel, 4, 0, 1, 1);

        WOFZone1FUNoFingerLabel = new QLabel(WOFGroupBox);
        WOFZone1FUNoFingerLabel->setObjectName(QStringLiteral("WOFZone1FUNoFingerLabel"));
        WOFZone1FUNoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FUNoFingerLabel, 4, 1, 1, 1);

        WOFZone1FUWithFingerLabel = new QLabel(WOFGroupBox);
        WOFZone1FUWithFingerLabel->setObjectName(QStringLiteral("WOFZone1FUWithFingerLabel"));
        WOFZone1FUWithFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FUWithFingerLabel, 4, 2, 1, 1);

        WOFZone1FUGainLabel = new QLabel(WOFGroupBox);
        WOFZone1FUGainLabel->setObjectName(QStringLiteral("WOFZone1FUGainLabel"));
        WOFZone1FUGainLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FUGainLabel, 4, 3, 1, 1);

        WOFZone1FUDeltaLabel = new QLabel(WOFGroupBox);
        WOFZone1FUDeltaLabel->setObjectName(QStringLiteral("WOFZone1FUDeltaLabel"));
        WOFZone1FUDeltaLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(WOFZone1FUDeltaLabel, 4, 4, 1, 1);


        gridLayout_5->addWidget(WOFGroupBox, 0, 2, 1, 1);

        NoFingerGroupBox = new QGroupBox(tab);
        NoFingerGroupBox->setObjectName(QStringLiteral("NoFingerGroupBox"));
        gridLayout_6 = new QGridLayout(NoFingerGroupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        NoFingerLabel = new QLabel(NoFingerGroupBox);
        NoFingerLabel->setObjectName(QStringLiteral("NoFingerLabel"));
        NoFingerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(NoFingerLabel, 0, 0, 1, 1);


        gridLayout_5->addWidget(NoFingerGroupBox, 0, 3, 1, 2);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);

        YangpuClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(YangpuClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 885, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        YangpuClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(YangpuClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        YangpuClass->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(YangpuClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        YangpuClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);

        retranslateUi(YangpuClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(YangpuClass);
    } // setupUi

    void retranslateUi(QMainWindow *YangpuClass)
    {
        YangpuClass->setWindowTitle(QApplication::translate("YangpuClass", "Yangpu", 0));
        actionOpen->setText(QApplication::translate("YangpuClass", "Open", 0));
        actionExit->setText(QApplication::translate("YangpuClass", "Exit", 0));
        actionSave->setText(QApplication::translate("YangpuClass", "Save", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("YangpuClass", "SerialNumber", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("YangpuClass", "Result", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("YangpuClass", "Signal", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("YangpuClass", "Noise", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("YangpuClass", "SNR", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("YangpuClass", "Sharpness", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("YangpuClass", "BinCodes", 0));
        BasicInfoGroupBox->setTitle(QApplication::translate("YangpuClass", "Basic Info", 0));
        SerialNumberLabel->setText(QApplication::translate("YangpuClass", "SerialNumber", 0));
        SoftwareVersionLabel->setText(QApplication::translate("YangpuClass", "SW_Version", 0));
        ConfigFileLabel->setText(QApplication::translate("YangpuClass", "Config File", 0));
        SignalGroupBox->setTitle(QApplication::translate("YangpuClass", "Signal,Noise,SNR", 0));
        SNRTagLabel->setText(QApplication::translate("YangpuClass", "Zone/Value", 0));
        Zone1NameLabel->setText(QApplication::translate("YangpuClass", "Zone1", 0));
        Zone2NameLabel->setText(QApplication::translate("YangpuClass", "Zone2", 0));
        Zone3NameLabel->setText(QApplication::translate("YangpuClass", "Zone3", 0));
        Zone4NameLabel->setText(QApplication::translate("YangpuClass", "Zone4", 0));
        Zone5NameLabel->setText(QApplication::translate("YangpuClass", "Zone5", 0));
        Zone6NameLabel->setText(QApplication::translate("YangpuClass", "Zone6", 0));
        ZoneOverAllNameLabel->setText(QApplication::translate("YangpuClass", "OverAll", 0));
        SignalLabel->setText(QApplication::translate("YangpuClass", "Signal", 0));
        SignalZone1ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalZone2ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalZone3ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalZone4ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalZone5ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalZone6ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SignalOverAllValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseLabel->setText(QApplication::translate("YangpuClass", "Noise", 0));
        NoiseZone1ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseZone2ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseZone3ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseZone4ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseZone5ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseZone6ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoiseOverAllValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRLabel->setText(QApplication::translate("YangpuClass", "SNR", 0));
        SNRZone1ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRZone2ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRZone3ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRZone4ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRZone5ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNRZone6ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SNROverAllValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SharpnessGroupBox->setTitle(QApplication::translate("YangpuClass", "Sharpness", 0));
        SharpnesZone1Label->setText(QApplication::translate("YangpuClass", "Zone1", 0));
        SharpnesZone1ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SharpnesZone2Label->setText(QApplication::translate("YangpuClass", "Zone2", 0));
        SharpnesZone2ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SharpnesZone3Label->setText(QApplication::translate("YangpuClass", "Zone3", 0));
        SharpnesZone3ValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SharpnesOverAllLabel->setText(QApplication::translate("YangpuClass", "OverAll", 0));
        SharpnesOverAllValueLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFGroupBox->setTitle(QApplication::translate("YangpuClass", "SCM_WOF", 0));
        SCMWOFLabel->setText(QApplication::translate("YangpuClass", "Tag/Value", 0));
        SCMWOFNoFingerLabel->setText(QApplication::translate("YangpuClass", "NoFinger", 0));
        SCMWOFWithFingerLabel->setText(QApplication::translate("YangpuClass", "WithFinger", 0));
        SCMWOFGainLabel->setText(QApplication::translate("YangpuClass", "Gain", 0));
        SCMWOFDeltaLabel->setText(QApplication::translate("YangpuClass", "Delta", 0));
        SCMWOFZone0Label->setText(QApplication::translate("YangpuClass", "Zone0/Bottom", 0));
        SCMWOFZone1Label->setText(QApplication::translate("YangpuClass", "Zone1/Top", 0));
        SCMWOFZone0NoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone0WithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone0GainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone0DeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone1NoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone1WithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone1GainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        SCMWOFZone1DeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        FakeFingerGroupBox->setTitle(QApplication::translate("YangpuClass", "Normalized FakeFinger", 0));
        FakeFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFGroupBox->setTitle(QApplication::translate("YangpuClass", "WOF", 0));
        WOFTagLabel->setText(QApplication::translate("YangpuClass", "Tag/Value", 0));
        WOFNoFingerLabel->setText(QApplication::translate("YangpuClass", "NoFinger", 0));
        WOFWithFingerLabel->setText(QApplication::translate("YangpuClass", "WithFinger", 0));
        WOFGainLabel->setText(QApplication::translate("YangpuClass", "Gain", 0));
        WOFDeltaLabel->setText(QApplication::translate("YangpuClass", "Delta", 0));
        WOFZone0FDLabel->setText(QApplication::translate("YangpuClass", "Zone0 FingerDown", 0));
        WOFZone0FDNoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FDWithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FDGainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FDDeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FULabel->setText(QApplication::translate("YangpuClass", "Zone0 FingerUp", 0));
        WOFZone0FUNoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FUWithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FUGainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone0FUDeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FDLabel->setText(QApplication::translate("YangpuClass", "Zone1 FingerDown", 0));
        WOFZone1FDNoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FDWithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FDGainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FDDeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FULabel->setText(QApplication::translate("YangpuClass", "Zone1FigerUp", 0));
        WOFZone1FUNoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FUWithFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FUGainLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        WOFZone1FUDeltaLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        NoFingerGroupBox->setTitle(QApplication::translate("YangpuClass", "Average No Finger", 0));
        NoFingerLabel->setText(QApplication::translate("YangpuClass", "--", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("YangpuClass", "Detail Info", 0));
        menuFile->setTitle(QApplication::translate("YangpuClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class YangpuClass: public Ui_YangpuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YANGPU_H
