#ifndef LIBFT_H
# define LIBFT_H
# include <libc.h>
# include <ctype.h>
# include <dlfcn.h>
# include "../list/list.h"
# define alloc(TYPE, ...) ({					\
	TYPE *o = malloc(sizeof(TYPE));				\
    if (!o)                                     \
    {                                           \
        printf("error, allocation error at %s:%i\n", __FILE__, __LINE__);\
        exit(1);                                \
        o;                                      \
    }                                           \
	*o = (TYPE) {__VA_ARGS__};				    \
	o;										    \
})                          
#define print(...) 								\
	(fprintf(stderr, "[%s:%i]\t", __FILE__, __LINE__)\
+ 												\
	fprintf(stderr, __VA_ARGS__))										
# define ull unsigned long long 
# define ll long long
# define strisp(STR, p) (!strncmp(str, p, strlen(str) ? strlen(str) : 0));
DEF_LIST_PROTO(char*, str_list)

extern int errno;
int     str_is(const char *str, const char *str2);
int     str_is_prefixed(const char *str, const char *prefix);
char	*read_file(char *path);
void    explode(const char *src, int (*is_sep)(const char *), str_list **output);
bool    is_var(char *str, char *prefix, char **compiler);
bool    is_flag(char *str, char *prefix);
int     skip_space(const char *s);
#endif