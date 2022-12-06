#ifndef COMPILER_API_H
# include "libc.h"
# include "ctype.h"
# include "dlfcn.h"
# include "liblist/list.h"
# define alloc(TYPE, ...) ({					\
	TYPE *o = malloc(sizeof(TYPE));				\
    if (o)                                      \
    {                                           \
	    *o = (TYPE) {__VA_ARGS__};				\
	    o;										\
    }                                           \
    printf("error, allocation error at %s:%i\n", __FILE__, __LINE__); \
    exit(1);                                    \
    o;                                          \
})
# define ull unsigned long long 
# define ll long long

extern int errno;

typedef struct 
{
    ull     line;
    ull     col;
    void    *extension;
}   compiler_ctx;

typedef struct 
{
    char    *symbol;
    void    *data;
}   ast_node;

DEF_LIST(ast_node*, node_list)

typedef ast_node    *parser             (const char *src);
typedef char        *macro              (const char *src, compiler_ctx *ctx);
typedef char        *compiler           (ast_node *tree);

DEF_LIST(parser*,   parser_list)
DEF_LIST(macro*,    macro_list)
DEF_LIST(compiler*, compiler_list)

parser_list parsers;
macro_list  macros;
compiler_list
            compilers;

bool        is_flag(char *str, char *prefix);
bool        is_var(char *str, char *prefix, char **value);
char	    *read_file(char *path);

parser      parse;
macro       apply_macros;
compiler    compile;

typedef void
            on_load_ext_t(int, char**, parser_list*, macro_list*, compiler_list*);
void        load_ext(int, char**, char *path);

#endif