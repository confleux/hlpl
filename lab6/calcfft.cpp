#include "calcfft.h"
#include <fftw3.h>
#include <cmath>

void CalcFFT::Calc(const Param& oParam_p, Sample<double>& oFunc_p, Sample<double>& oRes_p) {
    const int n = oParam_p.Get_Size();
    if (n <= 0) {
        throw std::runtime_error("CalcFFT::Calc: sample size must be positive.");
    }
    oFunc_p.Resize(n, n);
    oRes_p.Resize(n, n);
    
    CreateFunction(oParam_p, oFunc_p);
    
    SampleComplex sc = SampleComplex::FromSample(oFunc_p);
    CalcFourier(sc);
    
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            oRes_p(y, x) = std::abs(sc(y, x));
        }
    }
}

void CalcFFT::CreateFunction(const Param& oParam_p, Sample<double>& oFunction_p) {
    const int n = oParam_p.Get_Size();
    const double dx = oParam_p.Get_Step_Function();
    if (n <= 0 || dx <= 0) {
        throw std::invalid_argument("CalcFFT::CreateFunction: invalid N or step.");
    }
    const double half = 0.5 * oParam_p.m_dFunctionSize;
    const double cx = 0.5 * static_cast<double>(n - 1);
    const double cy = 0.5 * static_cast<double>(n - 1);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            const double x_mm = (static_cast<double>(i) - cx) * dx;
            const double y_mm = (static_cast<double>(j) - cy) * dx;
            double v = 0.0;
            if (oParam_p.m_bIsCircle) {
                if (x_mm * x_mm + y_mm * y_mm <= half * half) {
                    v = 1.0;
                }
            } else {
                if (std::abs(x_mm) <= half && std::abs(y_mm) <= half) {
                    v = 1.0;
                }
            }
            oFunction_p(j, i) = v;
        }
    }
}

void CalcFFT::ShiftSample(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();
    const int shiftY = rows / 2;
    const int shiftX = cols / 2;

    SampleComplex tmp(rows, cols);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            const int ty = (y + shiftY) % rows;
            const int tx = (x + shiftX) % cols;
            tmp(ty, tx) = oSample_p(y, x);
        }
    }
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            oSample_p(y, x) = tmp(y, x);
        }
    }
}

void CalcFFT::CalcFourier(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();
    ShiftSample(oSample_p);

    fftw_complex* in = fftw_alloc_complex(static_cast<size_t>(rows) * static_cast<size_t>(cols));
    fftw_complex* out = fftw_alloc_complex(static_cast<size_t>(rows) * static_cast<size_t>(cols));
    if (!in || !out) {
        if (in) fftw_free(in);
        if (out) fftw_free(out);
        throw std::runtime_error("CalcFFT::CalcFourier: fftw_alloc_complex failed.");
    }

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            const size_t idx = static_cast<size_t>(y) * static_cast<size_t>(cols) + static_cast<size_t>(x);
            const std::complex<double> z = oSample_p(y, x);
            in[idx][0] = z.real();
            in[idx][1] = z.imag();
        }
    }

    fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    const double scale = 1.0 / (static_cast<double>(rows) * static_cast<double>(cols));
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            const size_t idx = static_cast<size_t>(y) * static_cast<size_t>(cols) + static_cast<size_t>(x);
            oSample_p(y, x) = std::complex<double>(out[idx][0] * scale, out[idx][1] * scale);
        }
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    ShiftSample(oSample_p);
}
