#include "calcfft.h"
#include "param.h"

#include <chrono>
#include <iostream>

static double BenchOnce(CalcFFT& fft, const Param& p, CalcFFT::Mode mode, int iters) {
    Sample<double> func;
    Sample<double> res;

    fft.Calc(p, func, res, mode);

    const auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < iters; ++i) {
        fft.Calc(p, func, res, mode);
    }
    const auto t1 = std::chrono::steady_clock::now();

    const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return ms / static_cast<double>(iters);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Param p;
    const int n = 2048;
    p.Set_Step_Function(0.1, n);

    CalcFFT fft;
    constexpr int iters = 10;

    const double baselineMs = BenchOnce(fft, p, CalcFFT::Mode::Baseline, iters);
    const double optimizedMs = BenchOnce(fft, p, CalcFFT::Mode::Optimized, iters);

    std::cout << "N=" << n << ", iters=" << iters << "\n";
    std::cout << "baseline_avg_ms=" << baselineMs << "\n";
    std::cout << "optimized_avg_ms=" << optimizedMs << "\n";
    if (optimizedMs > 0.0) {
        std::cout << "speedup_x=" << (baselineMs / optimizedMs) << "\n";
    }
    return 0;
}

