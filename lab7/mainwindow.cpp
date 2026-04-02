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
#include <QElapsedTimer>
#include <QDebug>
#include "param.h"
#include "calcfft.h"

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

    setupPlots();

    resize(1200, 800);

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

void MainWindow::setupPlots()
{
    rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);

    plotsRowLayout = new QHBoxLayout();
    rightLayout->addLayout(plotsRowLayout);

    plotFunction = new QCustomPlot();
    plotFunction->setWindowTitle("Функция (x/y, мм)");
    plotFunction->xAxis->setLabel("x, мм");
    plotFunction->yAxis->setLabel("y, мм");
    plotFunction->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plotFunction->setMinimumSize(320, 320);
    colorMapFunction = new QCPColorMap(plotFunction->xAxis, plotFunction->yAxis);
    colorScaleFunction = new QCPColorScale(plotFunction);
    plotFunction->plotLayout()->addElement(0, 1, colorScaleFunction);
    colorScaleFunction->setType(QCPAxis::atRight);
    colorMapFunction->setColorScale(colorScaleFunction);
    colorMapFunction->setInterpolate(true);
    colorMapFunction->setGradient(QCPColorGradient::gpGrayscale);

    plotSpectrum = new QCustomPlot();
    plotSpectrum->setWindowTitle("Спектр (freq x / freq y, 1/мм)");
    plotSpectrum->xAxis->setLabel("freq x, 1/мм");
    plotSpectrum->yAxis->setLabel("freq y, 1/мм");
    plotSpectrum->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plotSpectrum->setMinimumSize(320, 320);
    colorMapSpectrum = new QCPColorMap(plotSpectrum->xAxis, plotSpectrum->yAxis);
    colorScaleSpectrum = new QCPColorScale(plotSpectrum);
    plotSpectrum->plotLayout()->addElement(0, 1, colorScaleSpectrum);
    colorScaleSpectrum->setType(QCPAxis::atRight);
    colorMapSpectrum->setColorScale(colorScaleSpectrum);
    colorMapSpectrum->setInterpolate(true);
    colorMapSpectrum->setGradient(QCPColorGradient::gpThermal);

    plotFFTResult = new QCustomPlot();
    plotFFTResult->setWindowTitle("freq x / FFT результат");
    plotFFTResult->xAxis->setLabel("freq x, 1/мм");
    plotFFTResult->yAxis->setLabel("FFT результат");
    plotFFTResult->legend->setVisible(true);
    plotFFTResult->legend->setBrush(QBrush(QColor(255, 255, 255, 180)));
    plotFFTResult->addGraph(); // Section X
    plotFFTResult->addGraph(); // Section Y
    plotFFTResult->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plotFFTResult->setMinimumSize(320, 320);

    plotsRowLayout->addWidget(plotFunction);
    plotsRowLayout->addWidget(plotSpectrum);
    plotsRowLayout->addWidget(plotFFTResult);
}

void MainWindow::updatePlots()
{
    int size = m_param.Get_Size();
    
    plotFunction->clearItems();
    
    double stepFunc = m_param.Get_Step_Function();

    colorMapFunction->data()->setSize(size, size);
    const double xMinFunc = -(static_cast<double>(size) / 2.0) * stepFunc;
    const double xMaxFunc = (static_cast<double>(size) / 2.0 - 1.0) * stepFunc;
    const double yMinFunc = xMinFunc;
    const double yMaxFunc = xMaxFunc;
    colorMapFunction->data()->setRange(QCPRange(xMinFunc, xMaxFunc), QCPRange(yMinFunc, yMaxFunc));

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            colorMapFunction->data()->setCell(x, y, m_functionData(y, x));
        }
    }

    plotFunction->xAxis->setRange(xMinFunc, xMaxFunc);
    plotFunction->yAxis->setRange(yMinFunc, yMaxFunc);
    colorMapFunction->rescaleDataRange(true);
    plotFunction->replot();
    
    plotSpectrum->clearItems();
    
    double stepSpectr = m_param.Get_Step_Spectr();

    colorMapSpectrum->data()->setSize(size, size);
    const double xMinSpec = -(static_cast<double>(size) / 2.0) * stepSpectr;
    const double xMaxSpec = (static_cast<double>(size) / 2.0 - 1.0) * stepSpectr;
    const double yMinSpec = xMinSpec;
    const double yMaxSpec = xMaxSpec;
    colorMapSpectrum->data()->setRange(QCPRange(xMinSpec, xMaxSpec), QCPRange(yMinSpec, yMaxSpec));

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            colorMapSpectrum->data()->setCell(x, y, m_spectrumData(y, x));
        }
    }

    plotSpectrum->xAxis->setRange(xMinSpec, xMaxSpec);
    plotSpectrum->yAxis->setRange(yMinSpec, yMaxSpec);
    colorMapSpectrum->rescaleDataRange(true);
    plotSpectrum->replot();

    int midY = size / 2;
    int midX = size / 2;

    plotFFTResult->clearPlottables();
    plotFFTResult->clearItems();
    plotFFTResult->addGraph(); // Section X
    plotFFTResult->addGraph(); // Section Y
    plotFFTResult->graph(0)->setName("Section X");
    plotFFTResult->graph(1)->setName("Section Y");

    QVector<double> freq(size), sectionX(size), sectionY(size);
    for (int x = 0; x < size; ++x) {
        freq[x] = (x - size / 2) * stepSpectr;
        sectionX[x] = m_spectrumData(midY, x);
        sectionY[x] = m_spectrumData(x, midX);
    }

    plotFFTResult->graph(0)->setData(freq, sectionX, true);
    plotFFTResult->graph(1)->setData(freq, sectionY, true);

    auto *zeroLine = new QCPItemStraightLine(plotFFTResult);
    zeroLine->point1->setCoords(0.0, 0.0);
    zeroLine->point2->setCoords(0.0, 1.0);
    zeroLine->setPen(QPen(QColor(30, 30, 30, 180)));

    plotFFTResult->xAxis->setLabel("частота по X, 1/мм");
    plotFFTResult->rescaleAxes();
    plotFFTResult->replot();
}

void MainWindow::onCalculateClicked()
{
    m_functionData = Sample<double>();
    m_spectrumData = Sample<double>();

    constexpr int kIters = 10;
    QElapsedTimer timer;
    timer.start();
    for (int it = 0; it < kIters; ++it) {
        m_calcFFT.Calc(m_param, m_functionData, m_spectrumData);
    }
    const qint64 elapsedNs = timer.nsecsElapsed();
    const double avgMs = (static_cast<double>(elapsedNs) / 1e6) / static_cast<double>(kIters);
    qDebug().noquote() << QString("FFT compute avg: %1 ms (N=%2, iters=%3)")
                          .arg(avgMs, 0, 'f', 3)
                          .arg(m_param.Get_Size())
                          .arg(kIters);

    updatePlots();
}

void MainWindow::onRecalculateClicked()
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
    updatePlots();
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
