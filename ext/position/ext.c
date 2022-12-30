#include "../../compiler.h"
#include "config.h"

static ast_node     *parse_line(compiler_ctx *ctx, const char *src)
{
    if (ctx->is_new_line(src))
    {
        return alloc(ast_node, 
            .src = strdup(NEW_LINE),
            .symbol = "NEW_LINE",
            .ctx = clone_ctx(ctx)
        );
    }
    return 0;
}

static char         *preprocess_line(compiler_ctx *ctx, const char **src)
{
    ast_node    *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "NEW_LINE"))
    {
        ctx->line += 1;
        ctx->column = 1;
     //   *src += 1;// TODO : detect if src changed within preprocess_all
        return 0;
    }
    return 0;
}

static ast_node     *parse_column(compiler_ctx *ctx, const char *src)
{
    if (ctx->is_new_line(src))
        return 0;
    if (ctx->do_compile && !IS_SPACE(src))
    {
        print("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, ctx->file, ctx->line, ctx->column);
        return 0;
    }
    ctx->column += *src == IS_TAB(src) ? TAB_LENGTH : 1;
    return alloc(ast_node,
        .src = strdup((char[2]){*src, 0}),
        .symbol = "COLUMN",
        .ctx = clone_ctx(ctx)
    );
}


void                impl_parse_node_position(compiler_ctx *ctx, ast_node *n)
{

		if (ctx->is_new_line)
		{
			const char *last_space = strrchr_cb(n->src, ctx->is_new_line);
			if (last_space)
				ctx->column = last_space - n->src;
			else 
				ctx->column = ctx->column + strlen(n->src);
		}
}

bool                impl_is_new_line(const char *src)
{
    return str_is_prefixed(src, NEW_LINE);
}

bool                on_load_ext(    
        compiler_ctx *ctx,
        int ac, 
        char** av)
{

    ctx->is_new_line = impl_is_new_line;
    ctx->parse_node_position = impl_parse_node_position;
    
    parser_list_add(&(ctx->parsers), parse_line);
    parser_list_add(&(ctx->parsers), parse_column);

    preprocessor_list_add(&(ctx->preprocessors), preprocess_line);

    print ("Position ext loaded!\n");
    return true;
}

void            on_unload_ext(compiler_ctx *ctx)
{
    return;
}