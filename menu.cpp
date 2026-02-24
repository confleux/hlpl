#include "menu.h"

void inputKeyboard(double& x, double& y) {
    std::cout << "Enter coordinates (x y): ";
    std::cin >> x >> y;
}

void inputFile(double& x, double& y, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> x >> y;
        file.close();
    } else {
        throw std::runtime_error("Error opening file to read");
    }
}

bool inCircle(double x, double y) {
    return (x * x + y * y) <= (CircleRadius * CircleRadius);
}

bool inSquare(double x, double y) {
    return (x >= -SquareSize && x <= SquareSize) && (y >= -SquareSize && y <= SquareSize);
}

void printResultScreen(bool result, const std::string& region, double x, double y) {
    std::cout << "Point (" << x << ", " << y << ") ";
    if (result) {
        std::cout << "is in " << region << std::endl;
    } else {
        std::cout << "is not in " << region << std::endl;
    }
}

void printResultFile(bool result, const std::string& region, double x, double y, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Point (" << x << ", " << y << ") ";
        if (result) {
            file << "is in " << region << std::endl;
        } else {
            file << "is not in " << region << std::endl;
        }
        file.close();
    } else {
        throw std::runtime_error("Error opening file to write");
    }
}
