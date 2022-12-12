#ifndef COMPILER_H
# define COMPILER_H
# include "lib/ft/ft.h"

typedef struct 
{
    const char          *src;
    char                *symbol;
    void                *data;
}                       ast_node;

DEF_LIST_PROTO(ast_node*,     ast_node_list)

typedef ast_node        *parser             (const char *);
typedef char            *preprocessor       (const char *);
typedef char            *compiler           (ast_node_list *);

DEF_LIST_PROTO(parser*,       parser_list)
DEF_LIST_PROTO(preprocessor*, preprocessor_list)
DEF_LIST_PROTO(compiler*,     compiler_list)

parser_list             *parsers;
preprocessor_list       *preprocessors;
compiler_list           *compilers;

parser                  parse;
preprocessor            preprocess;
compiler                compile;

ast_node_list           *parse_all(const char *);

typedef bool            on_load_ext_t(int, char**, parser_list**, preprocessor_list**, compiler_list**);
bool                    load_ext(int, char**, char *path);

#endif