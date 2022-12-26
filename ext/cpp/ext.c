#include "./../../compiler.h"

static char *current_file = "";
static ull  current_line = 1;
static ull  current_column = 1;

//////////

#define FILE_MACRO_TEXT "__FILE__" 

static char    *c_preprocess_cpp_file(compiler_ctx *ctx, const char **src)
{
    print("trying cpp file\n");

    if (str_is_prefixed(*src, FILE_MACRO_TEXT))
    {
        *src += strlen(FILE_MACRO_TEXT);
        return strdup(current_file);
    }
    return 0;
}

static char     *impl_get_current_file()
{
    return current_file; 
}


//////////

#define LINE_MACRO_TEXT "__LINE__" 

static ast_node    *c_parse_cpp_line(compiler_ctx *ctx, const char *src)
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

static char    *c_preprocess_cpp_line(compiler_ctx *ctx, const char **src)
{
    ast_node    *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "SPACE"))
    {
        current_line += 1;
        current_column = 0;
        return 0;
    }
    if (str_is_prefixed(*src, LINE_MACRO_TEXT))
    {
        *src += strlen(LINE_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", current_line);
        return o;
    }
    return 0;
}

static ull     impl_get_current_line()
{
    return current_column; 
}

//////////

#define COLUMN_MACRO_TEXT "__COLUMN__" 

static ast_node    *c_parse_cpp_column(compiler_ctx *ctx, const char *src)
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


static char    *c_preprocess_cpp_column(compiler_ctx *ctx, const char **src)
{
    if (str_is_prefixed(*src, COLUMN_MACRO_TEXT))
    {
        *src += strlen(COLUMN_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", current_column);
        return o;
    }
    return 0;
}

static ull     impl_get_current_column()
{
    return current_column; 
}

static void   impl_set_current_column(ull column)
{
    current_column = column; 
}

//////////

bool    on_load_ext(    
        compiler_ctx *ctx,
        int ac, 
        char** av)
{

    ctx->get_current_file = impl_get_current_file;
    ctx->set_current_column = impl_set_current_column;

    current_file = ctx->source_path; 

    parser_list_add(&(ctx->parsers), c_parse_cpp_line);
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_line);
    print ("CPP ext loaded!\n");
    return true;
}