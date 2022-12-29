#include "ft.h"

DEF_LIST(char*, str_list, free);

int str_is(const char *str, const char *str2)
{
    size_t  str_len = strlen(str2);
    if (!strcmp(str, str2))
        return str_len;
    return 0; 
}

int str_is_prefixed(const char *str, const char *prefix)
{
    size_t  prefix_len = strlen(prefix);
    if (!strncmp(str, prefix, prefix_len))
        return prefix_len;
    return 0; 
}


const char *strrchr_cb(const char *str, bool (*is)(const char *src))
{
    ull len = strlen(str);

    while (len)
    {
        len -= 1;
        if (is(str + len))
            return str + len;
    }    
    return 0;
}
