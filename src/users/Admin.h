#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <stack>

struct PaymentAction
{
    std::string unitID;
    double previousBalance;
    double paymentAmount;
};

extern std::stack<PaymentAction> undoStack;

bool AddUnit();
bool RemoveUnit();
bool RemoveTenant();
bool ProcessPayment();
bool UndoPayment();

#endif