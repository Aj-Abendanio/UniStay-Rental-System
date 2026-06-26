#include "Login.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string GenerateTenantID()
{
    ifstream file("data/tenants.csv");

    if (!file.is_open())
        return "T001";

    string line;
    int count = -1; // Ignore header

    while (getline(file, line))
    {
        count++;
    }

    stringstream id;
    id << "T" << setw(3) << setfill('0') << count + 1;

    return id.str();
}

string GenerateGuardianID()
{
    ifstream file("data/guardians.csv");

    if (!file.is_open())
        return "G001";

    string line;
    int count = -1;

    while (getline(file, line))
    {
        count++;
    }

    stringstream id;
    id << "G" << setw(3) << setfill('0') << count + 1;

    return id.str();
}

bool AuthenticateAdmin()
{
    string username;
    string password;

    cout << "\n===== Admin Login =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

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
    string username;
    string password;

    cout << "\n===== Tenant Login =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    ifstream file("data/tenants.csv");

    if (!file.is_open())
    {
        cout << "Unable to open tenants.csv\n";
        return false;
    }

    string line;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        string age;

        getline(ss, currentTenant.tenantID, ',');
        getline(ss, currentTenant.username, ',');
        getline(ss, currentTenant.password, ',');
        getline(ss, currentTenant.unitID, ',');
        getline(ss, age, ',');

        currentTenant.age = stoi(age);

        if (username == currentTenant.username &&
            password == currentTenant.password)
        {
            cout << "Login successful.\n";
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}

bool RegisterTenant()
{
    Tenant newTenant;

    cout << "\n===== Tenant Registration =====\n";

    cout << "Username: ";
    cin >> newTenant.username;

    cout << "Password: ";
    cin >> newTenant.password;

    cout << "Unit ID: ";
    cin >> newTenant.unitID;

    cout << "Age: ";
    cin >> newTenant.age;

    ifstream checkFile("data/tenants.csv");

    if (!checkFile.is_open())
    {
        cout << "Unable to open tenants.csv\n";
        return false;
    }

    string line;

    getline(checkFile, line);

    while (getline(checkFile, line))
    {
        stringstream ss(line);

        string tenantID;
        string username;
        string password;
        string unitID;
        string age;

        getline(ss, tenantID, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, unitID, ',');
        getline(ss, age, ',');

        if (username == newTenant.username)
        {
            cout << "Username already exists.\n";
            return false;
        }
    }

    checkFile.close();

    newTenant.tenantID = GenerateTenantID();

    ofstream tenantFile("data/tenants.csv", ios::app);

    if (!tenantFile.is_open())
    {
        cout << "Unable to open tenants.csv\n";
        return false;
    }

    tenantFile << newTenant.tenantID << ","
               << newTenant.username << ","
               << newTenant.password << ","
               << newTenant.unitID << ","
               << newTenant.age << "\n";

    tenantFile.close();

    if (newTenant.age < 18)
    {
        string guardianID = GenerateGuardianID();
        string guardianName;
        string guardianPhone;

        cin.ignore();

        cout << "\nTenant is under 18.\n";
        cout << "Guardian Name: ";
        getline(cin, guardianName);

        cout << "Guardian Phone: ";
        getline(cin, guardianPhone);

        ofstream guardianFile("data/guardians.csv", ios::app);

        if (!guardianFile.is_open())
        {
            cout << "Unable to open guardians.csv\n";
            return false;
        }

        guardianFile << guardianID << ","
                     << newTenant.tenantID << ","
                     << guardianName << ","
                     << guardianPhone << "\n";

        guardianFile.close();
    }

    cout << "Registration successful.\n";
    cout << "Assigned Tenant ID: " << newTenant.tenantID << "\n";

    return true;
}
