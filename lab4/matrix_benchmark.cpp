#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>
#include "sample.h"
#include "matrix.h"

int main()
{
    std::cout << "Matrix Multiplication with matrix.cpp" << std::endl;
    
    int sizes[] = {50, 100, 200, 300};
    
    for (int size : sizes) {
        Matrix mat1, mat2;
        mat1.Resize(size, size);
        mat2.Resize(size, size);
        
        int val = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                mat1(i, j) = 1.0;
                mat2(i, j) = 1.0;
            }
        }
        
        clock_t start = clock();
        Matrix result = mat1 * mat2;
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        
        std::cout << "Size " << size << "x" << size << ": " 
                  << std::fixed << std::setprecision(4) << elapsed << "s" << std::endl;
    }
    
    return 0;
}
