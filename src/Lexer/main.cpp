#include <stdio.h>

#include "include/Lexer/lexer.hpp"
#include "include/Lexer/scan.hpp"

#define extern_
#include "include/metadata.hpp"

static const char *tokenTypeToStr(TOKEN_TYPES type)
{
    switch (type)
    {
        case TOKEN_TYPES::PLUS:
            return "+";
        case TOKEN_TYPES::MINUS:
            return "-";
        case TOKEN_TYPES::ASTERISK:
            return "*";
        case TOKEN_TYPES::FORWARD_SLASH:
            return "/";
        case TOKEN_TYPES::NUMBER_LITERAL:
            return "NUMBER_LITERAL";
        default:
            return "Unknown";
    }
}

static void scanFile(FILE *fs)
{
    token_t token;
    while (scanToken(fs, &token))
    {
        printf("Token: %s", tokenTypeToStr(token.tokenType));
        if (token.tokenType == TOKEN_TYPES::NUMBER_LITERAL)
        {
            printf(", value: %d", token.intValue);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv)
{
    FILE *fs = fopen(argv[1], "r");
    scanFile(fs);

    fclose(fs);

    return 0;
}
