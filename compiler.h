#ifndef COMPILER_H
# define COMPILER_H
# include "config.h"
# include "lib/ft/ft.h"
# define DEFAULT_FILE_NAME "(unknow_file)"

typedef struct {
    char    *key;
    void    *data;
    void    (*destroy)(void *data);
} object;

DEF_LIST_PROTO(object,        object_list)

typedef struct s_compiler_ctx compiler_ctx;
typedef struct 
{
    char                *src;
    const char          *symbol;
    object_list         *data;
}                       ast_node;

typedef ast_node        *parser                 (const compiler_ctx *, const char *);
typedef char            *preprocessor           (compiler_ctx *, const char **);
typedef char            *compiler               (compiler_ctx *, const ast_node *);

typedef struct s_ext
{
    char    *name;
    void    *handle;
    float   version;
} ext;

DEF_LIST_PROTO(ast_node*,     ast_node_list)
DEF_LIST_PROTO(parser*,       parser_list)
DEF_LIST_PROTO(preprocessor*, preprocessor_list)
DEF_LIST_PROTO(compiler*,     compiler_list)
DEF_LIST_PROTO(ext,           ext_list)

typedef struct s_compiler_ctx {
    
    bool                            do_compile;
    ext_list                        *exts;
    parser_list                     *parsers;
    preprocessor_list               *preprocessors;
    compiler_list                   *compilers;
    bool                            no_expand;
    ull                             preprocessor_depth;
    ull                             compiler_depth;
    const char                      *file; 
    
    void                            (*on_add_ast_node)(compiler_ctx *, ast_node *n);

    object_list                     *data; 

// shall be object bellow :

    ull                             line;
    ull                             column;
    const char                      *language; 
    float                           language_version;     
    
} compiler_ctx;

void                    compiler_init(compiler_ctx*);
void                    compiler_destroy(compiler_ctx*);
parser                  parse;
char                    *preprocess_all(compiler_ctx *, const char *);
char                    *compile_all(compiler_ctx *,ast_node_list *);
ast_node_list           *parse_all(compiler_ctx *,const char *);
typedef ext             on_load_ext_t(compiler_ctx *,int, char**);
bool                    load_ext(compiler_ctx *,int, char**, char *path);

void ext_close(ext e);

void object_free(object o);

void ast_node_free(ast_node *o);
#endif