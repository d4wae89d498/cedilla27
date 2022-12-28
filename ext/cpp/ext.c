#include "./../../compiler.h"

#define FILE_MACRO_TEXT "__FILE__" 
#define LINE_MACRO_TEXT "__LINE__" 
#define COLUMN_MACRO_TEXT "__COLUMN__" 

static char    *c_preprocess_cpp_file(compiler_ctx *ctx, const char **src)
{
    if (ctx->get_current_language && !str_is(ctx->get_current_language(), "C"))
        return 0;
    if (str_is_prefixed(*src, FILE_MACRO_TEXT))
    {
        *src += strlen(FILE_MACRO_TEXT);
        char *o;
        asprintf(&o, "\"%s\"", ctx->get_current_file());
        return o;
    }
    return 0;
}

static char    *c_preprocess_cpp_line(compiler_ctx *ctx, const char **src)
{
    if (ctx->get_current_language && !str_is(ctx->get_current_language(), "C"))
        return 0;
    if (str_is_prefixed(*src, LINE_MACRO_TEXT))
    {   
        *src += strlen(LINE_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", ctx->get_current_line());
        return o;
    }
    return 0;
}

static char    *c_preprocess_cpp_column(compiler_ctx *ctx, const char **src)
{
    if (ctx->get_current_language && !str_is(ctx->get_current_language(), "C"))
        return 0;
    if (str_is_prefixed(*src, COLUMN_MACRO_TEXT))
    {   
        *src += strlen(COLUMN_MACRO_TEXT);
        char *o;
        asprintf(&o, "%llu", ctx->get_current_column());
        return o;
    }
    return 0;
}

/*
 *  TODO : optimisze me   
 */ 
static char     *c_preprocess_cpp_define(compiler_ctx *ctx, const char **src)
{
    if (ctx->get_current_language && !str_is(ctx->get_current_language(), "C"))
        return 0;
    if (ctx->do_compile && !isspace(**src))
    {
        print ("Error : unpexpected token : [%.5s]... in %s:%llu:%llu", (char*) src, ctx->get_current_file(), ctx->get_current_line(), ctx->get_current_column());
        return 0;
    }
    ull i = 0;
    ull startIndex = 0;
    if (ctx->get_current_column() == 1)
        while (isspace((*src)[i]))
        {
            if ((*src)[i] == '\n')
                return 0;
            i += 1;
        }
    if ((*src)[i] == '#')
    {
        i += 1;

        print ("# at %s:%llu:%llu!\n", ctx->get_current_file(), ctx->get_current_line(), i);
        while (isspace((*src)[i]) && (*src)[i] != '\n')
            i += 1;
        if (str_is_prefixed(*src + i, "include"))
        {
            print ("include at [%llu:%llu]\n", ctx->get_current_line(), i);
        }
        else if (str_is_prefixed(*src + i, "define"))
        {
            print ("define at [%llu:%llu]\n", ctx->get_current_line(), i);
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