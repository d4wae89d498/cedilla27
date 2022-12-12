#include "compiler.h"

DEF_LIST(ast_node*,     ast_node_list)
DEF_LIST(parser*,       parser_list)
DEF_LIST(preprocessor*, preprocessor_list)
DEF_LIST(compiler*,     compiler_list)

/*
 *	Returns biggest possible ast_node or 0
 */
ast_node *parse(const char *src)
{
	ast_node	*o = 0;
	ast_node	*try_o;
	parser_list	*pl;
	size_t		match_len = 0;

	pl = parsers;
	while (pl)
	{
		try_o = pl->data(src);

		if (!o || (strlen(o->src) >= match_len))
		{
			o = try_o;
		}

		pl = pl->next;
	}
	return o;	
}

/*
 *	Returns src by applying macros, will also apply macros in macros outputs
 */ 
char *preprocess(const char *src)
{
	char	*new_src;

	print("Preprocessing...\n");
	while (*src)
	{
		new_src = 0;
		if (new_src)
			src = new_src;
		else 
			src += 1;
	}

	return 0;
}

/*
 * Compile all nodes
 */ 
char *compile(ast_node_list *nodes)
{
	return 0;
}

/*
 * Returns an ast node list by parsing src. Returns 0 if something can't be parsed.
 */
ast_node_list *parse_all(const char *src)
{
    return 0;
}

/*
 * Try to load a compiler extension. Returns true on success, false on failure.
 */
bool load_ext(int ac, char **av, char *path)
{
	void	*handle = dlopen(path, RTLD_NOW);
	if (!handle)
	{
		print ("ext not found : %s\n", path);
		return false;
	}
	on_load_ext_t *f = dlsym(handle, "on_load_ext");
	if (!f)
	{
		print ("missing register_ext function for ext : %s\n", path);
		return false;
	}
	return f(ac, av, &parsers, &preprocessors, &compilers);
}
