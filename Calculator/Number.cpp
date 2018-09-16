#include "Number.h"

Number operator+ (const Number a, const Number b)
{
    Number result;
    if (a.isInt) {
        if (b.isInt) {
            result.isInt = true;
            result.iVal = a.iVal + b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.iVal + b.fVal;
        }
    }
    else {
        if (b.isInt) {
            result.isFloat = true;
            result.fVal = a.isFloat + b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.isFloat + b.fVal;
        }
    }
    return result;
}

Number operator- (const Number a, const Number b)
{
    Number result;
    if (a.isInt) {
        if (b.isInt) {
            result.isInt = true;
            result.iVal = a.iVal - b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.iVal - b.fVal;
        }
    }
    else {
        if (b.isInt) {
            result.isFloat = true;
            result.fVal = a.isFloat - b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.isFloat - b.fVal;
        }
    }
    return result;
}

Number operator* (const Number a, const Number b)
{
    Number result;
    if (a.isInt) {
        if (b.isInt) {
            result.isInt = true;
            result.iVal = a.iVal * b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.iVal * b.fVal;
        }
    }
    else {
        if (b.isInt) {
            result.isFloat = true;
            result.fVal = a.isFloat * b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.isFloat * b.fVal;
        }
    }
    return result;
}

Number operator/ (const Number a, const Number b)
{
    Number result;
    if (a.isInt) {
        if (b.isInt) {
            result.isInt = true;
            result.iVal = a.iVal / b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.iVal / b.fVal;
        }
    }
    else {
        if (b.isInt) {
            result.isFloat = true;
            result.fVal = a.isFloat / b.iVal;
        }
        else {
            result.isFloat = true;
            result.fVal = a.isFloat / b.fVal;
        }
    }
    return result;
}
