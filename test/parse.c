#include "../compiler.h"
#include "assert.h"

ast_node    *parse_42(compiler_ctx *ctx, const char *src)
{
    if (!strncmp(src, "42", 2))
    {
        return alloc(ast_node, 
            .src="42", 
            .symbol="43", 
            .ctx=clone_ctx(ctx)
        );
    }
    return 0;
}

ast_node    *parse_ab(compiler_ctx *ctx, const char *src)
{
    if (!strncmp(src, "ab", 2))
    {
        return alloc(ast_node, 
            .src="ab", 
            .symbol="AB", 
            .ctx=clone_ctx(ctx)
        );
    }
    return 0;
}

int main(void)
{
    compiler_ctx ctx;
    compiler_init(&ctx);

    parser_list_add(&(ctx.parsers), parse_42);
    ast_node *test = parse(&ctx, "0");
    assert(test == 0);

    test = parse(&ctx, "42");
    assert(test);
    assert(!strcmp(test->symbol, "43"));
    assert(!strcmp(test->src, "42"));

    test = parse(&ctx, "042");
    assert(test == 0);

    parser_list_add(&(ctx.parsers), parse_ab);
    test = parse(&ctx, "ab");
    assert(test);
    assert(!strcmp(test->src, "ab"));
    assert(!strcmp(test->symbol, "AB"));

    return 0;
}