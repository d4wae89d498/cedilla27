#include "ft.h"

// TODO : make me more serious
str_list *explode(const char *src, int (*is_sep)(const char *))
{
    const char *a;
    char *s;
    int r = 0;
    str_list    *output = 0;

    a = src;
    while (*src)
    {
        r = is_sep(src);
        if (r)
        {
            if (src > a)
            {
                s = strdup(a);
                s[src - a] = 0;
                str_list_add(&output, s);
            }
            src += r;
            a = src;
        }
        else
            src += 1;
    }
    if (src > a)
    {
        s = strdup(a);
        s[src - a] = 0;
        str_list_add(&output, s);
    }
    return output;
}
