#include "Tenant.h"
#include "../property/Unit.h"
#include <iostream>
#include <limits>

using namespace std;

void ViewMyDetails(const Tenant& currentTenant) {
    cout << "\n===== Tenant Information =====\n";
    cout << "Tenant ID : " << currentTenant.tenantID << '\n';
    cout << "Tenant Name : " << currentTenant.tenantName << '\n';
    cout << "Unit ID : " << currentTenant.unitID << '\n';
    cout << "Age : " << currentTenant.age << '\n';
    
    Unit* unit = FindUnit(currentTenant.unitID);
    if (unit != nullptr) {
        cout << "Balance : " << unit->balance << '\n';
        cout << "Status : " << unit->status << '\n';
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TenantComplaintMenu(const Tenant& currentTenant) {
    bool inComplaintMenu = true;
    while (inComplaintMenu) {
        cout << "\n--- Complaint Menu ---\n";
        cout << "1. Submit Complaint\n";
        cout << "2. View My Complaints\n";
        cout << "3. Return\n";
        cout << "Choice: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            SubmitComplaint(currentTenant.tenantID);
        } else if (choice == "2") {
            ViewTenantComplaints(currentTenant.tenantID);
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else if (choice == "3") {
            inComplaintMenu = false;
        } else {
            cout << "Invalid selection.\n";
        }
    }
}