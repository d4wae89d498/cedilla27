#include "../compiler.h"
#include "assert.h"

ast_node    *parse_sep(compiler_ctx *ctx, const char *src)
{
    if (str_is(src, " "))
        return alloc(ast_node, .symbol="SPACE", .src=" ");
    return 0;
}

char    *compile_sep(compiler_ctx *ctx, ast_node *node)
{
    if (str_is(node->symbol, "SPACE"))
        return " ";
    return 0;
}


int main()
{
    compiler_ctx ctx;
    compiler_init (&ctx);

    parser_list_add(&(ctx.parsers), parse_sep);
    compiler_list_add(&(ctx.compilers), compile_sep);

    char    *s = compile_all(&ctx, parse_all(&ctx, " "));
    assert(*s == ' ');
    printf ("OK\n");
}