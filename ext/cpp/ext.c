#include "./../../compiler.h"

#define FILE_MACRO_TEXT "__FILE__" 
#define LINE_MACRO_TEXT "__LINE__" 
#define COLUMN_MACRO_TEXT "__COLUMN__" 

static char    *c_preprocess_cpp_file(compiler_ctx *ctx, const char **src)
{
    if (!str_is(ctx->language, "C"))
        return 0;
    if (str_is_prefixed(*src, FILE_MACRO_TEXT))
    {
        *src += strlen(FILE_MACRO_TEXT);
        char *o;
        asprintf(&o, "\"%s\"", ctx->file);
        return o;
    }
    return 0;
}

static char    *c_preprocess_cpp_line(compiler_ctx *ctx, const char **src)
{
    if (!str_is(ctx->language, "C"))
        return 0;
    if (str_is_prefixed(*src, LINE_MACRO_TEXT))
    {   
        *src += strlen(LINE_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", ctx->line);
        return o;
    }
    return 0;
}

static char    *c_preprocess_cpp_column(compiler_ctx *ctx, const char **src)
{
    if (!str_is(ctx->language, "C"))
        return 0;
    if (str_is_prefixed(*src, COLUMN_MACRO_TEXT))
    {   
        *src += strlen(COLUMN_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", ctx->column);
        return o;
    }
    return 0;
}

/*
 *  TODO : optimisze me   
 */ 
static char     *c_preprocess_cpp_define(compiler_ctx *ctx, const char **src)
{
    if (ctx->language && !str_is(ctx->language, "C"))
        return 0;
    if (ctx->do_compile && !isspace(**src))
    {
        print ("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, ctx->file, ctx->line, ctx->column);
        return 0;
    }
    ull i = 0;
    ull startIndex = 0;
    if (ctx->column == 1)
        while (isspace((*src)[i]))
        {
            if ((*src)[i] == '\n')
                return 0;
            i += 1;
        }
    if ((*src)[i] == '#')
    {
        i += 1;

        print ("# at %s:%llu:%llu!\n", ctx->file, ctx->line, i);
        while (isspace((*src)[i]) && (*src)[i] != '\n')
            i += 1;
        if (str_is_prefixed(*src + i, "include"))
        {
            print ("include at [%llu:%llu]\n", ctx->line, i);
            *src += i + strlen("include");
            ctx->no_expand = true;
            return strdup("#include");
        }
        else if (str_is_prefixed(*src + i, "define"))
        {
            print ("define at [%llu:%llu]\n", ctx->line, i);
            *src += i + strlen("define");
            ctx->no_expand = true;
            return strdup("#define");
        }
        else if (str_is_prefixed(*src + i, "pragma"))
        {
            // TODO

        }
        else if (str_is_prefixed(*src + i, "line"))
        {
            // TODO :: add #line no fname and an option using ac av to emit line and col to the compiler
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
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_file);
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_line);
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_column);
    preprocessor_list_add(&(ctx->preprocessors), c_preprocess_cpp_define);
    print ("CPP ext loaded!\n");
    return true;
}