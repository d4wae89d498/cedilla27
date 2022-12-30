#ifndef COMPILER_H
# define COMPILER_H
# include "config.h"
# include "lib/ft/ft.h"
# define DEFAULT_FILE_NAME "(unknow_file)"

typedef struct s_compiler_ctx compiler_ctx;
typedef struct 
{
    const char          *src;
    char                *symbol;
    compiler_ctx        *ctx;
    void                *data;
}                       ast_node;
typedef ast_node        *parser                 (compiler_ctx *, const char *);
typedef char            *preprocessor           (compiler_ctx *, const char **);
typedef char            *compiler               (compiler_ctx *, ast_node *);

DEF_LIST_PROTO(ast_node*,     ast_node_list)
DEF_LIST_PROTO(parser*,       parser_list)
DEF_LIST_PROTO(preprocessor*, preprocessor_list)
DEF_LIST_PROTO(compiler*,     compiler_list)
DEF_LIST_PROTO(void*,         ext_list)

typedef struct s_compiler_ctx {
    
    bool                            do_compile;
    ext_list                        *exts;
    parser_list                     *parsers;
    preprocessor_list               *preprocessors;
    compiler_list                   *compilers;
    void                            (*parse_node_position)(compiler_ctx *, ast_node *n);
    bool                            (*is_new_line)(const char *); 
    const char                      *file; 
    ull                             line;
    ull                             column;
    const char                      *language;     
    float                           language_version;     
    ull                             preprocessor_depth;
    ull                             compiler_depth;
    bool                            no_expand;
} compiler_ctx;

void                    compiler_init(compiler_ctx*);
compiler_ctx            *clone_ctx(compiler_ctx *ctx);
void                    compiler_destroy(compiler_ctx*);
parser                  parse;
char                    *preprocess_all(compiler_ctx *, const char *);
char                    *compile_all(compiler_ctx *,ast_node_list *);
ast_node_list           *parse_all(compiler_ctx *,const char *);
typedef bool            on_load_ext_t(compiler_ctx *,int, char**);
bool                    load_ext(compiler_ctx *,int, char**, char *path);
#endif