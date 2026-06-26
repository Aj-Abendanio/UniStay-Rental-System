#include "Unit.h"
#include "../dsa/Sorting.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

unordered_map<string, Unit> unitDatabase;

bool LoadUnits()
{
    unitDatabase.clear();

    ifstream file("data/units.csv");

    if (!file.is_open())
    {
        cerr << "Unable to open units.csv\n";
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        stringstream ss(line);

        Unit unit;
        string rent;
        string balance;

        getline(ss, unit.unitID, ',');
        getline(ss, rent, ',');
        getline(ss, balance, ',');
        getline(ss, unit.status, ',');

       cout << "Line: " << line << endl;
cout << "Rent = [" << rent << "]" << endl;
cout << "Balance = [" << balance << "]" << endl;

try
{
    unit.rent = stod(rent);
    unit.balance = stod(balance);
}
catch (const exception& e)
{
    cout << "stod failed: " << e.what() << endl;
    return false;
}
        unitDatabase[unit.unitID] = unit;
    }

    file.close();
    return true;
}

bool SaveUnits()
{
    ofstream file("data/units.csv");

    if (!file.is_open())
    {
        cerr << "Unable to save units.csv\n";
        return false;
    }

    file << "UnitID,Rent,Balance,Status\n";

    vector<Unit> units;
    units.reserve(unitDatabase.size());

    for (const auto& pair : unitDatabase)
    {
        units.push_back(pair.second);
    }

    SortUnitsByID(units);

    for (const Unit& unit : units)
    {
        file << unit.unitID << ","
             << unit.rent << ","
             << unit.balance << ","
             << unit.status << '\n';
    }

    file.close();

    return true;
}

void ViewAllUnits()
{
    cout << "\n===== Units =====\n\n";

    cout << left
         << setw(10) << "Unit ID"
         << setw(12) << "Rent"
         << setw(12) << "Balance"
         << setw(12) << "Status"
         << '\n';

    cout << "----------------------------------------------\n";

    vector<Unit> units;
    units.reserve(unitDatabase.size());

    for (const auto& pair : unitDatabase)
    {
        units.push_back(pair.second);
    }

    SortUnitsByID(units);

    for (const Unit& unit : units)
    {
        cout << left
             << setw(10) << unit.unitID
             << setw(12) << unit.rent
             << setw(12) << unit.balance
             << setw(12) << unit.status
             << '\n';
    }
}

Unit* FindUnit(const string& unitID)
{
    auto it = unitDatabase.find(unitID);

    if (it == unitDatabase.end())
        return nullptr;

    return &it->second;
}

bool UnitExists(const string& unitID)
{
    return unitDatabase.find(unitID) != unitDatabase.end();
}