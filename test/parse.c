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

int main(void)
{
    parser_list_add(&parsers, parse_42);
    ast_node *test = parse("0");
    assert(test == 0);
    test = parse("42");
    assert(test);
    assert(!strcmp(test->symbol, "43"));
    assert(test->data == (void*) 44);
    assert(!strcmp(test->src, "42"));
    test = parse("042");
    assert(test == 0);

    parser_list_add(&parsers, parse_ab);

    test = parse("ab");
    assert(test);
    assert(!strcmp(test->src, "ab"));
    assert(!strcmp(test->symbol, "AB"));
    assert(test->data = (void*)47);

    return 0;
}