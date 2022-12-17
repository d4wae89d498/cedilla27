#include "../compiler.h"
#include "assert.h"

ast_node    *parse_42(const char *src)
{
    if (!strncmp(src, "42", 2))
    {
        return alloc(ast_node, 
            .src="42", 
            .symbol="43", 
            .data=(void*)44
        );
    }
    return 0;
}

ast_node    *parse_ab(const char *src)
{
    if (!strncmp(src, "ab", 2))
    {
        return alloc(ast_node, 
            .src="ab", 
            .symbol="AB", 
            .data=(void*)47
        );
    }
    return 0;
}

int main()
{
    parser_list_add(&parsers, parse_42);
    parser_list_add(&parsers, parse_ab);
    
    ast_node_list *list = parse_all("ab42ab");

    assert(str_is(list->data->src, "ab"));
    assert(str_is(list->next->data->src, "42"));
    assert(str_is(list->next->next->data->src, "ab")); 
    assert(!(list->next->next->next)); 

    assert(!parse_all("ab420ab"));


    return 0;
}