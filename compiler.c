#include "compiler.h"

DEF_LIST(ast_node*,     ast_node_list,		free)
DEF_LIST(parser*,       parser_list, 		0)
DEF_LIST(preprocessor*, preprocessor_list, 	0)
DEF_LIST(compiler*,     compiler_list, 		0)
DEF_LIST(void*,     	ext_list, 			dlclose)

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

		if (try_o && (!o || (strlen(o->src) >= strlen(try_o->src))))
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
	preprocessor_list 	*it;
	const char			*r;
	char				*try_new_src;
	char				*new_src = 0;
	size_t				depth = 0;

	r = src;
	depth = 0;
	print("Preprocessing...\n");
	while (*src)
	{
		new_src = 0;
		it = preprocessors;
		while (it)
		{
			try_new_src = it->data(src);
			if (try_new_src)
				new_src = try_new_src;
			it = it->next;
		}
		if (new_src)
		{
			r = new_src;
			src = new_src;
		}
		else 
			src += 1;
	}
	return strdup(r);
}

/*
 * Compile all nodes
 */ 
char *compile(ast_node_list *nodes)
{
	size_t		max_item;
	char		*s;
	str_list	*sl = 0;
	while (nodes)
	{
		compiler_list	*cl = compilers;	
		while (cl)
		{
			s = cl->data(nodes->data);	
			if (s)
			{
				return s;
			}
			cl = cl->next;
		}

		nodes = nodes->next;
	}
	return 0;
}

/*
 * Returns an ast node list by parsing src. Returns 0 if something can't be parsed.
 */
ast_node_list *parse_all(const char *src)
{
	size_t			i = 0;	
	ast_node_list	*o = 0;

	i = 0;
	while (src[i])
	{
		ast_node		*n = parse(src + i);
		if (!n)
		{
			return 0;
		}
		ast_node_list_add(&o, n);
		src += strlen(n->src);
		i = 0;
		continue ;
		i += 1;
	}
    return o;
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
		dlclose(handle);
		print ("missing register_ext function for ext : %s\n", path);
		return false;
	}
	ext_list_add(&exts, handle);
	return f(ac, av, &parsers, &preprocessors, &compilers);
}

void	compiler_init()
{
	parsers = 0;
	preprocessors = 0;
	compilers = 0;
	exts = 0;
}

void	compiler_destroy()
{
	ext_list 	*el = exts;
	while (el)
	{
		void (*f)() = dlsym(el->data, "on_unload_ext");
		if (f)
			f();
		el = el->next;
	}
	if (parsers)
		parser_list_free(parsers);
	if (preprocessors)
		preprocessor_list_free(preprocessors);
	if (compilers)
		compiler_list_free(compilers);
	if (exts)
		ext_list_free(exts);
	parsers = 0;
	preprocessors = 0;
	compilers = 0;
	exts = 0;
}