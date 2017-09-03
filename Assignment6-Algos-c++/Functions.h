#pragma once

#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cstdint>
#include <stdint.h>
using namespace std;

void SelectFile();
void ReadFile(string aFileName);

void search(string aText, string aKey);
void hashVal(int aVar, string aText, int aIndex);