#include "../../compiler.h"
#include "config.h"

static const char   *current_file = "";
static ull          current_line = 1;
static ull          current_column = 1;

static bool         impl_is_new_line(const char *c)
{
    return str_is_prefixed(c, "\n");
}

static const char   *impl_get_current_file()
{
    return current_file; 
}

static ull          impl_get_current_line()
{
    return current_line; 
}

static ull          impl_get_current_column()
{
    return current_column; 
}

static void         impl_set_current_file(const char *path)
{
    current_file = path;
}

static void         impl_set_current_line(ull line)
{
    current_line = line;
}

static void         impl_set_current_column(ull column)
{
    current_column = column; 
}


static ast_node     *parse_line(compiler_ctx *ctx, const char *src)
{
    if (*src == '\n')
    {
        return alloc(ast_node, 
            .src = strdup("\n"),
            .symbol = "NEW_LINE",
            .data = 0
        );
    }
    return 0;
}

static char         *preprocess_line(compiler_ctx *ctx, const char **src)
{
    ast_node    *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "NEW_LINE"))
    {
        current_line += 1;
        current_column = 1;
     //   *src += 1;// TODO : detect if src changed within preprocess_all
        return 0;
    }
    return 0;
}

static ast_node     *parse_column(compiler_ctx *ctx, const char *src)
{
    if (*src == '\n')
        return 0;
    if (ctx->do_compile && !isspace(*src))
    {
        print("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, current_file, current_line, current_column);
        return 0;
    }
    current_column += *src == '\t' ? 4 : 1;
    return alloc(ast_node,
        .src = strdup((char[2]){*src, 0}),
        .symbol = "COLUMN",
        .data = 0,
    );
}


void                impl_on_parse(compiler_ctx *ctx, ast_node *n)
{

		if (ctx->is_new_line)
		{
			const char *last_space = strrchr_cb(n->src, ctx->is_new_line);
			if (last_space)
				ctx->set_current_column(last_space - n->src);
			else 
				ctx->set_current_column(ctx->get_current_column(ctx) + strlen(n->src));
		}
}

bool                on_load_ext(    
        compiler_ctx *ctx,
        int ac, 
        char** av)
{

    ctx->is_new_line = impl_is_new_line;
    ctx->on_parse = impl_on_parse;

    current_file = ctx->source_path;

    ctx->get_current_file   = impl_get_current_file;
    ctx->get_current_line   = impl_get_current_line;
    ctx->get_current_column = impl_get_current_column;
    
    ctx->set_current_column = impl_set_current_column;
    ctx->set_current_line = impl_set_current_line;
    ctx->set_current_file = impl_set_current_file;

    parser_list_add(&(ctx->parsers), parse_line);
    parser_list_add(&(ctx->parsers), parse_column);


    preprocessor_list_add(&(ctx->preprocessors), preprocess_line);

    print ("Position ext loaded!\n");
    return true;
}