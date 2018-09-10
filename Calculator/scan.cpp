#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include "scan.h"

using namespace std;

regex num_int_matcher("-?[[:digit:]]+");
regex num_float_matcher("-?[0-9]*\.?[0-9]+");
regex name_matcher("[a-zA-Z0-9_]+");

int scan (const char * in, TokenCache & tc)
{
    stringstream ss(in);

    // TODO
    // Get a chain to store tokens in from the
    // TokenCache.

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
            // TODO convert to int value
        }
        else if (regex_match(t, num_float_matcher)) {
            token.type = NUM_FLOAT;
            // TODO convert to float value
        }
        else if (regex_match(t, name_matcher)) {
            token.type = NAME;
        }
        else {
            // TODO not recognized; throw
        }
        cout << token.type << " ";
    }
    cout << endl;
    return 0;
}
