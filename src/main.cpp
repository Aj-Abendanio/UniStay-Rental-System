#include <iostream>
#include <string>

#include "authentication/Login.h"
#include "property/Unit.h"
#include "maintenance/Maintenance.h"
#include "billing/Payment.h"

void DisplayMainMenu() {
    std::cout << "\n===== UniStay MAIN MENU =====\n";
    std::cout << "1. Admin Portal\n";
    std::cout << "2. Tenant Portal\n";
    std::cout << "3. Save & Exit\n";
    std::cout << "Choice: ";
}

void DisplayAdminMenu() {
    std::cout << "\n--- Admin Portal ---\n";
    std::cout << "1. View All Units\n";
    std::cout << "2. Process Payment\n";
    std::cout << "3. View/Resolve Maintenance\n";
    std::cout << "4. Undo Last Payment\n";
    std::cout << "5. Logout\n";
    std::cout << "Choice: ";
}

void DisplayTenantMenu() {
    std::cout << "\n--- Tenant Portal ---\n";
    std::cout << "1. View My Details\n";
    std::cout << "2. Report Maintenance Issue\n";
    std::cout << "3. Logout\n";
    std::cout << "Choice: ";
}

void AdminPortal() {
    if (!Authenticate()) return;

    bool adminActive = true;

    while (adminActive) {

        DisplayAdminMenu();

        std::string choice;
        std::cin >> choice;

        if (choice == "1") {

            std::cout << "\n--- All Units ---\n";

            for (const auto& pair : unitDatabase) {
                std::cout << "Unit "
                          << pair.first
                          << ": Balance $"
                          << pair.second
                          << "\n";
            }

        }
        else if (choice == "2") {

            std::string unitID;
            float amount;

            std::cout << "Enter Unit ID: ";
            std::cin >> unitID;

            std::cout << "Enter payment amount: ";
            std::cin >> amount;

            auto it = unitDatabase.find(unitID);

            if (it != unitDatabase.end()) {

                undoStack.push({"PAYMENT", unitID, it->second});

                it->second -= amount;

                std::cout << "Payment processed.\n";
                std::cout << "New balance: $" << it->second << "\n";

            } else {

                std::cout << "Unit not found.\n";

            }

        }
        else if (choice == "3") {

            if (!maintenanceQueue.empty()) {

                std::string task = maintenanceQueue.front();
                maintenanceQueue.pop();

                std::cout << "Resolving: " << task << "\n";

            } else {

                std::cout << "No maintenance requests pending.\n";

            }

        }
        else if (choice == "4") {

            if (!undoStack.empty()) {

                Action act = undoStack.top();
                undoStack.pop();

                unitDatabase[act.unitID] = act.oldValue;

                std::cout << "Undo successful.\n";

            } else {

                std::cout << "Nothing to undo.\n";

            }

        }
        else if (choice == "5") {

            adminActive = false;

        }
        else {

            std::cout << "Invalid choice.\n";

        }
    }
}

void TenantPortal() {

    if (!Authenticate()) return;

    std::string myID = "U1001";

    bool tenantActive = true;

    while (tenantActive) {

        DisplayTenantMenu();

        std::string choice;
        std::cin >> choice;

        if (choice == "1") {

            auto it = unitDatabase.find(myID);

            if (it != unitDatabase.end()) {

                std::cout
                    << "Unit "
                    << myID
                    << " Balance: $"
                    << it->second
                    << "\n";

            }

        }
        else if (choice == "2") {

            std::cin.ignore();

            std::string issue;

            std::cout << "Describe the issue: ";
            std::getline(std::cin, issue);

            maintenanceQueue.push(
                "Unit " + myID + ": " + issue
            );

            std::cout << "Maintenance request submitted.\n";

        }
        else if (choice == "3") {

            tenantActive = false;

        }
        else {

            std::cout << "Invalid choice.\n";

        }
    }
}

int main() {

    LoadDataFromCSV();

    bool running = true;

    while (running) {

        DisplayMainMenu();

        std::string choice;
        std::cin >> choice;

        if (choice == "1") {

            AdminPortal();

        }
        else if (choice == "2") {

            TenantPortal();

        }
        else if (choice == "3") {

            SaveDataToCSV();
            running = false;

        }
        else {

            std::cout << "Invalid selection.\n";

        }
    }

    std::cout << "Program terminated.\n";

    return 0;
}