#include "Complaint.h"
#include "../users/Tenant.h"
#include "../property/Unit.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <ctime>

using namespace std;

queue<Complaint> complaintQueue;

bool LoadComplaints() {
    ifstream file("data/complaints.csv");
    if (!file.is_open()) {
        ofstream newFile("data/complaints.csv");
        if (newFile.is_open()) {
            newFile << "ComplaintID,TenantID,UnitID,Description,Status\n";
            newFile.close();
        }
        return true;
    }
    
    string line;
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        Complaint c;
        getline(ss, c.complaintID, ',');
        getline(ss, c.tenantID, ',');
        getline(ss, c.unitID, ',');
        getline(ss, c.description, ',');
        getline(ss, c.status, ',');
        
        if (c.status == "Pending" || c.status == "In Progress") {
            complaintQueue.push(c);
        }
    }
    
    file.close();
    return true;
}

bool SaveComplaints() {
    ofstream file("data/complaints.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to save complaints.\n";
        return false;
    }
    
    file << "ComplaintID,TenantID,UnitID,Description,Status\n";
    
    queue<Complaint> tempQueue = complaintQueue;
    while (!tempQueue.empty()) {
        Complaint c = tempQueue.front();
        tempQueue.pop();
        file << c.complaintID << "," << c.tenantID << "," 
             << c.unitID << "," << c.description << "," 
             << c.status << "\n";
    }
    
    file.close();
    return true;
}

string GenerateComplaintID() {
    int count = complaintQueue.size();
    stringstream ss;
    ss << "CMP" << setfill('0') << setw(4) << (count + 1);
    return ss.str();
}

void SubmitComplaint(const string& tenantID) {
    auto it = tenantDatabase.find(tenantID);
    if (it == tenantDatabase.end()) {
        cout << "Error: Tenant not found.\n";
        return;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Complaint newComplaint;
    newComplaint.complaintID = GenerateComplaintID();
    newComplaint.tenantID = tenantID;
    newComplaint.unitID = it->second.unitID;
    newComplaint.status = "Pending";
    
    cout << "\n===== Submit Complaint =====\n";
    cout << "Complaint ID: " << newComplaint.complaintID << "\n";
    cout << "Tenant ID: " << tenantID << "\n";
    cout << "Unit ID: " << newComplaint.unitID << "\n";
    
    cout << "Describe the issue:\n";
    getline(cin, newComplaint.description);
    
    if (newComplaint.description.empty()) {
        cout << "Description cannot be empty.\n";
        return;
    }
    
    complaintQueue.push(newComplaint);
    SaveComplaints();
    
    cout << "\nComplaint submitted successfully.\n";
    cout << "Complaint ID: " << newComplaint.complaintID << "\n";
}

void ProcessComplaints() {
    if (complaintQueue.empty()) {
        cout << "\nNo complaints to process.\n";
        return;
    }
    
    Complaint currentComplaint = complaintQueue.front();
    
    cout << "\n===== Process Complaint =====\n";
    cout << "Complaint ID: " << currentComplaint.complaintID << "\n";
    cout << "Tenant ID: " << currentComplaint.tenantID << "\n";
    cout << "Unit ID: " << currentComplaint.unitID << "\n";
    cout << "Description: " << currentComplaint.description << "\n";
    cout << "Status: " << currentComplaint.status << "\n\n";
    
    cout << "Is this complaint resolved? (y/n): ";
    string input;
    cin >> input;
    
    complaintQueue.pop();
    
    if (input == "y" || input == "Y") {
        cout << "\nComplaint resolved.\n";
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } else if (input == "n" || input == "N") {
        currentComplaint.status = "In Progress";
        
        queue<Complaint> newQueue;
        newQueue.push(currentComplaint);
        
        while (!complaintQueue.empty()) {
            newQueue.push(complaintQueue.front());
            complaintQueue.pop();
        }
        
        complaintQueue = newQueue;
        
        cout << "\nComplaint marked as in progress.\n";
    } else {
        queue<Complaint> newQueue;
        newQueue.push(currentComplaint);
        
        while (!complaintQueue.empty()) {
            newQueue.push(complaintQueue.front());
            complaintQueue.pop();
        }
        
        complaintQueue = newQueue;
        
        cout << "\nInvalid input. Complaint returned to queue.\n";
    }
    
    SaveComplaints();
}

void ViewComplaints() {
    if (complaintQueue.empty()) {
        cout << "\nNo complaints.\n";
        return;
    }
    
    cout << "\n===== Complaints =====\n";
    cout << "Total: " << complaintQueue.size() << "\n\n";
    
    queue<Complaint> tempQueue = complaintQueue;
    int position = 1;
    while (!tempQueue.empty()) {
        Complaint c = tempQueue.front();
        tempQueue.pop();
        cout << position << ". ID: " << c.complaintID << "\n";
        cout << "   Tenant: " << c.tenantID << "\n";
        cout << "   Unit: " << c.unitID << "\n";
        cout << "   Issue: " << c.description << "\n";
        cout << "   Status: " << c.status << "\n\n";
        position++;
    }
}

void ViewTenantComplaints(const string& tenantID) {
    bool found = false;
    
    cout << "\n===== Your Complaints =====\n";
    
    queue<Complaint> tempQueue = complaintQueue;
    while (!tempQueue.empty()) {
        Complaint c = tempQueue.front();
        tempQueue.pop();
        if (c.tenantID == tenantID) {
            found = true;
            cout << "ID: " << c.complaintID << "\n";
            cout << "Unit: " << c.unitID << "\n";
            cout << "Issue: " << c.description << "\n";
            cout << "Status: " << c.status << "\n\n";
        }
    }
    
    if (!found) {
        cout << "No complaints found.\n";
    }
}