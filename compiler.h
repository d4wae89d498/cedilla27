#ifndef COMPILER_H
# define COMPILER_H
# include "config.h"
# include "lib/ft/ft.h"

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

typedef const char      *current_file_getter            ();
typedef ull             current_line_getter             ();
typedef ull             current_column_getter           ();
typedef const char      *current_language_getter        ();
typedef float           current_language_version_getter ();

typedef void            current_file_setter             (const char *);
typedef void            current_line_setter             (ull);
typedef void            current_column_setter           (ull);
typedef void            current_language_setter         (const char *);
typedef void            current_language_version_setter (float);

typedef bool            is_new_line                     (const char *src);

DEF_LIST_PROTO(parser*,       parser_list)
DEF_LIST_PROTO(preprocessor*, preprocessor_list)
DEF_LIST_PROTO(compiler*,     compiler_list)
DEF_LIST_PROTO(void*,         ext_list)

typedef struct s_compiler_ctx {
    parser_list                     *parsers;
    preprocessor_list               *preprocessors;
    compiler_list                   *compilers;
    ext_list                        *exts;
    char                            *source_path;
    bool                            do_compile;

    is_new_line                     *is_new_line; 

    current_file_getter             *get_current_file; 
    current_line_getter             *get_current_line;
    current_column_getter           *get_current_column;               
    current_language_getter         *get_current_language;     
    current_language_version_getter *get_current_language_version;     

    current_file_setter             *set_current_file;       
    current_line_setter             *set_current_line;       
    current_column_setter           *set_current_column;
    current_language_setter         *set_current_language;
    current_language_version_setter *set_current_language_version;
    
    void                            (*on_parse)(compiler_ctx *ctx, ast_node *n);
    
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