#include <iostream>
#include <string>

#include "authentication/Login.h"
#include "property/Unit.h"
#include "users/Admin.h"
#include "users/Tenant.h"

using namespace std;

void ClearScreen() {
    system("cls");
}

void Pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void Divider() {
    cout << "============================================================\n";
}

void DisplayMainMenu() {
    ClearScreen();

    Divider();
    cout << "               UNISTAY RENTAL SYSTEM\n";
    Divider();

    cout << "\n";
    cout << "                 MAIN MENU\n";
    cout << "\n";

    cout << "  [1] Administrator Login\n";
    cout << "  [2] Tenant Login\n";
    cout << "  [3] Register New Tenant\n";
    cout << "  [4] Exit\n";

    cout << "\n";
    Divider();
    cout << " Enter your choice: ";
}

void DisplayTenantMenu() {
    ClearScreen();

    Divider();
    cout << "                  TENANT PORTAL\n";
    Divider();

    cout << "\n";
    cout << "  [1] View My Details\n";
    cout << "  [2] Report Maintenance Issue\n";
    cout << "  [3] Logout\n";

    cout << "\n";
    Divider();
    cout << " Enter your choice: ";
}

void AdminPortal() {
    if (!AuthenticateAdmin()) return;
    bool adminActive = true;
    while (adminActive) {
        ClearScreen();

        Divider();
        cout << "                 ADMIN DASHBOARD\n";
        Divider();

        cout << "\n";
        cout << " PROPERTY MANAGEMENT\n";
        cout << " ------------------------------\n";
        cout << "  [1] View All Units\n";
        cout << "  [2] Add Unit\n";
        cout << "  [3] Remove Unit\n";

        cout << "\n";
        cout << " TENANT MANAGEMENT\n";
        cout << " ------------------------------\n";
        cout << "  [4] Remove Tenant\n";

        cout << "\n";
        cout << " BILLING\n";
        cout << " ------------------------------\n";
        cout << "  [5] Process Payment\n";
        cout << "  [6] Undo Payment\n";

        cout << "\n";
        cout << " MAINTENANCE\n";
        cout << " ------------------------------\n";
        cout << "  [7] Manage Complaints\n";

        cout << "\n";
        cout << " SYSTEM\n";
        cout << " ------------------------------\n";
        cout << "  [8] Logout\n";

        cout << "\n";
        Divider();

        cout << " Enter your choice: ";
        string choice;
        cin >> choice;
        if (choice == "1") {
            ClearScreen();
            ViewAllUnits();
            Pause();
        } else if (choice == "2") {
            ClearScreen();
            AddUnit();
            Pause();
        } else if (choice == "3") {
            ClearScreen();
            RemoveUnit();
            Pause();
        } else if (choice == "4") {
            ClearScreen();
            RemoveTenant();
            Pause();
        } else if (choice == "5") {
            ClearScreen();
            ProcessPayment();
            Pause();
        } else if (choice == "6") {
            ClearScreen();
            UndoPayment();
            Pause();
        } else if (choice == "7") {
            bool complaintActive = true;
            while (complaintActive) {
                ClearScreen();

                Divider();
                cout << "             COMPLAINT MANAGEMENT\n";
                Divider();

                cout << "\n";
                cout << "  [1] View Complaints\n";
                cout << "  [2] Process Complaint\n";
                cout << "  [3] Return\n";

                cout << "\n";
                Divider();
                cout << " Enter your choice: ";
                string cchoice;
                cin >> cchoice;
                
                if (cchoice == "1") {
                    ClearScreen();
                    ViewComplaints();
                    Pause();
                } else if (cchoice == "2") {
                    ClearScreen();
                    ProcessComplaints();
                    Pause();
                } else if (cchoice == "3") {
                    complaintActive = false;
                } else {
                    cout << "\nInvalid selection.\n";
                    Pause();
                }
            }
        } else if (choice == "8") {
            adminActive = false;
        } else {
            cout << "\nInvalid selection.\n";
            Pause();
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
            ClearScreen();
            ViewMyDetails(currentTenant);
            Pause();
        } else if (choice == "2") {
            ClearScreen();
            TenantComplaintMenu(currentTenant);
            Pause();
        } else if (choice == "3") {
            tenantActive = false;
        } else {
            cout << "\nInvalid selection.\n";
            Pause();
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
            ClearScreen();
            RegisterTenant();
            Pause();
        } else if (choice == "4") {
            SaveUnits();
            SaveTenants();
            SaveComplaints();
            running = false;
        } else {
            cout << "\nInvalid selection.\n";
            Pause();
        }
    }
    
    ClearScreen();

    Divider();
    cout << "      Thank you for using UniStay Rental System\n";
    Divider();

    cout << "\nSaving system data...\n";
    cout << "Goodbye!\n\n";
    return 0;
}