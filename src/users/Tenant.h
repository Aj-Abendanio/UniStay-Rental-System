#ifndef TENANT_H
#define TENANT_H

#include "../authentication/Login.h"
#include "../maintenance/Complaint.h"

void ViewMyDetails(const Tenant& currentTenant);
void TenantComplaintMenu(const Tenant& currentTenant);

#endif