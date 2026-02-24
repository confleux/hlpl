#include "menu.h"

int main() {
    int choice;
    double x, y;
    std::string filename;

    while (true) {
        std::cout << "\n=== Menu ===" << std::endl;
        std::cout << "1. Square" << std::endl;
        std::cout << "2. Circle" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 3) {
            break;
        }

        if (choice != 1 && choice != 2) {
            std::cout << "Invalid choice!" << std::endl;
            continue;
        }

        std::cout << "Input method: 1 - Keyboard, 2 - File: ";
        int inputMethod;
        std::cin >> inputMethod;

        if (inputMethod == 2) {
            std::cout << "Enter filename: ";
            std::cin >> filename;
            inputFile(x, y, filename);
        } else {
            inputKeyboard(x, y);
        }

        bool result;
        std::string regionName;

        if (choice == 1) {
            result = inSquare(x, y);
            regionName = "square";
        } else {
            result = inCircle(x, y);
            regionName = "circle";
        }

        printResultScreen(result, regionName, x, y);
        printResultFile(result, regionName, x, y, "output.txt");
    }

    return 0;
}
