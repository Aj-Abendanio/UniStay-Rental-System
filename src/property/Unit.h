#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <unordered_map>

struct Unit
{
    std::string unitID;
    double rent;
    double balance;
    std::string status;
};

extern std::unordered_map<std::string, Unit> unitDatabase;

bool LoadUnits();
bool SaveUnits();

void ViewAllUnits();
bool UnitExists(const std::string& unitID);
Unit* FindUnit(const std::string& unitID);

#endif