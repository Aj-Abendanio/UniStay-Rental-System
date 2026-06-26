#include "Login.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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

    // Skip header
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        string tenantID;
        string csvUsername;
        string csvPassword;
        string unitID;

        getline(ss, tenantID, ',');
        getline(ss, csvUsername, ',');
        getline(ss, csvPassword, ',');
        getline(ss, unitID, ',');

        if (username == csvUsername && password == csvPassword)
        {
            currentTenant.tenantID = tenantID;
            currentTenant.username = csvUsername;
            currentTenant.password = csvPassword;
            currentTenant.unitID = unitID;

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

    cout << "Tenant ID: ";
    cin >> newTenant.tenantID;

    cout << "Username: ";
    cin >> newTenant.username;

    cout << "Password: ";
    cin >> newTenant.password;

    cout << "Unit ID: ";
    cin >> newTenant.unitID;

    ifstream checkFile("data/tenants.csv");

    if (!checkFile.is_open())
    {
        cout << "Unable to open tenants.csv\n";
        return false;
    }

    string line;

    // Skip header
    getline(checkFile, line);

    while (getline(checkFile, line))
    {
        stringstream ss(line);

        string tenantID;
        string username;
        string password;
        string unitID;

        getline(ss, tenantID, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, unitID, ',');

        if (username == newTenant.username)
        {
            cout << "Username already exists.\n";
            return false;
        }
    }

    checkFile.close();

    ofstream file("data/tenants.csv", ios::app);

    if (!file.is_open())
    {
        cout << "Unable to open tenants.csv\n";
        return false;
    }

    file << newTenant.tenantID << ","
         << newTenant.username << ","
         << newTenant.password << ","
         << newTenant.unitID << "\n";

    file.close();

    cout << "Registration successful.\n";

    return true;
}
