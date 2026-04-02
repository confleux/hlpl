#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include <QSpacerItem>
#include "param.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);

    leftLayout = new QVBoxLayout();
    mainLayout->addLayout(leftLayout);

    groupFunctionParams = new QGroupBox("Параметры функции", centralWidget);
    verticalLayoutFunc = new QVBoxLayout(groupFunctionParams);

    radioCircle = new QRadioButton("Круг", groupFunctionParams);
    radioCircle->setChecked(true);
    radioSquare = new QRadioButton("Квадрат", groupFunctionParams);

    horizontalLayoutDiameter = new QHBoxLayout();
    labelDiameter = new QLabel("Диаметр круга (сторона квадрата)", groupFunctionParams);
    spinDiameterMm = new QDoubleSpinBox(groupFunctionParams);
    spinDiameterMm->setDecimals(6);
    spinDiameterMm->setMinimum(1e-6);
    spinDiameterMm->setMaximum(1e6);
    spinDiameterMm->setValue(1.0);
    labelMm = new QLabel("мм", groupFunctionParams);

    horizontalLayoutDiameter->addWidget(labelDiameter);
    horizontalLayoutDiameter->addWidget(spinDiameterMm);
    horizontalLayoutDiameter->addWidget(labelMm);

    verticalLayoutFunc->addWidget(radioCircle);
    verticalLayoutFunc->addWidget(radioSquare);
    verticalLayoutFunc->addLayout(horizontalLayoutDiameter);
    groupFunctionParams->setLayout(verticalLayoutFunc);
    leftLayout->addWidget(groupFunctionParams);

    groupDisplayParams = new QGroupBox("Параметры отображения", centralWidget);
    verticalLayoutDisp = new QVBoxLayout(groupDisplayParams);

    labelDisplayUnits = new QLabel("Единицы измерения на графиках:", groupDisplayParams);
    horizontalLayoutDisplay = new QHBoxLayout();
    radioAxisMicrometers = new QRadioButton("мкм", groupDisplayParams);
    radioAxisMicrometers->setChecked(true);
    radioAxisPixels = new QRadioButton("пиксели", groupDisplayParams);
    btnRedraw = new QPushButton("Перерисовать", groupDisplayParams);

    horizontalLayoutDisplay->addWidget(radioAxisMicrometers);
    horizontalLayoutDisplay->addWidget(radioAxisPixels);
    horizontalLayoutDisplay->addWidget(btnRedraw);

    verticalLayoutDisp->addWidget(labelDisplayUnits);
    verticalLayoutDisp->addLayout(horizontalLayoutDisplay);
    groupDisplayParams->setLayout(verticalLayoutDisp);
    leftLayout->addWidget(groupDisplayParams);

    verticalSpacerLeft = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftLayout->addItem(verticalSpacerLeft);

    groupCalcParams = new QGroupBox("Параметры вычислений", centralWidget);
    verticalLayoutCalc = new QVBoxLayout(groupCalcParams);

    formLayoutCalc = new QFormLayout();

    labelSampleSize = new QLabel("Размер выборки", groupCalcParams);
    comboSampleSize = new QComboBox(groupCalcParams);
    comboSampleSize->addItem("128");
    comboSampleSize->addItem("256");
    comboSampleSize->addItem("512");
    comboSampleSize->addItem("1024");
    comboSampleSize->addItem("2048");
    comboSampleSize->setCurrentText("512");

    labelSourceParam = new QLabel("Исходный параметр для вычислений:", groupCalcParams);
    comboSourceParam = new QComboBox(groupCalcParams);
    comboSourceParam->addItem("Шаг по функции [мм]");
    comboSourceParam->addItem("Шаг по спектру [1/мм]");
    comboSourceParam->setCurrentText("Шаг по функции [мм]");

    labelStepFunction = new QLabel("Шаг по функции", groupCalcParams);
    horizontalLayoutStepFunction = new QHBoxLayout();
    spinStepFunction = new QDoubleSpinBox(groupCalcParams);
    spinStepFunction->setDecimals(6);
    spinStepFunction->setMinimum(1e-10);
    spinStepFunction->setMaximum(1e3);
    spinStepFunction->setValue(0.1);
    labelUnitFunction = new QLabel("мм", groupCalcParams);

    horizontalLayoutStepFunction->addWidget(spinStepFunction);
    horizontalLayoutStepFunction->addWidget(labelUnitFunction);

    labelStepSpectr = new QLabel("Шаг по спектру", groupCalcParams);
    horizontalLayoutStepSpectr = new QHBoxLayout();
    spinStepSpectr = new QDoubleSpinBox(groupCalcParams);
    spinStepSpectr->setDecimals(6);
    spinStepSpectr->setMinimum(1e-10);
    spinStepSpectr->setMaximum(1e3);
    spinStepSpectr->setValue(0.0195313);
    spinStepSpectr->setReadOnly(true);
    labelUnitSpectr = new QLabel("мм", groupCalcParams);

    horizontalLayoutStepSpectr->addWidget(spinStepSpectr);
    horizontalLayoutStepSpectr->addWidget(labelUnitSpectr);

    formLayoutCalc->addRow(labelSampleSize, comboSampleSize);
    formLayoutCalc->addRow(labelSourceParam, comboSourceParam);
    formLayoutCalc->addRow(labelStepFunction, horizontalLayoutStepFunction);
    formLayoutCalc->addRow(labelStepSpectr, horizontalLayoutStepSpectr);

    verticalLayoutCalc->addLayout(formLayoutCalc);

    horizontalLayoutButtons = new QHBoxLayout();
    btnRecalculate = new QPushButton("Пересчитать шаги", groupCalcParams);
    btnCalculate = new QPushButton("Вычислить", groupCalcParams);
    btnResetAll = new QPushButton("Сбросить все параметры", groupCalcParams);

    horizontalLayoutButtons->addWidget(btnRecalculate);
    horizontalLayoutButtons->addWidget(btnCalculate);
    horizontalLayoutButtons->addWidget(btnResetAll);

    verticalLayoutCalc->addLayout(horizontalLayoutButtons);

    verticalSpacerCalc = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayoutCalc->addItem(verticalSpacerCalc);

    groupCalcParams->setLayout(verticalLayoutCalc);
    mainLayout->addWidget(groupCalcParams);

    resize(640, 480);

    connect(radioCircle, &QRadioButton::toggled, [this](bool checked) {
        if (checked) m_param.m_bIsCircle = true;
    });
    connect(radioSquare, &QRadioButton::toggled, [this](bool checked) {
        if (checked) m_param.m_bIsCircle = false;
    });
    connect(spinDiameterMm, &QDoubleSpinBox::valueChanged, [this](double value) {
        m_param.m_dFunctionSize = value;
    });
    connect(comboSampleSize, &QComboBox::currentTextChanged, [this](const QString &text) {
        int size = text.toInt();
        m_param.Set_Step_Function(m_param.Get_Step_Function(), size);
    });
    connect(comboSourceParam, &QComboBox::currentIndexChanged, this, &MainWindow::onSourceParamChanged);
    connect(spinStepFunction, &QDoubleSpinBox::valueChanged, this, &MainWindow::onStepFunctionChanged);
    connect(btnRedraw, &QPushButton::clicked, this, &MainWindow::onRedrawClicked);
    connect(btnRecalculate, &QPushButton::clicked, this, &MainWindow::onRecalculateClicked);
    connect(btnCalculate, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
    connect(btnResetAll, &QPushButton::clicked, this, &MainWindow::onResetClicked);
}

MainWindow::~MainWindow()
{
    delete centralWidget;
}

void MainWindow::onCalculateClicked()
{
}

void MainWindow::onRecalculateClicked()
{
}

void MainWindow::onResetClicked()
{
    m_param.Reset();
    
    radioCircle->setChecked(true);
    spinDiameterMm->setValue(1.0);
    comboSampleSize->setCurrentText("512");
    comboSourceParam->setCurrentText("Шаг по функции [мм]");
    spinStepFunction->setValue(0.1);
    spinStepSpectr->setReadOnly(true);
    spinStepSpectr->setValue(m_param.Get_Step_Spectr());
    
    labelStepFunction->setEnabled(true);
    spinStepFunction->setEnabled(true);
    labelUnitFunction->setEnabled(true);
    labelStepSpectr->setEnabled(false);
    spinStepSpectr->setEnabled(false);
    labelUnitSpectr->setEnabled(false);
}

void MainWindow::onRedrawClicked()
{
}

void MainWindow::onSourceParamChanged(int index)
{
    if (index == 0) {
        labelStepFunction->setEnabled(true);
        spinStepFunction->setEnabled(true);
        labelUnitFunction->setEnabled(true);
        labelStepSpectr->setEnabled(false);
        spinStepSpectr->setReadOnly(true);
        spinStepSpectr->setEnabled(false);
        labelUnitSpectr->setEnabled(false);
        spinStepSpectr->setValue(m_param.Get_Step_Spectr());
    } else {
        labelStepFunction->setEnabled(false);
        spinStepFunction->setEnabled(false);
        labelUnitFunction->setEnabled(false);
        labelStepSpectr->setEnabled(true);
        spinStepSpectr->setReadOnly(false);
        spinStepSpectr->setEnabled(true);
        labelUnitSpectr->setEnabled(true);
        spinStepFunction->setValue(m_param.Get_Step_Function());
    }
}

void MainWindow::onStepFunctionChanged(double value)
{
    m_param.Set_Step_Function(value, m_param.Get_Size());
}

void MainWindow::onSampleSizeChanged(int index)
{
}
