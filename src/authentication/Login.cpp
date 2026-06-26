#include "Login.h"
#include "../property/Unit.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <cctype>

using namespace std;

// Forward declarations for functions from Unit.h
extern bool UnitExists(const string& unitID);
extern Unit* FindUnit(const string& unitID);
extern bool SaveUnits();

unordered_map<string, Tenant> tenantDatabase;
unordered_map<string, string> tenantNameIndex;

bool IsLettersOnly(const string& text)
{
    if (text.empty())
        return false;

    for (char c : text)
    {
        if (!isalpha(static_cast<unsigned char>(c)) && c != ' ')
            return false;
    }

    return true;
}

bool IsDigitsOnly(const string& text)
{
    if (text.empty())
        return false;

    for (char c : text)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

bool LoadTenants()
{
    tenantDatabase.clear();
    tenantNameIndex.clear();

    ifstream file("data/tenants.csv");

    if (!file.is_open())
    {
        cerr << "Unable to open tenants.csv\n";
        return false;
    }

    string line;

    getline(file, line); // Skip header

    while (getline(file, line))
    {
        Tenant tenant;

        string age;

        stringstream ss(line);

        getline(ss, tenant.tenantID, ',');
        getline(ss, tenant.tenantName, ',');
        getline(ss, tenant.password, ',');
        getline(ss, tenant.unitID, ',');
        getline(ss, age, ',');

        tenant.age = stoi(age);

        tenantDatabase[tenant.tenantID] = tenant;
        tenantNameIndex[tenant.tenantName] = tenant.tenantID;
    }

    file.close();

    return true;
}

bool SaveTenants()
{
    ofstream file("data/tenants.csv");

    if (!file.is_open())
    {
        cerr << "Unable to save tenants.csv\n";
        return false;
    }

    file << "TenantID,TenantName,Password,UnitID,Age\n";

    for (const auto& pair : tenantDatabase)
    {
        const Tenant& tenant = pair.second;

        file << tenant.tenantID << ","
             << tenant.tenantName << ","
             << tenant.password << ","
             << tenant.unitID << ","
             << tenant.age << "\n";
    }

    file.close();

    return true;
}

string GenerateTenantID()
{
    int highest = 0;

    for (const auto& pair : tenantDatabase)
    {
        string id = pair.second.tenantID.substr(1);

        highest = max(highest, stoi(id));
    }

    stringstream ss;

    ss << "T"
       << setw(3)
       << setfill('0')
       << highest + 1;

    return ss.str();
}

string GenerateGuardianID()
{
    ifstream file("data/guardians.csv");

    if (!file.is_open())
        return "G001";

    string line;

    int count = 0;

    while (getline(file, line))
        count++;

    stringstream ss;

    ss << "G"
       << setw(3)
       << setfill('0')
       << count;

    return ss.str();
}

bool AuthenticateAdmin()
{
    string username;
    string password;

    cout << "\n===== Admin Login =====\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    if (username == "admin" && password == "admin123")
    {
        cout << "Admin login successful.\n";
        return true;
    }

    cout << "Invalid admin credentials.\n";
    return false;
}

bool AuthenticateTenant(Tenant& currentTenant)
{
    string tenantName;
    string password;

    cout << "\n===== Tenant Login =====\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Tenant Name: ";
    getline(cin, tenantName);

    cout << "Password: ";
    getline(cin, password);

    auto index = tenantNameIndex.find(tenantName);

    if (index == tenantNameIndex.end())
    {
        cout << "Tenant not found.\n";
        return false;
    }

    auto tenant = tenantDatabase.find(index->second);

    if (tenant == tenantDatabase.end())
    {
        cout << "Tenant not found.\n";
        return false;
    }

    if (tenant->second.password != password)
    {
        cout << "Incorrect password.\n";
        return false;
    }

    currentTenant = tenant->second;

    cout << "Login successful.\n";

    return true;
}

bool RegisterTenant()
{
    Tenant newTenant;

    cout << "\n===== Tenant Registration =====\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get tenant name
    while (true)
    {
        cout << "Tenant Name: ";
        getline(cin, newTenant.tenantName);

        if (!IsLettersOnly(newTenant.tenantName))
        {
            cout << "Invalid name. Letters and spaces only.\n";
            continue;
        }

        if (tenantNameIndex.find(newTenant.tenantName) != tenantNameIndex.end())
        {
            cout << "Tenant name already exists.\n";
            continue;
        }

        break;
    }

    // Get password
    while (true)
    {
        cout << "Password: ";
        getline(cin, newTenant.password);

        if (!newTenant.password.empty())
            break;

        cout << "Password cannot be empty.\n";
    }

    // Get Unit ID
    while (true)
    {
        cout << "Unit ID: ";
        getline(cin, newTenant.unitID);

        if (newTenant.unitID.empty())
        {
            cout << "Unit ID cannot be empty.\n";
            continue;
        }

        if (!UnitExists(newTenant.unitID))
        {
            cout << "Unit does not exist.\n";
            continue;
        }

        Unit* unit = FindUnit(newTenant.unitID);

        if (unit == nullptr)
        {
            cout << "Error finding unit.\n";
            continue;
        }

        if (unit->status == "Occupied")
        {
            cout << "That unit is already occupied.\n";
            continue;
        }

        break;
    }

    // Get age
    while (true)
    {
        string input;

        cout << "Age: ";
        getline(cin, input);

        if (IsDigitsOnly(input))
        {
            newTenant.age = stoi(input);

            if (newTenant.age > 0 && newTenant.age <= 120)
                break;
        }

        cout << "Invalid age. Must be between 1 and 120.\n";
    }

    // Generate ID and save
    newTenant.tenantID = GenerateTenantID();

    tenantDatabase[newTenant.tenantID] = newTenant;
    tenantNameIndex[newTenant.tenantName] = newTenant.tenantID;

    SaveTenants();

    // Update unit status
    Unit* unit = FindUnit(newTenant.unitID);

    if (unit != nullptr)
    {
        unit->status = "Occupied";
        unit->balance = unit->rent;

        SaveUnits();
    }

    // Handle guardians for minors
    if (newTenant.age < 18)
    {
        string guardianID = GenerateGuardianID();
        string guardianName;
        string guardianPhone;

        cout << "\nTenant is under 18. Guardian information required.\n";

        while (true)
        {
            cout << "Guardian Name: ";
            getline(cin, guardianName);

            if (IsLettersOnly(guardianName))
                break;

            cout << "Invalid guardian name. Letters and spaces only.\n";
        }

        while (true)
        {
            cout << "Guardian Phone: ";
            getline(cin, guardianPhone);

            if (IsDigitsOnly(guardianPhone))
                break;

            cout << "Invalid phone number. Numbers only.\n";
        }

        ofstream guardianFile("data/guardians.csv", ios::app);

        if (!guardianFile.is_open())
        {
            cerr << "Unable to open guardians.csv\n";
            return false;
        }

        guardianFile << guardianID << ","
                     << newTenant.tenantID << ","
                     << guardianName << ","
                     << guardianPhone << "\n";

        guardianFile.close();
    }

    cout << "\nRegistration successful.\n";
    cout << "Assigned Tenant ID: " << newTenant.tenantID << "\n";

    return true;
}