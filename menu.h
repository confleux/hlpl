#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <cmath>

const double SquareSize = 1.0;
const double CircleRadius = 1.0;

void inputKeyboard(double& x, double& y);
void inputFile(double& x, double& y, const std::string& filename);
bool inCircle(double x, double y);
bool inSquare(double x, double y);
void printResultScreen(bool result, const std::string& region, double x, double y);
void printResultFile(bool result, const std::string& region, double x, double y, const std::string& filename);

#endif
