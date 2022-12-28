#ifndef COMPILER_H
# define COMPILER_H
# include "lib/ft/ft.h"
# define MAX_COMPILER_DEPTH 128

typedef struct 
{
    const char          *src;
    char                *symbol;
    void                *data;
}                       ast_node;

DEF_LIST_PROTO(ast_node*,     ast_node_list)

typedef struct s_compiler_ctx compiler_ctx;

typedef ast_node        *parser                 (compiler_ctx *, const char *);
typedef char            *preprocessor           (compiler_ctx *, const char **);
typedef char            *compiler               (compiler_ctx *, ast_node *);
typedef ull             current_line_getter     ();
typedef ull             current_column_getter   ();
typedef char            *current_file_getter    ();
typedef void            current_column_setter   (ull);

DEF_LIST_PROTO(parser*,       parser_list)
DEF_LIST_PROTO(preprocessor*, preprocessor_list)
DEF_LIST_PROTO(compiler*,     compiler_list)
DEF_LIST_PROTO(void*,         ext_list)

typedef struct s_compiler_ctx {
    parser_list             *parsers;
    preprocessor_list       *preprocessors;
    compiler_list           *compilers;
    ext_list                *exts;
    char                    *source_path;
    bool                    do_compile;
    current_line_getter     *get_current_line;
    current_column_getter   *get_current_column;               
    current_file_getter     *get_current_file;       
    current_column_setter   *set_current_column;        
} compiler_ctx;

void                    compiler_init(compiler_ctx*);
void                    compiler_destroy(compiler_ctx*);
parser                  parse;
char                    *preprocess_all(compiler_ctx *, const char *);
char                    *compile_all(compiler_ctx *,ast_node_list *);
ast_node_list           *parse_all(compiler_ctx *,const char *);
typedef bool            on_load_ext_t(compiler_ctx *,int, char**);
bool                    load_ext(compiler_ctx *,int, char**, char *path);
#endif