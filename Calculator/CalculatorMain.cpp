#include <iostream>
#include <string>
#include "TokenCache.h"
#include "scan.h"
#include "parse.h"

int main ()
{
    // allocation
    TokenCache tc;
    tc.init(10, 20);

    // read a line of text
    std::string lineStr;
    std::getline(std::cin, lineStr);
    const char * line = lineStr.c_str();

    // scan the line
    int tcid = scan(line, tc);
    
    std::cout << tcid;

    // make a parse tree from the tokens
    //parse(tc.getChain(tcid), tc.getChainLength(tcid));

    // execute the calculation
    // TODO

    system("PAUSE");
    return 0;
}