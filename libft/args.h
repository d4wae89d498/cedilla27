#include "ft.h"

bool is_var(char *str, char *prefix, char **compiler)
{
    size_t prefix_len = strlen(prefix);
	bool r = (!strncmp(str, prefix, prefix_len) && str[prefix_len] == '=');
	if (r) {
		*compiler = str + prefix_len + 1;
		return true;
	}
	return false;
}

bool is_flag(char *str, char *prefix)
{
	size_t prefix_len = strlen(prefix);
    return (!strncmp(str, prefix, prefix_len) && (!str[prefix_len] || isspace(str[prefix_len])));
}


int skip_space(const char *s)
{
    int i = 0;
    while (isspace(s[i]))
        i += 1;
    return i;
}