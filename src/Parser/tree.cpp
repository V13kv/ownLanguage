#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/errorHander.hpp"
#include "include/metadata.hpp"

#include "include/Lexer/lexer.hpp"
#include "include/Lexer/scanner.hpp"

#include "include/Parser/tree.hpp"


ast_node_t *newASTNode(AST_NODE_TYPES nodeOpType, ast_node_t *left, ast_node_t *right, int numberValue)
{
    // Allocate memory for new node
    ast_node_t *node = (ast_node_t *) calloc(1, sizeof(ast_node_t));
    assert(node != NULL);

    // Init fields
    node->nodeOpType      = nodeOpType;
    node->left          = left;
    node->right         = right;
    node->numberValue   = numberValue;

    return node;
}

ast_node_t *newASTLeaf(AST_NODE_TYPES nodeOpType, int numberValue)
{
    return newASTNode(nodeOpType, NULL, NULL, numberValue);
}

ast_node_t *newSingleSuccessorNode(AST_NODE_TYPES nodeOpType, ast_node_t *left, int numberValue)
{
    return newASTNode(nodeOpType, left, NULL, numberValue);
}

AST_NODE_TYPES cvtTokenOpToASTOp(TOKEN_TYPES tokenType)
{
    switch (tokenType)
    {
        case TOKEN_TYPES::PLUS:
            return AST_NODE_TYPES::ADD;
        case TOKEN_TYPES::MINUS:
            return AST_NODE_TYPES::SUBTRACT;
        case TOKEN_TYPES::ASTERISK:
            return AST_NODE_TYPES::MULTIPLY;
        case TOKEN_TYPES::FORWARD_SLASH:
            return AST_NODE_TYPES::DIVIDE;

        case TOKEN_TYPES::NUMBER_LITERAL:
        default:
            onError("Unknown tokenType `%d` in %s() in line %d\n", (int) tokenType, __func__, LineNumber);
    }
}

int evaluateAST(ast_node_t *node)
{
    int leftSubtreeValue  = 0;
    int rightSubtreeValue = 0;

    if (node->left != NULL)
    {
        leftSubtreeValue = evaluateAST(node->left);
    }

    if (node->right != NULL)
    {
        rightSubtreeValue = evaluateAST(node->right);
    }

    switch (node->nodeOpType)
    {
        case AST_NODE_TYPES::ADD:
            return leftSubtreeValue + rightSubtreeValue;
        case AST_NODE_TYPES::SUBTRACT:
            return leftSubtreeValue - rightSubtreeValue;
        case AST_NODE_TYPES::MULTIPLY:
            return leftSubtreeValue * rightSubtreeValue;
        case AST_NODE_TYPES::DIVIDE:
            return leftSubtreeValue / rightSubtreeValue;
        case AST_NODE_TYPES::NUMBER:
            return node->numberValue;
        default:
            onError("Unknown AST node operation type: `%d`\n", node->nodeOpType);
    }
}
