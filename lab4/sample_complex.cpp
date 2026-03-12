#include "sample_complex.h"
#include <fstream>
#include <stdexcept>
#include <cmath>

SampleComplex::SampleComplex(int size)
{
    Resize(size, size);
}

namespace {
    template <class T>
    T* GetSampleData(Sample<T>& s) { return s.GetDataPointer(); }
    
    template <class T>
    const T* GetSampleData(const Sample<T>& s) { return s.GetDataPointer(); }
}

double SampleComplex::GetMagnitude() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    double max_mag = 0.0;
    for (const auto& el : m_data) {
        double mag = std::abs(el);
        if (mag > max_mag) {
            max_mag = mag;
        }
    }
    return max_mag;
}

double SampleComplex::GetPhase() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    double max_phase = 0.0;
    for (const auto& el : m_data) {
        double phase = std::arg(el);
        if (std::abs(phase) > std::abs(max_phase)) {
            max_phase = phase;
        }
    }
    return max_phase;
}

Sample<double> SampleComplex::GetIntensity() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        double mag_sq = std::norm(m_data[i]);
        result_data[i] = mag_sq;
    }
    
    return result;
}

Sample<double> SampleComplex::GetRealPart() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        result_data[i] = m_data[i].real();
    }
    
    return result;
}

Sample<double> SampleComplex::GetImagPart() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        result_data[i] = m_data[i].imag();
    }
    
    return result;
}

Sample<double> SampleComplex::GetMagnitudeArray() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        result_data[i] = std::abs(m_data[i]);
    }
    
    return result;
}

Sample<double> SampleComplex::GetPhaseArray() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        result_data[i] = std::arg(m_data[i]);
    }
    
    return result;
}

Sample<double> SampleComplex::GetIntensityArray() const
{
    if (IsZeroSize()) {
        throw std::runtime_error("Sample is empty");
    }
    
    Sample<double> result;
    result.Resize(m_size_x, m_size_y);
    
    double* result_data = GetSampleData(result);
    for (int i = 0; i < GetSize(); ++i) {
        result_data[i] = std::norm(m_data[i]);
    }
    
    return result;
}

void SampleComplex::SaveRealPart(const std::string& filename) const
{
    Sample<double> real = GetRealPart();
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    real.Save(out);
}

void SampleComplex::SaveImagPart(const std::string& filename) const
{
    Sample<double> imag = GetImagPart();
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    imag.Save(out);
}

void SampleComplex::SaveMagnitude(const std::string& filename) const
{
    Sample<double> mag = GetMagnitudeArray();
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    mag.Save(out);
}

void SampleComplex::SavePhase(const std::string& filename) const
{
    Sample<double> phase = GetPhaseArray();
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    phase.Save(out);
}

void SampleComplex::SaveIntensity(const std::string& filename) const
{
    Sample<double> intensity = GetIntensityArray();
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    intensity.Save(out);
}

SampleComplex::operator Sample<double>() const
{
    return GetMagnitudeArray();
}

SampleComplex SampleComplex::FromSample(const Sample<double>& sample)
{
    SampleComplex result;
    result.Resize(sample.GetSizeX(), sample.GetSizeY());
    
    const double* sample_data = GetSampleData(sample);
    std::complex<double>* result_data = GetSampleData(result);
    for (int i = 0; i < result.GetSize(); ++i) {
        result_data[i] = std::complex<double>(sample_data[i], 0.0);
    }
    
    return result;
}

std::ostream& operator<<(std::ostream& out, const SampleComplex& sample)
{
    out << sample.GetSizeX() << " " << sample.GetSizeY() << "\n";
    for (int i = 0; i < sample.GetSizeY(); ++i) {
        for (int j = 0; j < sample.GetSizeX(); ++j) {
            out << sample(i, j) << " ";
        }
        out << "\n";
    }
    return out;
}

template class Sample<std::complex<double>>;

