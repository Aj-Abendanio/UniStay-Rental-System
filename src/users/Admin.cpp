#include "Admin.h"
#include "../authentication/Login.h"
#include "../property/Unit.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

stack<PaymentAction> undoStack;

bool AddUnit()
{
    Unit newUnit;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        cout << "\nEnter Unit ID: ";
        getline(cin, newUnit.unitID);

        if (newUnit.unitID.empty())
        {
            cout << "Unit ID cannot be empty.\n";
            continue;
        }

        if (UnitExists(newUnit.unitID))
        {
            cout << "Unit already exists.\n";
            continue;
        }

        break;
    }

    string input;

while (true)
{
    cout << "Monthly Rent: ";
    getline(cin, input);

    try
    {
        newUnit.rent = stod(input);

        if (newUnit.rent >= 0)
            break;
    }
    catch (...)
    {
    }

    cout << "Invalid rent amount.\n";
}

newUnit.balance = 0;
newUnit.status = "Vacant";

    unitDatabase[newUnit.unitID] = newUnit;

    SaveUnits();

    cout << "\nUnit successfully added.\n";

    return true;
}

bool RemoveUnit()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string unitID;

    cout << "\nEnter Unit ID to remove: ";
    getline(cin, unitID);

    auto it = unitDatabase.find(unitID);

    if (it == unitDatabase.end())
    {
        cout << "Unit not found.\n";
        return false;
    }

    if (it->second.status == "Occupied")
    {
        cout << "Cannot remove an occupied unit.\n";
        return false;
    }

    unitDatabase.erase(it);

    SaveUnits();

    cout << "Unit removed successfully.\n";

    return true;
}

bool RemoveTenant()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string tenantID;

    cout << "\nEnter Tenant ID: ";
    getline(cin, tenantID);

    auto it = tenantDatabase.find(tenantID);

    if (it == tenantDatabase.end())
    {
        cout << "Tenant not found.\n";
        return false;
    }

    string unitID = it->second.unitID;

    tenantNameIndex.erase(it->second.tenantName);

    tenantDatabase.erase(it);

    SaveTenants();

    ifstream guardianFile("data/guardians.csv");

    if (guardianFile.is_open())
    {
        vector<string> guardians;

        string line;

        getline(guardianFile, line);

        guardians.push_back(line);

        while (getline(guardianFile, line))
        {
            stringstream ss(line);

            string guardianID;
            string tenant;
            string guardianName;
            string phone;

            getline(ss, guardianID, ',');
            getline(ss, tenant, ',');
            getline(ss, guardianName, ',');
            getline(ss, phone, ',');

            if (tenant != tenantID)
                guardians.push_back(line);
        }

        guardianFile.close();

        ofstream outFile("data/guardians.csv");

        for (const string& row : guardians)
            outFile << row << '\n';

        outFile.close();
    }

    Unit* unit = FindUnit(unitID);

    if (unit != nullptr)
    {
        unit->status = "Vacant";
        unit->balance = 0;

        SaveUnits();
    }

    cout << "\nTenant removed successfully.\n";

    return true;
}

bool ProcessPayment()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string unitID;

    cout << "\nEnter Unit ID: ";
    getline(cin, unitID);

    Unit* unit = FindUnit(unitID);

    if (unit == nullptr)
    {
        cout << "Unit not found.\n";
        return false;
    }

    // Find tenant occupying this unit
    string tenantID;

    for (const auto& tenant : tenantDatabase)
    {
        if (tenant.second.unitID == unitID)
        {
            tenantID = tenant.first;
            break;
        }
    }

    if (tenantID.empty())
    {
        cout << "No tenant is assigned to this unit.\n";
        return false;
    }

    string input;
    double payment;

    while (true)
    {
        cout << "Enter Payment Amount: ";
        getline(cin, input);

        try
        {
            payment = stod(input);

            if (payment > 0)
                break;
        }
        catch (...)
        {
        }

        cout << "Invalid payment amount.\n";
    }

    // Save current state for Undo
    PaymentAction action;
    action.unitID = unit->unitID;
    action.previousBalance = unit->balance;
    action.paymentAmount = payment;

    undoStack.push(action);

    // Process payment
    unit->balance -= payment;

    if (unit->balance < 0)
        unit->balance = 0;

    SaveUnits();

    // Get today's date
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", local);

    // Generate PaymentID
    int paymentCount = 0;
    string line;

    ifstream inFile("data/payments.csv");

    if (inFile.is_open())
    {
        getline(inFile, line); // Skip header

        while (getline(inFile, line))
            paymentCount++;

        inFile.close();
    }

    string paymentID = "PAY" + to_string(paymentCount + 1);

    // Save payment record
    ofstream outFile("data/payments.csv", ios::app);

    if (outFile.is_open())
    {
        outFile << paymentID << ","
                << tenantID << ","
                << payment << ","
                << date << '\n';

        outFile.close();
    }

    cout << "\nPayment processed successfully.\n";
    cout << "Payment ID: " << paymentID << endl;
    cout << "Date: " << date << endl;
    cout << "Payment: " << payment << endl;
    cout << "Remaining Balance: " << unit->balance << endl;

    return true;
}

bool UndoPayment()
{
    if (undoStack.empty())
    {
        cout << "\nNothing to undo.\n";
        return false;
    }

    PaymentAction action = undoStack.top();
    undoStack.pop();

    Unit* unit = FindUnit(action.unitID);

    if (unit == nullptr)
    {
        cout << "\nUnit no longer exists.\n";
        return false;
    }

    // Restore previous balance
    unit->balance = action.previousBalance;
    SaveUnits();

    // Remove the last payment record from payments.csv
    vector<string> rows;
    string line;

    ifstream inFile("data/payments.csv");

    if (inFile.is_open())
    {
        while (getline(inFile, line))
            rows.push_back(line);

        inFile.close();
    }

    // Keep the header, remove only the last payment row
    if (rows.size() > 1)
        rows.pop_back();

    ofstream outFile("data/payments.csv");

    for (const string& row : rows)
        outFile << row << '\n';

    outFile.close();

    cout << "\nLast payment undone successfully.\n";
    cout << "Restored Balance: " << unit->balance << endl;

    return true;
}

