#include "../compiler.h"
#include "assert.h"

ast_node    *parse_sep(const char *src)
{
    if (str_is(src, " "))
        return alloc(ast_node, .symbol="SPACE", .src=" ");
    return 0;
}

char    *compile_sep(ast_node *node)
{
    if (str_is(node->symbol, "SPACE"))
        return " ";
    return 0;
}


int main()
{
    parser_list_add(&parsers, parse_sep);
    compiler_list_add(&compilers, compile_sep);

    char    *s = compile(parse_all(" "));
    assert(*s == ' ');
}