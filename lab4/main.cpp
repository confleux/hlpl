#include <iostream>
#include "sample_complex.h"
#include "matrix.h"

int main()
{
    std::cout << "\tSampleComplex:\n" << std::endl;
    
    SampleComplex complexSample(3);
    complexSample(0, 0) = std::complex<double>(3.0, 4.0);
    complexSample(0, 1) = std::complex<double>(1.0, 1.0);
    complexSample(1, 0) = std::complex<double>(0.0, 2.0);
    
    std::cout << "Magnitude: " << complexSample.GetMagnitude() << std::endl;
    std::cout << "Phase: " << complexSample.GetPhase() << std::endl;
    
    Sample<double> intensity = complexSample.GetIntensity();
    std::cout << "Intensity at (0,0): " << intensity(0, 0) << std::endl;
    
    Sample<double> realPart = complexSample.GetRealPart();
    Sample<double> imagPart = complexSample.GetImagPart();
    std::cout << "Real part at (0,0): " << realPart(0, 0) << std::endl;
    std::cout << "Imag part at (0,0): " << imagPart(0, 0) << std::endl;
    
    Sample<double> magArray = complexSample.GetMagnitudeArray();
    std::cout << "Magnitude array at (0,0): " << magArray(0, 0) << std::endl;
    
    Sample<double> phaseArray = complexSample.GetPhaseArray();
    std::cout << "Phase array at (0,0): " << phaseArray(0, 0) << std::endl;
    
    Sample<double> intensityArray = complexSample.GetIntensityArray();
    std::cout << "Intensity array at (0,0): " << intensityArray(0, 0) << std::endl;
    
    SampleComplex fromDouble = SampleComplex::FromSample(complexSample.GetRealPart());
    std::cout << "FromDouble sample created, size: " << fromDouble.GetSizeX() << "x" << fromDouble.GetSizeY() << std::endl;
    
    std::cout << "\n\tTesting Matrix:\n" << std::endl;
    
    Matrix mat1, mat2;
    mat1.Resize(2, 3);
    mat2.Resize(3, 2);
    
    int val = 1;
    for (int i = 0; i < mat1.GetSizeX(); ++i) {
        for (int j = 0; j < mat1.GetSizeY(); ++j) {
            mat1(i, j) = val++;
        }
    }
    
    val = 7;
    for (int i = 0; i < mat2.GetSizeX(); ++i) {
        for (int j = 0; j < mat2.GetSizeY(); ++j) {
            mat2(i, j) = val++;
        }
    }
    
    std::cout << "Matrix 1 (2x3):" << std::endl;
    std::cout << "Size: " << mat1.GetSizeX() << "x" << mat1.GetSizeY() << std::endl;
    
    std::cout << "Matrix 2 (3x2):" << std::endl;
    std::cout << "Size: " << mat2.GetSizeX() << "x" << mat2.GetSizeY() << std::endl;
    
    std::cout << "Can multiply: " << mat1.CanMultiply(mat2) << std::endl;
    
    Matrix result = mat1 * mat2;
    std::cout << "Result (2x2):" << std::endl;
    std::cout << "Size: " << result.GetSizeX() << "x" << result.GetSizeY() << std::endl;
    
    Matrix identity;
    identity.MakeIdentity(3);
    std::cout << "Identity matrix (3x3):" << std::endl;
    std::cout << "Size: " << identity.GetSizeX() << "x" << identity.GetSizeY() << std::endl;
    
    Matrix transposed = ~mat1;
    std::cout << "Transposed mat1 (3x2):" << std::endl;
    std::cout << "Size: " << transposed.GetSizeX() << "x" << transposed.GetSizeY() << std::endl;
    
    try {
        mat1 /= 2.0;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        mat1 *= 2.0;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        mat1 /= 2.0;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    return 0;
}
