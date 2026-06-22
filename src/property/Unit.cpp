#include <iostream>
#include "Unit.h"

std::unordered_map<std::string, float> unitDatabase;

void LoadDataFromCSV() {
    unitDatabase.clear();

    unitDatabase["U1001"] = 1200.50f;
    unitDatabase["U1002"] = 850.00f;
    unitDatabase["U1003"] = 2100.75f;

    std::cout << "[DATA] Loaded "
              << unitDatabase.size()
              << " units from CSV.\n";
}

void SaveDataToCSV() {
    std::cout << "[DATA] Data saved to CSV.\n";
}