#include "../../compiler.h"

static char *current_file = "";
static ull  current_line = 1;
static ull  current_column = 1;

static char     *impl_get_current_file()
{
    return current_file; 
}

static ull  impl_get_current_line()
{
    return current_line; 
}

static ull     impl_get_current_column()
{
    return current_column; 
}

static void   impl_set_current_column(ull column)
{
    current_column = column; 
}

static ast_node    *parse_line(compiler_ctx *ctx, const char *src)
{
    if (*src == '\n')
    {
        return alloc(ast_node, 
            .src = strdup("\n"),
            .symbol = "SPACE",
            .data = 0
        );
    }
    return 0;
}

static char    *preprocess_line(compiler_ctx *ctx, const char **src)
{
    ast_node    *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "SPACE"))
    {
        current_line += 1;
        current_column = 1;
        return 0;
    }
    return 0;
}

static ast_node    *parse_column(compiler_ctx *ctx, const char *src)
{
    if (ctx->do_compile && !isspace(*src))
    {
        print("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, current_file, current_line, current_column);
        return 0;
    }
    current_column += 1;
    return alloc(ast_node,
        .src = strdup((char[2]){*src, 0}),
        .symbol = "COLUMN",
        .data = 0,
    );
}

bool    on_load_ext(    
        compiler_ctx *ctx,
        int ac, 
        char** av)
{
    current_file = ctx->source_path;

    ctx->get_current_file   = impl_get_current_file;
    ctx->get_current_line   = impl_get_current_line;
    ctx->get_current_column = impl_get_current_column;
    
    ctx->set_current_column = impl_set_current_column;
    
    parser_list_add(&(ctx->parsers), parse_line);
    parser_list_add(&(ctx->parsers), parse_column);


    preprocessor_list_add(&(ctx->preprocessors), preprocess_line);

    print ("Position ext loaded!\n");
    return true;
}