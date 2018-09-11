#include <exception>
#include <regex>
#include <string.h>
#include <sstream>
#include <vector>
#include "scan.h"

using namespace std;

// TODO make appropriately static
regex num_int_matcher("-?[0-9]+");
regex num_float_matcher("-?[0-9]*\.?[0-9]+");
regex name_matcher("[a-zA-Z0-9_]+");

int scan (const char * in, TokenCache & tc)
{
    // TODO copy in and use strtok
    //      this would eliminate allocations
    stringstream ss(in);

    // TODO
    // Get a chain to store tokens in from the
    // TokenCache.

    // TODO it would be good to eliminate this
    //      we already have the storage in TokenCache
    vector<Token> tokens;

    string t;
    while (ss >> t) {
        Token token;
        if (t == "+") {
            token.type = OPER_ADD;
        }
        else if (t == "-") {
            token.type = OPER_SUB;
        }
        else if (t == "*") {
            token.type = OPER_MUL;
        }
        else if (t == "/") {
            token.type = OPER_DIV;
        }
        else if (t == "=") {
            token.type = OPER_ASSN;
        }
        else if (regex_match(t, num_int_matcher)) {
            token.type = NUM_INT;
            token.iVal = atoi(t.c_str);
        }
        else if (regex_match(t, num_float_matcher)) {
            token.type = NUM_FLOAT;
            token.fVal = atof(t.c_str);
        }
        else if (regex_match(t, name_matcher)) {
            token.type = NAME;
        }
        else {
            throw UnrecognizedTokenTypeException(t.c_str);
        }
        tokens.push_back(token);
    }
    return 0;
}

// UnrecognizedTokenTypeException IMPL
UnrecognizedTokenTypeException::UnrecognizedTokenTypeException(const char * text) : m_text(text) {}

const char * UnrecognizedTokenTypeException::getText ()
{
    return m_text;
}

const char * UnrecognizedTokenTypeException::what () const throw()
{
    char result[100];
    strcpy(result, m_text);
    strcat(result, " does not match a TokenType");
    return result;
}
