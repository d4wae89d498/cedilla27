#include "list.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

DEF_LIST(void*, list)
DEF_LIST(int, int_list)

int main()
{
    list    *l;

    const char 
        *s1 = "13", 
        *s2 = "14"
    ;

	int_list *il = 0;


	int_list_add(&il, 8);

	assert((il->data) == 8);

    l = 0;
    list_add(&l, (void*) s1);
    list_add(&l, (void*)s2);

    assert(l->data == s1);
    assert(l->next->data == s2);
    assert(l->next->next == 0);
    list    *i;
    (void)  i;
/*
    list    *i;
    i = l;
    while (i)
    {
        printf("v: %s\n", i->data);
        i = i->next;
    }*/

    list_free(l, 0);
    l = 0;

    list *t = list_add(&l, strdup("113"));
    list *k = list_add(&l, strdup("114"));
    (void)k;
    list_add(&l, strdup("115"));
    
    list_del(&l, t, free);


    assert(!strcmp(l->data, "114"));
    assert(!strcmp(l->next->data, "115"));
    assert(l->next->next == 0);
   /*
    i = l;
    while (i)
    {
        printf("v: %s\n", i->data);
        i = i->next;
    }*/
    list_free(l, free);

    printf("---------------\n");
    printf("LIBLIST.a   TESTS OK\n\n");
    printf("---------------\n");
}
