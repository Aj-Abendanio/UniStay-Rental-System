#ifndef LOGIN_H
#define LOGIN_H

#include <string>

struct Tenant
{
    string tenantID;
    string username;
    string password;
    string unitID;
    int age;
};

bool AuthenticateAdmin();
bool AuthenticateTenant(Tenant& currentTenant);
bool RegisterTenant();

#endif
