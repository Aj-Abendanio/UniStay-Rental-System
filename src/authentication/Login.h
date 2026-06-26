#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <unordered_map>

struct Tenant
{
    std::string tenantID;
    std::string tenantName;
    std::string password;
    std::string unitID;
    int age;
};

extern std::unordered_map<std::string, Tenant> tenantDatabase;
extern std::unordered_map<std::string, std::string> tenantNameIndex;

bool LoadTenants();
bool SaveTenants();

bool AuthenticateAdmin();
bool AuthenticateTenant(Tenant& currentTenant);
bool RegisterTenant();

#endif