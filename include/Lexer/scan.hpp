#ifndef SCAN_HPP
#define SCAN_HPP

#include <stdio.h>

#include "include/Lexer/lexer.hpp"

int scanToken(FILE *fs, token_t *token);

#endif	// SCAN_HPP
