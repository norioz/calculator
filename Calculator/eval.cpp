#include "eval.h"

// TODO might want to change Token into a class so that 
// it can have functions like isOperator and isNumber.

Number eval (Token * root)
{
    if (root->isNumber()) {
        return *(root->getVal());
    }
    if (root->isOperator()) {
        Number valLeft = eval(root->getLeftChild());
        Number valRight = eval(root->getRightChild());

        Number result;
        Token::Type op = root->getType();
        switch (op) {
        case Token::OPER_ADD:
            result = valLeft + valRight;
            break;
        case Token::OPER_SUB:
            result = valLeft - valRight;
            break;
        case Token::OPER_MUL:
            result = valLeft * valRight;
            break;
        case Token::OPER_DIV:
            result = valLeft / valRight;
            break;
        }

        return result;
    }
}
