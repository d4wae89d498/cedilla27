#ifndef LIBFT_H
# define LIBFT_H
# include <libc.h>
# include <ctype.h>
# include <dlfcn.h>
# include "../liblist/list.h"
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
#define print(...) 														\
	(fprintf(stderr, "[%s:%i]\t", __FILE__, __LINE__)					\
+ 																		\
	fprintf(stderr, __VA_ARGS__))										
# define ull unsigned long long 
# define ll long long

DEF_LIST(char*, str_list)

extern int errno;


# include "explode.h"
# include "args.h"
# include "read_file.h"
#endif