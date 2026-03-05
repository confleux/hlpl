#include "sample_int.h"

void Sample_int::Resize(int size) {
  if (size < 0)
    throw std::invalid_argument("Size must be positive");

  m_size_x = size;
  m_size_y = size;
  m_data.resize(m_size_x * m_size_y);
}

void Sample_int::Resize(int size_x, int size_y) {
  if (size_x < 0 || size_y < 0)
    throw std::invalid_argument("Size must be positive");

  m_size_x = size_x;
  m_size_y = size_y;
  m_data.resize(size_x * size_y);
}

int Sample_int::GetSize() const {
  return m_size_x * m_size_y;
}

int Sample_int::GetSizeX() const {
  return m_size_x;
}

int Sample_int::GetSizeY() const {
  return m_size_y;
}

int& Sample_int::operator()(int i, int j) {
  if (i < 0 || i >= m_size_x || j < 0 || j >= m_size_y)
    throw std::invalid_argument("Invlid index");

  return m_data[i * m_size_x + j];
}

const int& Sample_int::operator()(int i, int j) const {
  if (i < 0 || i >= m_size_x || j < 0 || j >= m_size_y)
    throw std::invalid_argument("Invlid index");

  return m_data[i * m_size_x + j];
}

bool Sample_int::IsSquare() const {
  return m_size_x == m_size_y;
}

bool Sample_int::IsZeroSize() const {
  return m_size_x == 0 || m_size_y == 0;
}

bool Sample_int::IsEqualSize(const Sample_int& temp) const {
  return m_size_x == temp.GetSizeX() && m_size_y == temp.GetSizeY();
}

void Sample_int::SetValue(int value) {
  m_data.assign(GetSize(), value);
}

int* Sample_int::GetPointer() {
  return m_data.data();
}

int Sample_int::GetMax() const {
  return *std::max_element(m_data.begin(), m_data.end());
}

Sample_int& Sample_int::operator+=(int value) {
  for (auto& el : m_data)
    el += value;

  return *this;
}

Sample_int& Sample_int::operator*=(int value) {
  for (auto& el : m_data)
    el *= value;

  return *this;
}

Sample_int& Sample_int::operator/=(int value) {
  for (auto& el : m_data)
    el /= value;

  return *this;
}

Sample_int& Sample_int::operator=(const Sample_int& temp) {
  m_data = temp.m_data;
  m_size_x = temp.GetSizeX();
  m_size_y = temp.GetSizeY();

  return *this;
}

Sample_int& Sample_int::operator+=(const Sample_int& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < GetSize(); ++i)
    m_data[i] += temp.m_data[i];

  return *this;
}

Sample_int& Sample_int::operator-=(const Sample_int& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < GetSize(); ++i)
    m_data[i] -= temp.m_data[i];

  return *this;
}

Sample_int& Sample_int::operator*=(const Sample_int& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < GetSize(); ++i)
    m_data[i] *= temp.m_data[i];

  return *this;
}

std::ostream& Sample_int::Save(std::ostream& out) {
  out << GetSizeX() << ' ' << GetSizeY() << '\n';
  for (size_t i = 0; i < GetSizeY(); ++i) {
    for (size_t j = 0; j < GetSizeX(); ++j) {
      out << m_data[i * GetSizeY() + j] << " ";
    }
    out << '\n';
  }

  return out;
}

std::istream& Sample_int::Load(std::istream& out) {
  size_t x, y;
  out >> x >> y;

  Resize(x, y);

  for (auto& el : m_data)
    out >> el;

  return out;
}

void Sample_int::CheckSquare() const {
  if (!IsSquare())
    throw std::logic_error("Sample is not square");
}