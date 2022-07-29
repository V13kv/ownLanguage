// TODO: #1 Done some file structural improvements @V13kv
// TODO: #3 #2 Add explanations on RDP and Pratt parsing algorithms @V13kv

#include <stdio.h>

#define extern_
#include "include/metadata.hpp"

#include "include/Lexer/scanner.hpp"
#include "include/Parser/tree.hpp"
#include "include/Parser/parser.hpp"


int main(int argc, char **argv)
{
    FileStream = fopen(argv[1], "r");

    scanToken(&Token);
    ast_node_t *node1 = rdp();
    printf("rdp:\t%d\n", evaluateAST(node1));
    
    // ast_node_t *node = parseBinaryExpression();
    // printf("%d\n", rearrangeAST(node));

    fclose(FileStream);

    FileStream = fopen(argv[1], "r");
    scanToken(&Token);
    ast_node_t *node2 = prattParsing(0);
    printf("pratt:\t%d\n", evaluateAST(node2));
    
    fclose(FileStream);

    return 0;
}
