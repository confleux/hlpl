#include "param.h"

Param::Param()
{
    Reset();
}

void Param::Reset()
{
    m_dStepFunction = 1.0 / (m_iSize * 0.1);
    m_dStepSpectr = 0.1;
    m_dFunctionSize = 10.0;
    m_bIsCircle = true;
}

void Param::Set_Step_Function(double dValue_p, int iSize_p)
{
    m_dStepFunction = dValue_p;
    m_iSize = iSize_p;
    if (m_dStepSpectr != 0) {
        m_dStepSpectr = 1.0 / (m_iSize * m_dStepFunction);
    }
}

void Param::Set_Step_Spectr(double dValue_p, int iSize_p)
{
    m_dStepSpectr = dValue_p;
    m_iSize = iSize_p;
    if (m_dStepFunction != 0) {
        m_dStepFunction = 1.0 / (m_iSize * m_dStepSpectr);
    }
}

double Param::Get_Step_Function() const
{
    return m_dStepFunction;
}

double Param::Get_Step_Spectr() const
{
    return m_dStepSpectr;
}

int Param::Get_Size() const
{
    return m_iSize;
}
