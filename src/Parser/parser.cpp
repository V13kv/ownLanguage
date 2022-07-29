#include <stdlib.h>
#include <stdbool.h>

#include "include/Parser/parser.hpp"
#include "include/Parser/tree.hpp"
#include "include/Lexer/lexer.hpp"
#include "include/Lexer/scanner.hpp"
#include "include/metadata.hpp"
#include "include/errorHander.hpp"


static ast_node_t *parseNumber()
{
    switch (Token.tokenType)
    {
        case TOKEN_TYPES::NUMBER_LITERAL:
            {
                ast_node_t *leaf = newASTLeaf(AST_NODE_TYPES::NUMBER, Token.intValue);
                scanToken(&Token);

                return leaf;
            }
            
        case TOKEN_TYPES::ASTERISK:
        case TOKEN_TYPES::FORWARD_SLASH:
        case TOKEN_TYPES::MINUS:
        case TOKEN_TYPES::PLUS:
        case TOKEN_TYPES::EOI:
        default:
            onError("Syntax error in line %d\n", LineNumber);
    }
}

/*
ast_node_t *parseBinaryExpression()
{
    // Get number && get next token
    ast_node_t *left = parseNumber();
    if (Token.tokenType == TOKEN_TYPES::EOI)
    {
        return left;
    }

    // Convert token operation into a AST node operation
    AST_NODE_TYPES nodeOpType = cvtTokenOpToASTOp(Token.tokenType);
    
    // Get next token && get right-hand subtree
    scanToken(&Token);
    ast_node_t *right = parseBinaryExpression();

    // Build an AST tree
    ast_node_t *node = newASTNode(nodeOpType, left, right, 0);
    
    return node;
}
*/

static ast_node_t *mul_div_expr()
{
    ast_node_t *left = parseNumber();
    if (Token.tokenType == TOKEN_TYPES::EOI)
    {
        return left;
    }

    TOKEN_TYPES tokenType = Token.tokenType;
    while ((tokenType == TOKEN_TYPES::ASTERISK) || (tokenType == TOKEN_TYPES::FORWARD_SLASH))
    {
        scanToken(&Token);
        ast_node_t *right = parseNumber();

        left = newASTNode(cvtTokenOpToASTOp(tokenType), left, right, 0);
        if (Token.tokenType == TOKEN_TYPES::EOI)
        {
            break;
        }

        tokenType = Token.tokenType;
    }

    return left;
}

ast_node_t *add_sub_expr()
{
    ast_node_t *left = mul_div_expr();
    if (Token.tokenType == TOKEN_TYPES::EOI)
    {
        return left;
    }

    TOKEN_TYPES tokenType = Token.tokenType;
    while (true)
    {
        scanToken(&Token);

        ast_node_t *right = mul_div_expr();

        left = newASTNode(cvtTokenOpToASTOp(tokenType), left, right, 0);
        if (Token.tokenType == TOKEN_TYPES::EOI)
        {
            break;
        }

        tokenType = Token.tokenType;
    }

    return left;
}

ast_node_t *rdp()
{
    return add_sub_expr();
}



static int OpPrec[] = {
    10, // +
    10, // -
    20, // *
    20, // /
    0,  // NumberLiteral
    0,  // EOI
};

static int opPrecedence(TOKEN_TYPES tokenType)
{
    int prec = OpPrec[(int) tokenType];
    if (prec == 0)
    {
        onError("Syntax error in line %d, token type %d, function %s()", LineNumber, tokenType, __func__);
    }

    return prec;
}

ast_node_t *prattParsing(int prevTokenPrec)
{
    ast_node_t *left = parseNumber();
    TOKEN_TYPES tokenType = Token.tokenType;
    if (tokenType == TOKEN_TYPES::EOI)
    {
        return left;
    }

    while (opPrecedence(tokenType) > prevTokenPrec)
    {
        scanToken(&Token);

        ast_node_t *right = prattParsing(OpPrec[(int) tokenType]);
        left = newASTNode(cvtTokenOpToASTOp(tokenType), left, right, 0);

        tokenType = Token.tokenType;
        if (tokenType == TOKEN_TYPES::EOI)
        {
            return left;
        }
    }

    return left;
}
