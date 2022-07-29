#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "include/Lexer/scan.hpp"
#include "include/metadata.hpp"
#include "include/errorHander.hpp"


/**
 * @brief Get the next character from the file stream
 * 
 * @param fs 
 * @return char 
 */
static char getNextChar(FILE *fs)
{
    char chr = fgetc(fs);
    if (chr == '\n')
    {
        ++lineNumber;
    }

    return chr;
}

/**
 * @brief Function skips all control characters and return the first character that is not the control character
 * 
 * @param fs 
 * @return char 
 */
static char skip(FILE *fs)
{
    char chr = getNextChar(fs);
    while (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\f' || chr == '\r')
    {
        chr = getNextChar(fs);
    }

    return chr;
}

static int scanint(FILE *fs, char chr)
{
    int result = 0;
    while (strchr("0123456789", chr) != NULL)
    {
        result = result * 10 + (chr - '0');
        
        chr = getNextChar(fs);
    }

    ungetc(chr, fs);
    
    return result;
}

int scanToken(FILE *fs, token_t *token)
{
    char chr = skip(fs);
    switch (chr)
    {
        case EOF:
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
                token->intValue = scanint(fs, chr);
            }
            else
            {
                onError("Unrecognised character `%c` in %d line\n", chr, lineNumber);
            }

            break;
    }

    return 1;
}
