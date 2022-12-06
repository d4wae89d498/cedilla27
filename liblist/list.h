#ifndef LIST_H
# define LIST_H
# include <stdlib.h>
# define DEF_LIST(TYPE, NAME) 			\
	typedef struct s_ ## NAME			\
	{									\
		TYPE				data;		\
		struct s_ ## NAME	*next;		\
	}  NAME;							\
										\
										\
NAME    *NAME ## _last(NAME *l)			\
{										\
    while (l)							\
    {									\
        if (!l->next)					\
            return l;					\
        l = l->next;					\
    }									\
    return 0;							\
}										\
										\
NAME    *NAME ## _new(TYPE data)		\
{										\
    NAME *o;							\
										\
    o = malloc(sizeof(NAME));			\
    o->data = data;						\
    o->next = 0;						\
    return o;							\
}										\
										\
NAME    *NAME ## _add(NAME **l, TYPE data)\
{										\
    NAME *last;							\
										\
    last = NAME ## _last(*l);			\
    if (!last)							\
        return *l = NAME ## _new(data);	\
    return last->next = NAME ## _new(data);\
}\
										\
void   NAME ## _del(NAME **l, NAME *k, void(*value_destructor)(TYPE))\
{										\
    NAME    *it;						\
    NAME    *swp;						\
    NAME    **prev;						\
										\
    it = *l;							\
    prev = l;							\
    while (it)							\
    {									\
        swp = it->next;					\
        if (it == k)					\
        {								\
            if (value_destructor)		\
                value_destructor(it->data);\
            free(it);					\
            *prev = swp;				\
        }								\
        it = swp;						\
        if (it)							\
            prev = &(it->next);			\
    }									\
}										\
										\
void    NAME ## _free(NAME *l, void(*value_destructor)(TYPE))\
{										\
    NAME    *it;						\
    NAME    *swp;						\
										\
    it = l;								\
    while (it)							\
    {									\
        swp = it->next;					\
        if (value_destructor)			\
            value_destructor(it->data);	\
        free(it);						\
        it = swp;						\
    }									\
}										\

#endif
