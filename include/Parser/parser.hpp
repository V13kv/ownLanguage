#ifndef PARSER_HPP
#define PARSER_HPP

#include "include/Parser/tree.hpp"

// ast_node_t *parseBinaryExpression();
ast_node_t *rdp();
ast_node_t *prattParsing(int prevTokenPrec);

#endif	// PARSER_HPP
