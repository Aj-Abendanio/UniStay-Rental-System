#include <iostream>
#include <string>

#include "authentication/Login.h"
#include "property/Unit.h"
#include "users/Admin.h"
#include "users/Tenant.h"

using namespace std;

void DisplayMainMenu()
{
    cout << "\n===== UniStay MAIN MENU =====\n";
    cout << "1. Admin Login\n";
    cout << "2. Tenant Login\n";
    cout << "3. Register Tenant\n";
    cout << "4. Exit\n";
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

void AdminPortal() {
    if (!AuthenticateAdmin()) return;
    bool adminActive = true;
    while (adminActive) {
        cout << "\n--- Admin Portal ---\n";
        cout << "1. View All Units\n";
        cout << "2. Add Unit\n";
        cout << "3. Remove Unit\n";
        cout << "4. Remove Tenant\n";
        cout << "5. Process Payment\n";
        cout << "6. Undo Payment\n";
        cout << "7. Manage Complaints\n";
        cout << "8. Logout\n";
        cout << "Choice: ";
        string choice;
        cin >> choice;
        if (choice == "1") {
            ViewAllUnits();
        } else if (choice == "2") {
            AddUnit();
        } else if (choice == "3") {
            RemoveUnit();
        } else if (choice == "4") {
            RemoveTenant();
        } else if (choice == "5") {
            ProcessPayment();
        } else if (choice == "6") {
            UndoPayment();
        } else if (choice == "7") {
            bool complaintActive = true;
            while (complaintActive) {
                cout << "\n--- Complaint Management ---\n";
                cout << "1. View Complaints\n";
                cout << "2. Process Complaint\n";
                cout << "3. Return\n";
                cout << "Choice: ";
                string cchoice;
                cin >> cchoice;
                
                if (cchoice == "1") {
                    ViewComplaints();
                } else if (cchoice == "2") {
                    ProcessComplaints();
                } else if (cchoice == "3") {
                    complaintActive = false;
                } else {
                    cout << "Invalid selection.\n";
                }
            }
        } else if (choice == "8") {
            adminActive = false;
        } else {
            cout << "Invalid selection.\n";
        }
    }
}

void TenantPortal() {
    Tenant currentTenant;
    if (!AuthenticateTenant(currentTenant)) return;
    bool tenantActive = true;
    while (tenantActive) {
        DisplayTenantMenu();
        string choice;
        cin >> choice;
        if (choice == "1") {
            ViewMyDetails(currentTenant);
        } else if (choice == "2") {
            TenantComplaintMenu(currentTenant);
        } else if (choice == "3") {
            tenantActive = false;
        } else {
            cout << "Invalid selection.\n";
        }
    }
}

int main() {
    LoadUnits();
    LoadTenants();
    LoadComplaints();
    
    bool running = true;
    while (running) {
        DisplayMainMenu();
        string choice;
        cin >> choice;
        if (choice == "1") {
            AdminPortal();
        } else if (choice == "2") {
            TenantPortal();
        } else if (choice == "3") {
            RegisterTenant();
        } else if (choice == "4") {
            SaveUnits();
            SaveTenants();
            SaveComplaints();
            running = false;
        } else {
            cout << "Invalid selection.\n";
        }
    }
    
    cout << "\nProgram terminated.\n";
    return 0;
}