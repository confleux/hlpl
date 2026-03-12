#include "matrix.h"
#include <stdexcept>
#include <iostream>

void Matrix::MakeIdentity(int size)
{
    Resize(size, size);
    SetValue(0.0);
    for (int i = 0; i < size; ++i) {
        (*this)(i, i) = 1.0;
    }
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (!CanMultiply(other)) {
        throw std::runtime_error("Matrix dimensions are invalid");
    }
    
    Matrix result;
    result.Resize(m_size_x, other.m_size_y);
    
    for (int i = 0; i < m_size_x; ++i) {
        for (int j = 0; j < other.m_size_y; ++j) {
            double sum = 0.0;
            for (int k = 0; k < m_size_y; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    
    return result;
}

Matrix Matrix::operator~() const
{
    Matrix result;
    result.Resize(m_size_y, m_size_x);
    
    for (int i = 0; i < m_size_x; ++i) {
        for (int j = 0; j < m_size_y; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    
    return result;
}

Matrix& Matrix::operator/=(double value)
{
    throw std::runtime_error("Division operator not supported for Matrix");
}

Matrix& Matrix::operator*=(double value)
{
    throw std::runtime_error("Scalar multiplication operator not supported for Matrix");
}

Matrix& Matrix::operator*=(const Sample<double>& other)
{
    throw std::runtime_error("Element-wise multiplication operator not supported for Matrix");
}

bool Matrix::CanMultiply(const Matrix& other) const
{
    return m_size_y == other.m_size_x;
}

template class Sample<double>;
