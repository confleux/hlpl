#ifndef CALCFFT_H
#define CALCFFT_H

#include "param.h"
#include "sample.h"
#include "sample_complex.h"

class CalcFFT
{
public:
    CalcFFT() = default;
    ~CalcFFT() = default;

    // вычисление преобразования Фурье
    void Calc(const Param& oParam_p, Sample<double>& oFunc_p, Sample<double>& oRes_p);

private:
    // генерация функции
    void CreateFunction(const Param& oParam_p, Sample<double>& oFunction_p);

    // вычисление двумерного преобразования Фурье от oSample_p (+ сдвиг до и после)
    void CalcFourier(SampleComplex& oSample_p);
    // сдвиг oSample_p для преобразования Фурье
    void ShiftSample(SampleComplex& oSample_p);
};

#endif
