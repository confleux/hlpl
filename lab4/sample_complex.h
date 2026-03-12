#ifndef SAMPLE_COMPLEX_H
#define SAMPLE_COMPLEX_H

#include "sample.h"
#include <complex>
#include <ostream>

class SampleComplex : public Sample<std::complex<double>>
{
public:
    SampleComplex() = default;
    
    SampleComplex(int size);
    
    double GetMagnitude() const;
    double GetPhase() const;
    Sample<double> GetIntensity() const;
    
    Sample<double> GetRealPart() const;
    Sample<double> GetImagPart() const;
    Sample<double> GetMagnitudeArray() const;
    Sample<double> GetPhaseArray() const;
    Sample<double> GetIntensityArray() const;
    
    void SaveRealPart(const std::string& filename) const;
    void SaveImagPart(const std::string& filename) const;
    void SaveMagnitude(const std::string& filename) const;
    void SavePhase(const std::string& filename) const;
    void SaveIntensity(const std::string& filename) const;
    
    operator Sample<double>() const;
    
    static SampleComplex FromSample(const Sample<double>& sample);
    
protected:
    using Sample<std::complex<double>>::m_data;
    using Sample<std::complex<double>>::m_size_x;
    using Sample<std::complex<double>>::m_size_y;
    using Sample<std::complex<double>>::Resize;
};

std::ostream& operator<<(std::ostream& out, const SampleComplex& sample);

#endif
