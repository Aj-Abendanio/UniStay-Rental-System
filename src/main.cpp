```cpp
#include <iostream>
#include <string>

#include "authentication/Login.h"
#include "property/Unit.h"
#include "maintenance/Maintenance.h"
#include "billing/Payment.h"

using namespace std;

void DisplayMainMenu()
{
    cout << "\n===== UniStay MAIN MENU =====\n";
    cout << "1. Admin Portal\n";
    cout << "2. Tenant Portal\n";
    cout << "3. Register Tenant\n";
    cout << "4. Save & Exit\n";
    cout << "Choice: ";
}

void DisplayAdminMenu()
{
    cout << "\n--- Admin Portal ---\n";
    cout << "1. View All Units\n";
    cout << "2. Process Payment\n";
    cout << "3. View/Resolve Maintenance\n";
    cout << "4. Undo Last Payment\n";
    cout << "5. Logout\n";
    cout << "Choice: ";
}

void DisplayTenantMenu()
{
    cout << "\n--- Tenant Portal ---\n";
    cout << "1. View My Details\n";
    cout << "2. Report Maintenance Issue\n";
    cout << "3. Logout\n";
    cout << "Choice: ";
}

void AdminPortal()
{
    if (!AuthenticateAdmin())
        return;

    bool adminActive = true;

    while (adminActive)
    {
        DisplayAdminMenu();

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            cout << "\n--- All Units ---\n";

            for (const auto& pair : unitDatabase)
            {
                cout << "Unit "
                     << pair.first
                     << ": Balance $"
                     << pair.second
                     << "\n";
            }
        }
        else if (choice == "2")
        {
            string unitID;
            float amount;

            cout << "Enter Unit ID: ";
            cin >> unitID;

            cout << "Enter payment amount: ";
            cin >> amount;

            auto it = unitDatabase.find(unitID);

            if (it != unitDatabase.end())
            {
                undoStack.push({"PAYMENT", unitID, it->second});

                it->second -= amount;

                cout << "Payment processed.\n";
                cout << "New balance: $" << it->second << "\n";
            }
            else
            {
                cout << "Unit not found.\n";
            }
        }
        else if (choice == "3")
        {
            if (!maintenanceQueue.empty())
            {
                string task = maintenanceQueue.front();
                maintenanceQueue.pop();

                cout << "Resolving: " << task << "\n";
            }
            else
            {
                cout << "No maintenance requests pending.\n";
            }
        }
        else if (choice == "4")
        {
            if (!undoStack.empty())
            {
                Action act = undoStack.top();
                undoStack.pop();

                unitDatabase[act.unitID] = act.oldValue;

                cout << "Undo successful.\n";
            }
            else
            {
                cout << "Nothing to undo.\n";
            }
        }
        else if (choice == "5")
        {
            adminActive = false;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}

void TenantPortal()
{
    Tenant currentTenant;

    if (!AuthenticateTenant(currentTenant))
        return;

    string myID = currentTenant.unitID;

    bool tenantActive = true;

    while (tenantActive)
    {
        DisplayTenantMenu();

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            auto it = unitDatabase.find(myID);

            if (it != unitDatabase.end())
            {
                cout << "Unit "
                     << myID
                     << " Balance: $"
                     << it->second
                     << "\n";
            }
        }
        else if (choice == "2")
        {
            cin.ignore();

            string issue;

            cout << "Describe the issue: ";
            getline(cin, issue);

            maintenanceQueue.push(
                "Unit " + myID + ": " + issue
            );

            cout << "Maintenance request submitted.\n";
        }
        else if (choice == "3")
        {
            tenantActive = false;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}

int main()
{
    LoadDataFromCSV();

    bool running = true;

    while (running)
    {
        DisplayMainMenu();

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            AdminPortal();
        }
        else if (choice == "2")
        {
            TenantPortal();
        }
        else if (choice == "3")
        {
            RegisterTenant();
        }
        else if (choice == "4")
        {
            SaveDataToCSV();
            running = false;
        }
        else
        {
            cout << "Invalid selection.\n";
        }
    }

    cout << "Program terminated.\n";

    return 0;
}
```
