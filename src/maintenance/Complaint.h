#ifndef COMPLAINT_H
#define COMPLAINT_H

#include <string>
#include <queue>

struct Complaint {
    std::string complaintID;
    std::string tenantID;
    std::string unitID;
    std::string description;
    std::string status;
    
    Complaint() : status("Pending") {}
    Complaint(std::string id, std::string tID, std::string uID, 
              std::string desc, std::string stat = "Pending")
        : complaintID(id), tenantID(tID), unitID(uID), 
          description(desc), status(stat) {}
};

extern std::queue<Complaint> complaintQueue;

bool LoadComplaints();
bool SaveComplaints();
void SubmitComplaint(const std::string& tenantID);
void ProcessComplaints();
void ViewComplaints();
void ViewTenantComplaints(const std::string& tenantID);
std::string GenerateComplaintID();

#endif