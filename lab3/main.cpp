#include <iostream>
#include <sstream>

#include "sample.h"

int main() {
  std::cout << "Testing Sample<int> class\n\n";

  // Resize (square) and basic size checks
  Sample<int> a;
  a.Resize(3);
  std::cout << "After a.Resize(3): "
            << "sizeX=" << a.GetSizeX()
            << ", sizeY=" << a.GetSizeY()
            << ", total=" << a.GetSize()
            << ", IsSquare=" << a.IsSquare()
            << ", IsZeroSize=" << a.IsZeroSize() << "\n";

  // SetValue, element access (non-const) and GetMax
  a.SetValue(5);
  a(0, 0) = 1;
  a(1, 2) = 10;
  const Sample<int>& ca = a;
  std::cout << "a(1, 2) (const access) = " << ca(1, 2) << "\n";
  std::cout << "GetMax(a) = " << a.GetMax() << "\n";

  // GetPointer
  int* ptr = a.GetPointer();
  if (ptr) {
    ptr[0] = 100;
  }
  std::cout << "a(0, 0) after GetPointer() modification = " << a(0, 0) << "\n\n";

  // Resize (rectangular) and IsSquare / IsZeroSize / IsEqualSize
  Sample<int> b;
  b.Resize(2, 4);
  std::cout << "After b.Resize(2, 4): "
            << "sizeX=" << b.GetSizeX()
            << ", sizeY=" << b.GetSizeY()
            << ", IsSquare=" << b.IsSquare()
            << ", IsZeroSize=" << b.IsZeroSize() << "\n";

  Sample<int> empty;
  std::cout << "Empty sample: sizeX=" << empty.GetSizeX()
            << ", sizeY=" << empty.GetSizeY()
            << ", IsZeroSize=" << empty.IsZeroSize() << "\n";

  std::cout << "IsEqualSize(a, b) = " << a.IsEqualSize(b) << "\n";

  // Make a new 'c' with same size as b and test IsEqualSize again
  Sample<int> c;
  c.Resize(b.GetSizeX(), b.GetSizeY());
  std::cout << "IsEqualSize(b, c) = " << b.IsEqualSize(c) << "\n\n";

  // Scalar arithmetic operators (+=, *=, /=)
  b.SetValue(1);
  b += 2;  // all elements become 3
  b *= 3;  // all elements become 9
  b /= 3;  // all elements become 3
  std::cout << "b(0, 0) after scalar ops (=3) -> " << b(0, 0) << "\n\n";

  // Assignment and element-wise operations (+=, -=, *= with another Sample)
  c.SetValue(5);
  b = c;
  std::cout << "After b = c, b(0, 0) = " << b(0, 0) << "\n";

  Sample<int> d;
  d.Resize(b.GetSizeX(), b.GetSizeY());
  d.SetValue(2);

  b += d;  // 5 + 2 = 7
  std::cout << "After b += d, b(0, 0) = " << b(0, 0) << "\n";

  b -= d;  // 7 - 2 = 5
  std::cout << "After b -= d, b(0, 0) = " << b(0, 0) << "\n";

  b *= d;  // 5 * 2 = 10
  std::cout << "After b *= d, b(0, 0) = " << b(0, 0) << "\n\n";

  // Save and Load
  std::stringstream ss;
  std::cout << "Saving b to stream:\n";
  b.Save(std::cout);
  b.Save(ss);

  Sample<int> e;
  e.Load(ss);

  std::cout << "\nLoaded e from stream:\n";
  std::cout << "e sizeX=" << e.GetSizeX()
            << ", sizeY=" << e.GetSizeY()
            << ", e(0, 0)=" << e(0, 0)
            << ", GetMax(e)=" << e.GetMax() << "\n";

  return 0;
}