#include "eval.h"

// TODO might want to change Token into a class so that 
// it can have functions like isOperator and isNumber.

Number * eval (Token * root)
{
    if (root->isNumber()) {
        return root->getVal();
    }
    if (root->isOperator()) {
        // TODO This isn't right.
        return root->getVal();
    }
}
