#include "../../compiler.h"
#include "config.h"

static ast_node *parse_line(const compiler_ctx *ctx, const char *src)
{
    if (IS_NEW_LINE(src))
    {
        return alloc(ast_node,
        
            .src = strdup(NEW_LINE),
            .symbol = "NEW_LINE",
            .data = 0
        );
    }
    return 0;
}

static char *preprocess_line(compiler_ctx *ctx, const char **src)
{
    ast_node *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "NEW_LINE"))
    {
        ctx->line += 1;
        ctx->column = 1;

        return 0;
    }
    return 0;
}

static char *preprocess_char(compiler_ctx *ctx, const char **src)
{
    if (ctx->do_compile)
    {
        print("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char *)src, ctx->file, ctx->line, ctx->column);
        return 0;
    }
    ctx->column += IS_TAB(*src) ? TAB_LENGTH : 1;
    return 0;
}

void impl_on_add_ast_node(compiler_ctx *ctx, ast_node *n)
{
    ull i = 0;
    ull lines = 0;
    const char *last_space;

    last_space = 0;
    if (!n || !n->src)
    {
        print ("Warning : invalid ast_node\n");
        return ;
    }
    while (n->src[i])
    {
        if (IS_NEW_LINE(n->src + i))
            lines += 1;
        if (IS_SPACE(n->src + i))
            last_space = n->src + i;
        i += 1;
    }
    if (last_space)
        ctx->column = last_space - n->src;
    else
        ctx->column = ctx->column + strlen(n->src);
}

bool impl_is_new_line(const char *src)
{
    return str_is_prefixed(src, NEW_LINE);
}

ext on_load_ext(
    compiler_ctx *ctx,
    int ac,
    char **av)
{
    ctx->on_add_ast_node = impl_on_add_ast_node;

    parser_list_add(&(ctx->parsers), parse_line);

    preprocessor_list_add(&(ctx->preprocessors), preprocess_line);
    preprocessor_list_add(&(ctx->preprocessors), preprocess_char);

    print("Position ext loaded!\n");
    return (ext){.name = "std-position", .version = 0.1};
}

void on_unload_ext(compiler_ctx *ctx)
{
    return;
}