#include "./../../compiler.h"

static ast_node    *c_open_brace          (const char *src)
{
    if (*src == '{')
        print ("braces found!");
    return 0;
}

char    *c_macro_hello(const char *src)
{

    if (parse(src))
        return;
    return;
}

bool    on_load_ext(int ac, char** av, parser_list** parsers, preprocessor_list** macros, compiler_list** compilers)
{
    parser_list_add(parsers, c_open_brace);
    print ("CPP ext loaded!\n");
    return true;
}