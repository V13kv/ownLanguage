#ifndef TREE_HPP
#define TREE_HPP

#include "include/Lexer/lexer.hpp"

enum class AST_NODE_TYPES
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NUMBER,
};

typedef struct ast_node_t
{
    AST_NODE_TYPES nodeOpType;
    ast_node_t *left;
    ast_node_t *right;

    int numberValue;
} ast_node_t;


ast_node_t *newASTNode(AST_NODE_TYPES nodeOpType, ast_node_t *left, ast_node_t *right, int numberValue);
ast_node_t *newASTLeaf(AST_NODE_TYPES nodeOpType, int numberValue);
ast_node_t *newSingleSuccessorNode(AST_NODE_TYPES nodeOpType, ast_node_t *left, int numberValue);

AST_NODE_TYPES cvtTokenOpToASTOp(TOKEN_TYPES tokenType);

int evaluateAST(ast_node_t *rootNode);

#endif	// TREE_HPP
