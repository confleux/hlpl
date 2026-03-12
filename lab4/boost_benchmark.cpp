#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation.hpp>

int main()
{
    std::cout << "Matrix multiplication with Boost::Numeric::Ublas" << std::endl;
    
    int sizes[] = {50, 100, 200, 300};
    
    for (int size : sizes) {
        using namespace boost::numeric::ublas;
        
        matrix<double> mat1(size, size);
        matrix<double> mat2(size, size);
        matrix<double> result(size, size);
        
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                mat1(i, j) = 1.0;
                mat2(i, j) = 1.0;
            }
        }
        
        clock_t start = clock();
        result = prod(mat1, mat2);
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        
        std::cout << "Size " << size << "x" << size << ": " 
                  << std::fixed << std::setprecision(4) << elapsed << "s" << std::endl;
        
        std::cout << "  Result(0,0) = " << result(0, 0) << std::endl;
    }
    
    return 0;
}
