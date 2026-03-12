#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <fftw3.h>
#include "sample_complex.h"

const int SIZE = 512;

int main()
{
    SampleComplex data(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            data(i, j) = std::complex<double>(1.0, 0.0);
        }
    }
    
    int n = SIZE;
    int total_size = n * n;
    
    fftw_complex* in = (fftw_complex*)data.GetPointer();
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * total_size);
    
    fftw_plan plan = fftw_plan_dft_2d(n, n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    
    fftw_destroy_plan(plan);
    
    std::ofstream out_file("./fft_result.txt");
    if (!out_file) {
        std::cerr << "Cannot open fft_result.txt" << std::endl;
        return 1;
    }
    
    double scale = 1.0 / total_size;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double real = out[i * n + j][0];
            double imag = out[i * n + j][1];
            double magnitude = std::sqrt(real * real + imag * imag);
            
            out_file << "(" << real << ", " << imag << ")" << " ";
        }
        out_file << "\n";
    }
    
    out_file.close();
    
    fftw_free(out);
    
    std::cout << "FFT completed and result saved to fft_result.txt" << std::endl;
    
    double dc_value = std::sqrt(out[0][0] * out[0][0] + out[0][1] * out[0][1]) * scale;
    
    return 0;
}
