#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include "param.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateClicked();
    void onRecalculateClicked();
    void onResetClicked();
    void onRedrawClicked();
    void onSourceParamChanged(int index);
    void onStepFunctionChanged(double value);
    void onSampleSizeChanged(int index);

private:
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    
    QVBoxLayout *leftLayout;
    QGroupBox *groupFunctionParams;
    QVBoxLayout *verticalLayoutFunc;
    QRadioButton *radioCircle;
    QRadioButton *radioSquare;
    QHBoxLayout *horizontalLayoutDiameter;
    QLabel *labelDiameter;
    QDoubleSpinBox *spinDiameterMm;
    QLabel *labelMm;
    
    QGroupBox *groupDisplayParams;
    QVBoxLayout *verticalLayoutDisp;
    QLabel *labelDisplayUnits;
    QHBoxLayout *horizontalLayoutDisplay;
    QRadioButton *radioAxisMicrometers;
    QRadioButton *radioAxisPixels;
    QPushButton *btnRedraw;
    
    QSpacerItem *verticalSpacerLeft;
    
    QGroupBox *groupCalcParams;
    QVBoxLayout *verticalLayoutCalc;
    QFormLayout *formLayoutCalc;
    QLabel *labelSampleSize;
    QComboBox *comboSampleSize;
    QLabel *labelSourceParam;
    QComboBox *comboSourceParam;
    QLabel *labelStepFunction;
    QHBoxLayout *horizontalLayoutStepFunction;
    QDoubleSpinBox *spinStepFunction;
    QLabel *labelUnitFunction;
    QLabel *labelStepSpectr;
    QHBoxLayout *horizontalLayoutStepSpectr;
    QDoubleSpinBox *spinStepSpectr;
    QLabel *labelUnitSpectr;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnRecalculate;
    QPushButton *btnCalculate;
    QPushButton *btnResetAll;
    
    QSpacerItem *verticalSpacerCalc;
    
    Param m_param;
};

#endif
