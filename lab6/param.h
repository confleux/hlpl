#ifndef PARAM_H
#define PARAM_H

class Param
{
private:
    double m_dStepFunction = 0;
    double m_dStepSpectr = 0;
    int m_iSize = 512;
public:
    double m_dFunctionSize = 0;
    bool m_bIsCircle = true;

    Param();
    ~Param() = default;
    void Reset(); 
    void Set_Step_Function(double dValue_p, int iSize_p);
    void Set_Step_Spectr(double dValue_p, int iSize_p);
    double Get_Step_Function() const;
    double Get_Step_Spectr() const;
    int Get_Size() const;
};

#endif
