#include <iostream>
#include <sstream>

#include "sample.h"

int main() {
  std::cout << "Testing Sample<int> class\n\n";

  Sample<int> a;
  a.Resize(3);
  std::cout << "After a.Resize(3): "
            << "sizeX=" << a.GetSizeX()
            << ", sizeY=" << a.GetSizeY()
            << ", total=" << a.GetSize()
            << ", IsSquare=" << a.IsSquare()
            << ", IsZeroSize=" << a.IsZeroSize() << "\n";

  a.SetValue(5);
  a(0, 0) = 1;
  a(1, 2) = 10;
  const Sample<int>& ca = a;
  std::cout << "a(1, 2) (const access) = " << ca(1, 2) << "\n";
  std::cout << "GetMax(a) = " << a.GetMax() << "\n";

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

  b.SetValue(1);
  b += 2;
  b *= 3;
  b /= 3;
  std::cout << "b(0, 0) after scalar ops (=3) -> " << b(0, 0) << "\n\n";

  c.SetValue(5);
  b = c;
  std::cout << "After b = c, b(0, 0) = " << b(0, 0) << "\n";

  Sample<int> d;
  d.Resize(b.GetSizeX(), b.GetSizeY());
  d.SetValue(2);

  b += d;
  std::cout << "After b += d, b(0, 0) = " << b(0, 0) << "\n";

  b -= d;
  std::cout << "After b -= d, b(0, 0) = " << b(0, 0) << "\n";

  b *= d;
  std::cout << "After b *= d, b(0, 0) = " << b(0, 0) << "\n\n";

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