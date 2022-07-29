#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "include/Lexer/scanner.hpp"
#include "include/metadata.hpp"
#include "include/errorHander.hpp"


/**
 * @brief Get the next character from the file stream
 * 
 * @param fs 
 * @return char 
 */
static int getNextChar()
{
    int chr = fgetc(FileStream);
    if (chr == '\n')
    {
        ++LineNumber;
    }

    return chr;
}

/**
 * @brief Function skips all control characters and return the first character that is not the control character
 * 
 * @param fs 
 * @return char 
 */
static int skip()
{
    int chr = getNextChar();
    while (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\f' || chr == '\r')
    {
        chr = getNextChar();
    }

    return chr;
}

static int scanint(int chr)
{
    int result = 0;
    while (strchr("0123456789", chr) != NULL)
    {
        result = result * 10 + (chr - '0');
        
        chr = getNextChar();
    }

    ungetc(chr, FileStream);
    
    return result;
}

int scanToken(token_t *token)
{
    int chr = skip();
    switch (chr)
    {
        case EOF:
            token->tokenType = TOKEN_TYPES::EOI;
            return 0;
        case '+':
            token->tokenType = TOKEN_TYPES::PLUS;
            break;
        case '-':
            token->tokenType = TOKEN_TYPES::MINUS;
            break;
        case '*':
            token->tokenType = TOKEN_TYPES::ASTERISK;
            break;
        case '/':
            token->tokenType = TOKEN_TYPES::FORWARD_SLASH;
            break;
        default:
            if (isdigit(chr))
            {
                token->tokenType = TOKEN_TYPES::NUMBER_LITERAL;
                token->intValue = scanint(chr);
            }
            else
            {
                onError("Unrecognised character `%c` in %d line\n", chr, LineNumber);
            }

            break;
    }

    return 1;
}
