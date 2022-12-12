#include "ft.h"

int main(void)
{
    char *str = "   .  .      .  hello1   d    p .      ";
    str_list *items = 0;

    explode(str, skip_space, &items);

    while (items)
    {
        printf ("-- [%s]\n", items->data);
        items = items->next;   
    }
}