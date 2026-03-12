#ifndef MATRIX_H
#define MATRIX_H

#include "sample.h"

class Matrix : public Sample<double>
{
public:
    Matrix() = default;
    
    void MakeIdentity(int size);
    
    Matrix operator*(const Matrix& other) const;
    Matrix operator~() const;
    
    Matrix& operator/=(double value);
    Matrix& operator*=(double value);
    Matrix& operator*=(const Sample<double>& other);
    
    bool CanMultiply(const Matrix& other) const;
    
    using Sample<double>::m_data;
    using Sample<double>::m_size_x;
    using Sample<double>::m_size_y;
    using Sample<double>::Resize;
    using Sample<double>::SetValue;
    using Sample<double>::operator();
};

#endif
