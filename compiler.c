#include "compiler.h"

void	load_ext(int ac, char **av, char *path)
{
	void	*handle = dlopen(path, RTLD_NOW);
	if (!handle)
	{
		print ("ext not found : %s\n", path);
	}
	on_load_ext_t *f = dlsym(handle, "on_load_ext");
	if (!f)
	{
		print ("missing register_ext function for ext : %s\n", path);
	}
	f(ac, av, &parsers, &macros, &compilers);
}



char		*preprocess(const char *src)
{
	print("Preprocessing...\n");

	char	*new_src;

	while (*src)
	{
		new_src = try_apply_patterns(src);
		if (new_src)
			src = new_src;
		else 
			src += 1;
	}

	return 0;
}

ast_node	*parse_node(const char *src)
{
	parser_list *pl = parsers;
	ast_node *o;

	while (pl)
	{
		o = pl->data(src);
		if (o)
			return o;	
		pl = pl->next;
	
	return 0;
}


ast_node_list	
			*parse_nodes(const char *src)
{
	ast_node_list	*o;

	while (src)
	{
		// if node found, also increment src 
		src += 1;
	}
}

char		*compile(ast_node_list *nodes)
{

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
    char    *exts = 0;
    char    *source = 0;
    ull     aci;

    if (ac < 4)
    {
        print("Usage: %s  [-E] --EXTS=\"...\" <source_file>\n", av[0]);
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
			source = av[aci];
		else 
			return !!print("error, only one source argument shall be written\n");
        aci += 1;
    }
	if (!exts)
		return !!print("error, --EXTS flags is missing\n");

	print("-----------------------------\n");
	print("cedilla compiler 0.0\n");
	print("-----------------------------\n");
	print("do_compile :\t%i\n", do_compile);
	print("extensons :\t%s\n", exts);
	print("source :\t%s\n", source);
	print("-----------------------------\n");
    str_list *ext_list = 0;

    explode(exts, skip_space, &ext_list);

	while (ext_list)
	{
		print("-- loading ext=[%s] ...\n", ext_list->data);
		load_ext(ac, av, ext_list->data);
		ext_list = ext_list->next;
	}


	// try link all preprocessors

	// for each char ... transpile

	// echo transpiled version if -E, else save it in an intermediate file

	if (do_compile)
	{
		
	}
	return 0;
}