#ifndef CALCFFT_H
#define CALCFFT_H

#include "param.h"
#include "sample.h"
#include "sample_complex.h"
#include <fftw3.h>

class CalcFFT
{
public:
    enum class Mode {
        Baseline,
        Optimized,
    };

    CalcFFT() = default;
    ~CalcFFT();

    // вычисление преобразования Фурье
    void Calc(const Param& oParam_p, Sample<double>& oFunc_p, Sample<double>& oRes_p, Mode mode = Mode::Optimized);

private:
    void EnsurePlan(int rows, int cols);
    void FreePlan();

    // генерация функции
    void CreateFunction(const Param& oParam_p, Sample<double>& oFunction_p);

    // вычисление двумерного преобразования Фурье от oSample_p (+ сдвиг до и после)
    void CalcFourier(SampleComplex& oSample_p); // optimized
    void CalcFourierBaseline(SampleComplex& oSample_p);
    // сдвиг oSample_p для преобразования Фурье
    void ShiftSample(SampleComplex& oSample_p); // optimized
    void ShiftSampleBaseline(SampleComplex& oSample_p);

private:
    fftw_complex* m_buf = nullptr; // in-place buffer
    fftw_plan m_plan = nullptr;
    int m_rows = 0;
    int m_cols = 0;
};

#endif
