#include "../compiler.h"
#include "assert.h"

char    *find_str(const char *str)
{
    char    *s;
    size_t  p;

    if ((p = str_is_prefixed(str, "__HELLO__")))
    {
        asprintf(&s, "%s%s", "hi!", str + p);
        return s;
    }
    return 0;
}

int main()
{
    preprocessor_list_add(&preprocessors, find_str);

    char *test = preprocess("__HELLO__ WORLD!");

    assert(test);
    assert(str_is(test, "hi! WORLD!"));
}