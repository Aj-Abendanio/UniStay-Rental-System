#ifndef LOGIN_H
#define LOGIN_H

#include <string>

struct Tenant
{
    std::string username;
    std::string password;
    std::string tenantID;
    std::string unitID;
};

bool AuthenticateAdmin();
bool AuthenticateTenant(Tenant& currentTenant);
bool RegisterTenant();

#endif
