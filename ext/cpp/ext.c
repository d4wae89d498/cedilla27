#include "./../../compiler.h"

static char *current_file = "";
static ull  current_line = 1;
static ull  current_column = 1;

//////////

#define FILE_MACRO_TEXT "__FILE__" 

static char    *c_preprocess_cpp_file(compiler_ctx *ctx, const char **src)
{
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
        current_column = 1;
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
    return current_line; 
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
    ast_node    *n = parse(ctx, *src);
    if (n && str_is(n->symbol, "COLUMN"))
    {
        current_column += 1;
        return 0;
    }
    else if (str_is_prefixed(*src, COLUMN_MACRO_TEXT))
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


/*
 *  TODO : optimisze me   
 */ 
static char     *c_preprocess_cpp_define(compiler_ctx *ctx, const char **src)
{
    if (ctx->do_compile && !isspace(**src))
    {
        print("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, current_file, current_line, current_column);
        return 0;
    }
    ull i = 0;
    ull startIndex = 0;
    if (current_column == 1)
        while (isspace((*src)[i]))
        {
            if ((*src)[i] == '\n')
                return 0;
            i += 1;
        }
    if ((*src)[i] == '#')
    {
        i += 1;

        print ("# at %s:%llu:%llu!\n", current_file, current_line, i);
        while (isspace((*src)[i]) && (*src)[i] != '\n')
            i += 1;
        if (str_is_prefixed(*src + i, "include"))
        {
            print ("include at [%llu:%llu]\n", current_line, i);
        }
        else if (str_is_prefixed(*src + i, "define"))
        {
            print ("idefine at [%llu:%llu]\n", current_line, i);
        }
        else 
        {
            print ("ERROR : unknow preprocessor verb : %.5s\n", *src + i);
            exit (1);
        }
    }

    return 0;
}


bool    on_load_ext(    
        compiler_ctx *ctx,
        int ac, 
        char** av)
{
    current_file = ctx->source_path;
    ctx->get_current_file = impl_get_current_file;
    ctx->get_current_line = impl_get_current_line;
    ctx->get_current_column = impl_get_current_column;
    
    ctx->set_current_column = impl_set_current_column;
    
    parser_list_add(&(ctx->parsers), c_parse_cpp_line);
    parser_list_add(&(ctx->parsers), c_parse_cpp_column);

    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_line);
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_define);

    print ("CPP ext loaded!\n");
    return true;
}