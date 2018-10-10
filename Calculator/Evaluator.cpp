#include "Evaluator.h"
#include "Token.h"

Number Evaluator::eval (Parser & parser, const ParseTreeNode & root)
{
    const Token & rootToken = root.data;
    
    if (rootToken.isNumber()) {
        return *(rootToken.getVal());
    }
    if (rootToken.isOperator()) {
        Number valLeft = eval(parser, parser.getNodeById(root.leftId));
        Number valRight = eval(parser, parser.getNodeById(root.rightId));

        Number result;
        Token::Type op = rootToken.getType();
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
