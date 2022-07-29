#ifndef LEXER_HPP
#define LEXER_HPP

enum class TOKEN_TYPES
{
    PLUS,
    MINUS,
    ASTERISK,
    FORWARD_SLASH,
    NUMBER_LITERAL,
    EOI,                // stands for "End Of Input"
};

typedef struct
{
    TOKEN_TYPES tokenType;
    int intValue;
} token_t;


#endif	// LEXER_HPP
