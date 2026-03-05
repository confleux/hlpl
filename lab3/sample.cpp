#include "sample.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>

template <class PAR>
void Sample<PAR>::Resize(int size) {
  if (size < 0)
    throw std::invalid_argument("Size must be positive");

  m_size_x = size;
  m_size_y = size;
  m_data.resize(m_size_x * m_size_y);
}

template <class PAR>
void Sample<PAR>::Resize(int size_x, int size_y) {
  if (size_x < 0 || size_y < 0)
    throw std::invalid_argument("Size must be positive");

  m_size_x = size_x;
  m_size_y = size_y;
  m_data.resize(size_x * size_y);
}

template <class PAR>
int Sample<PAR>::GetSize() const {
  return m_size_x * m_size_y;
}

template <class PAR>
int Sample<PAR>::GetSizeX() const {
  return m_size_x;
}

template <class PAR>
int Sample<PAR>::GetSizeY() const {
  return m_size_y;
}

template <class PAR>
PAR& Sample<PAR>::operator()(int i, int j) {
  if (i < 0 || i >= m_size_x || j < 0 || j >= m_size_y)
    throw std::invalid_argument("Invlid index");

  return m_data[i * m_size_x + j];
}

template <class PAR>
const PAR& Sample<PAR>::operator()(int i, int j) const {
  if (i < 0 || i >= m_size_x || j < 0 || j >= m_size_y)
    throw std::invalid_argument("Invlid index");

  return m_data[i * m_size_x + j];
}

template <class PAR>
bool Sample<PAR>::IsSquare() const {
  return m_size_x == m_size_y;
}

template <class PAR>
bool Sample<PAR>::IsZeroSize() const {
  return m_size_x == 0 || m_size_y == 0;
}

template <class PAR>
bool Sample<PAR>::IsEqualSize(const Sample<PAR>& temp) const {
  return m_size_x == temp.GetSizeX() && m_size_y == temp.GetSizeY();
}

template <class PAR>
void Sample<PAR>::SetValue(PAR value) {
  m_data.assign(GetSize(), value);
}

template <class PAR>
PAR* Sample<PAR>::GetPointer() {
  return m_data.data();
}

template <class PAR>
PAR Sample<PAR>::GetMax() const {
  return *std::max_element(m_data.begin(), m_data.end());
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(PAR value) {
  for (auto& el : m_data)
    el += value;

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(PAR value) {
  for (auto& el : m_data)
    el *= value;

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator/=(PAR value) {
  for (auto& el : m_data)
    el /= value;

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator=(const Sample<PAR>& temp) {
  m_data = temp.m_data;
  m_size_x = temp.GetSizeX();
  m_size_y = temp.GetSizeY();

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(const Sample<PAR>& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < static_cast<size_t>(GetSize()); ++i)
    m_data[i] += temp.m_data[i];

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator-=(const Sample<PAR>& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < static_cast<size_t>(GetSize()); ++i)
    m_data[i] -= temp.m_data[i];

  return *this;
}

template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(const Sample<PAR>& temp) {
  if (!IsEqualSize(temp))
    throw std::invalid_argument("Sizes must match");

  for (size_t i = 0; i < static_cast<size_t>(GetSize()); ++i)
    m_data[i] *= temp.m_data[i];

  return *this;
}

template <class PAR>
std::ostream& Sample<PAR>::Save(std::ostream& out) {
  out << GetSizeX() << ' ' << GetSizeY() << '\n';
  for (size_t i = 0; i < static_cast<size_t>(GetSizeY()); ++i) {
    for (size_t j = 0; j < static_cast<size_t>(GetSizeX()); ++j) {
      out << m_data[i * static_cast<size_t>(GetSizeY()) + j] << " ";
    }
    out << '\n';
  }

  return out;
}

template <class PAR>
std::istream& Sample<PAR>::Load(std::istream& out) {
  size_t x, y;
  out >> x >> y;

  Resize(static_cast<int>(x), static_cast<int>(y));

  for (auto& el : m_data)
    out >> el;

  return out;
}

template <class PAR>
void Sample<PAR>::CheckSquare() const {
  if (!IsSquare())
    throw std::logic_error("Sample is not square");
}

template class Sample<int>;

