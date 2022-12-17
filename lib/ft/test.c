#include "ft.h"
#include "assert.h"

int main(void)
{
    char *str = "   .  .      .  hello1   d    p .      ";
    str_list *items;
    str_list * items_head;
    items_head = items;
    explode(str, skip_space, &items);
    items_head = items;
    while (items)
    {
        printf ("-- [%s]\n", items->data);
        items = items->next;   
    }
    assert(items_head->data[0] == '.');
    assert(str_is(items_head->next->next->next->data , "hello1"));
    printf("OK\n");
/*
    printf("printf(%s))\n", items->data);
    */
    assert(str_is_prefixed("--1;;HELLO", "--1;;"));
    printf("OK\n");
    
    assert(!str_is_prefixed("--1;;HELLO", "--10;"));
    printf("OK\n");
}