#ifndef METADATA_HPP
#define METADATA_HPP

#ifndef extern_
    #define extern_ extern
#endif

#include <stdio.h>
#include "include/Lexer/lexer.hpp"

extern_ int LineNumber;
extern_ FILE *FileStream;
extern_ token_t Token;

#endif	// METADATA_HPP
