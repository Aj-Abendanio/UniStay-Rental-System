#ifndef PAYMENT_H
#define PAYMENT_H

#include <stack>
#include <string>

struct Action {
    std::string type;
    std::string unitID;
    float oldValue;
};

extern std::stack<Action> undoStack;

#endif