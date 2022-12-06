#include "./../../compiler.h"

static ast_node    *c_open_brace          (const char *src)
{
    if (*src == '{')
        print ("braces found!");
    return 0;
}

void    on_load_ext(int ac, char** av, parser_list** parsers, macro_list** macros, compiler_list** compilers)
{
    parser_list_add(parsers, c_open_brace);
    print ("CPP ext loaded!\n");
}