//#include <iostream>
//#include <string>
//#include "TokenCache.h"
//#include "scan.h"
//#include "parse.h"
//#include "eval.h"
//
//int main ()
//{
//    // allocation
//    TokenCache tc;
//    tc.init(10, 20);
//
//    // read a line of text
//    std::string lineStr;
//    std::getline(std::cin, lineStr);
//    const char * line = lineStr.c_str();
//
//    // scan the line
//    int tcid = scan(line, tc);
//    
//    // make a parse tree from the tokens
//    Token * rootPtr = parse(tc, tcid);
//
//    // execute the calculation
//    Number result = eval(rootPtr);
//
//    std::cout << (result.isInt ? result.iVal : result.fVal) << std::endl;
//    system("PAUSE");
//    return 0;
//}
