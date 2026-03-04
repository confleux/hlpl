#include "functions.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <numeric>

void task1Array() {
    std::cout << "Array (double):" << std::endl;
    double* arr = new double[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 10.0;
    }
    std::cout << "Values: ";
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    double sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    double avg = sum / 10;
    std::cout << "Average: " << avg << std::endl;
    delete[] arr;
}

void task2Vector() {
    std::cout << "Vector (int):" << std::endl;
    std::vector<int> vec(15);
    for (int i = 0; i < 15; i++) {
        vec[i] = std::round(rand() % 6);
    }
    std::cout << "Values: ";
    for (int i = 0; i < 15; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void task3VectorAlgorithms() {
    std::cout << "Vector algorithms:" << std::endl;
    std::vector<int> vec(15);
    for (int i = 0; i < 15; i++) {
        vec[i] = std::round(rand() % 6);
    }
    std::cout << "Initial values: ";
    for (int i = 0; i < 15; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    int maxVal = *std::max_element(vec.begin(), vec.end());
    std::cout << "Max element: " << maxVal << std::endl;
    int sumVec = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum of elements: " << sumVec << std::endl;
    vec.erase(std::remove(vec.begin(), vec.end(), 0), vec.end());
    std::cout << "After removing zeros: ";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    std::cout << "After removing duplicates: ";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void task4List() {
    std::cout << "List (double):" << std::endl;
    std::list<double> lst;
    char choice;
    do {
        double num;
        std::cout << "Enter number: ";
        std::cin >> num;
        lst.push_back(num);
        std::cout << "Continue? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    std::cout << "Values: ";
    for (const auto& val : lst) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    double maxAbs = *std::max_element(lst.begin(), lst.end(), 
        [](double a, double b) { return std::abs(a) < std::abs(b); });
    std::cout << "Max absolute value: " << maxAbs << std::endl << std::endl;
}

void task5Map() {
    std::cout << "Map (refractive index):" << std::endl;
    std::map<std::string, double> refractiveIndex;
    std::ifstream inputFile("glass_data.txt");
    if (inputFile.is_open()) {
        std::string name;
        double value;
        while (inputFile >> name >> value) {
            refractiveIndex[name] = value;
        }
        inputFile.close();
    }
    std::cout << "Materials:" << std::endl;
    for (const auto& pair : refractiveIndex) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    auto minIt = std::min_element(refractiveIndex.begin(), refractiveIndex.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    auto maxIt = std::max_element(refractiveIndex.begin(), refractiveIndex.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    std::cout << "Min refractive index: " << minIt->first << " = " << minIt->second << std::endl;
    std::cout << "Max refractive index: " << maxIt->first << " = " << maxIt->second << std::endl;

    std::cout << std::endl;
}

void task6DequeAndSet() {
    std::cout << "Deque and Set:" << std::endl;
    std::deque<int> deq(15);
    for (int i = 0; i < 15; i++) {
        deq[i] = std::round(rand() % 6);
    }
    std::cout << "Deque values: ";
    for (int i = 0; i < 15; i++) {
        std::cout << deq[i] << " ";
    }
    std::cout << std::endl;
    std::set<int> st(deq.begin(), deq.end());
    std::cout << "Set values: ";
    for (const auto& val : st) {
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;
}
