#include "compiler.h"

void	load_ext(int ac, char **av, char *path)
{
	void	*handle = dlopen(path, RTLD_NOW);
	if (!handle)
	{
		printf ("ext not found : %s\n", path);
	}
	on_load_ext_t *f = dlsym(handle, "on_load_ext");
	if (f)
	{
		printf ("missing register_ext function for ext : %s\n", path);
	}
	f(ac, av, &parsers, &macros, &compilers);
}

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

char	*read_file(char *path)
{
	int     fd;
	size_t  fsize;
	char	*src;
	ssize_t	bytes;
	char	*ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: open=%i for %s\n", errno, path);
		return 0;
	}
	fsize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	src = malloc(fsize + 1);
	if (!src)
	{
		close(fd);
		return 0;
	}
	src[fsize] = 0;
	fsize = 0;
	while((bytes = read(fd, src + fsize++, 1)))
		;
	if (bytes != 0)
	{
		printf("ERROR: read=%i for %s\n", errno, path);
		free(src);
		close(fd);
		return 0;
	}
	close(fd);
	return src;
}

/*
 *      FLAGS :
 *          
 *          -E
 *          --EXTS="ext/cpp ext/std"
 *              ext/std/cpp defines -D=value -I=./ flags
 *          <source_file>
 */
int main(int ac, char **av)
{
    bool    do_compile = true;
    char    *exts;
    char    *source;
    ull     aci;

    if (ac < 3)
    {
        printf("Usage: %s [-E | --COMPILER=... | -PREPROCESSORS=...] <source_file>\n", av[0]);
        return 0;
    }
    aci = 1;
    while (aci < ac)
    {
        if (is_flag(av[aci], "-E"))
			do_compile = false;
		else if (is_var(av[aci], "--EXTS", &exts))
			;
		else if (!source)
		{
			source = av[aci];
		}
		else 
			return !!printf("error, only one source argument shall be written\n");
        aci += 1;
    }


	printf("do_compile :\t%i\n", do_compile);
	printf("exts :\t%s\n", exts);
	printf("source :\t%s\n", source);
	printf("\n");
	printf("\n");
	printf("Preprocessing...\n");


	// try link all preprocessors

	// for each char ... transpile

	// echo transpiled version if -E, else save it in an intermediate file

	if (do_compile)
	{
		printf("Compiling...\n");
	}
	return 0;
}