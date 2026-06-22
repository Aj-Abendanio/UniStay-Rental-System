#ifndef UNIT_H
#define UNIT_H

#include <unordered_map>
#include <string>

extern std::unordered_map<std::string, float> unitDatabase;

void LoadDataFromCSV();
void SaveDataToCSV();

#endif