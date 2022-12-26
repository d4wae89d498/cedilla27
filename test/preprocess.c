#include "../compiler.h"
#include "assert.h"

char    *find_str(compiler_ctx *ctx, const char **str)
{
    char    *s;
    size_t  p;

    if ((p = str_is_prefixed(*str, "__HELLO__")))
    {
        *str += strlen("__HELLO__");
        asprintf(&s, "%s%s", "hi!", *str + p);
        return s;
    }
    return 0;
}

int main()
{
    compiler_ctx ctx;
    compiler_init(&ctx);

    preprocessor_list_add(&(ctx.preprocessors), find_str);

    char *test = preprocess(&ctx, "__HELLO__ WORLD!");

    assert(test);
    assert(str_is(test, "hi! WORLD!"));
}