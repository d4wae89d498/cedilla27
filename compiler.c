#include "compiler.h"

DEF_LIST(ast_node*,     ast_node_list,		free)
DEF_LIST(parser*,       parser_list, 		0)
DEF_LIST(preprocessor*, preprocessor_list, 	0)
DEF_LIST(compiler*,     compiler_list, 		0)
DEF_LIST(void*,     	ext_list, 			dlclose)

/*
 *	Returns biggest possible ast_node or 0
 */
ast_node *parse(compiler_ctx *ctx, const char *src)
{
	ast_node			*o = 0;
	ast_node			*try_o;
	parser_list			*pl;
	size_t				match_len = 0;

	pl = parser_list_last(ctx->parsers);
	while (pl)
	{
		try_o = pl->data(ctx, src);

		if (try_o && (!o || (strlen(o->src) >= strlen(try_o->src))))
		{
			o = try_o;
		}
		pl = pl->prev;
	}
	return o;	
}

/*
 *	Returns src by applying macros, will also apply macros in macros outputs
 */ 
char *preprocess_all(compiler_ctx *ctx, const char *src)
{
	preprocessor_list 	*it;
	char 				*srci;
	char				*srci_bkp;
	const char 			*replacement;
	char				*output;

	srci = strdup(src);
	output = "";
	print("Preprocessing...\n");
	while (*srci)
	{
		int tentatives = 0;
		try_all_macros:
			if(tentatives++ >= MAX_PREPROCESSOR_TENTATIVES)
			{
				print ("WARNING : MAX_PREPROCESSOR_TENTATIVES reached in %s:%llu:%llu. Try to use no_expand: in your macros.\n", 
						ctx->get_current_file(), ctx->get_current_line(), ctx->get_current_column());
				srci += 1;
			}
		it = preprocessor_list_last(ctx->preprocessors);
		while (it)
		{
			// todo : check if srci changed, restart from 
			srci_bkp = srci;
			replacement = it->data(ctx, (const char **)&srci);
			if (replacement)
			{
				if (str_is(srci_bkp, srci))
				{
					print ("ERROR: src ptr incrementation missing in a macro that add a replacement.\n");
					exit (1);
				}
				if (str_is_prefixed(replacement, "no_expand:")) 
					asprintf(&output, "%s%s", output, replacement + strlen("no_expand:"));
				else 
					asprintf(&srci, "%s%s", replacement, srci);
				goto try_all_macros;	
			}
			else if (srci_bkp != srci)
				goto try_all_macros;
			it = it->prev;
		}
		asprintf(&output, "%s%c", output, *srci);
		srci += 1;
	}
	return output;
}

/*
 * Compile all nodes
 */ 
char *compile_all(compiler_ctx *ctx, ast_node_list *nodes)
{
	compiler_list		*cl;
	size_t				max_item;
	char				*s;
	str_list			*sl = 0;

	while (nodes)
	{
		cl = compiler_list_last(ctx->compilers);	
		while (cl)
		{
			s = cl->data(ctx, nodes->data);	
			if (s)
			{
				return s;
			}
			cl = cl->prev;
		}
		nodes = nodes->next;
	}
	return 0;
}

/*
 * Returns an ast node list by parsing src. Returns 0 if something can't be parsed.
 */
ast_node_list *parse_all(compiler_ctx *ctx, const char *src)
{
	ast_node_list		*o = 0;
	ast_node			*n;

	while (*src)
	{
		n = parse(ctx, src);
		if (!n)
		{
			print ("Parse error in file %s:%llu:%llu\n", ctx->get_current_file(ctx), ctx->get_current_line(ctx), ctx->get_current_column(ctx));
			return 0;
		}
		ast_node_list_add(&o, n);
		if (ctx->on_parse)	
			ctx->on_parse(ctx, n);
		src += strlen(n->src);
	}
    return o;
}

/*
 * Try to load a compiler extension. Returns true on success, false on failure.
 */
bool load_ext(compiler_ctx* ctx, int ac, char **av, char *path)
{
	void				*handle;
	on_load_ext_t 		*f;

	handle = dlopen(path, RTLD_NOW);
	if (!handle)
	{
		print ("ext not found : %s\n", path);
		return false;
	}
	f = dlsym(handle, "on_load_ext");
	if (!f)
	{
		dlclose(handle);
		print ("missing register_ext function for ext : %s\n", path);
		return false;
	}
	ext_list_add(&(ctx->exts), handle);
	bool r =  f(ctx, ac, av);
	return r;
}

static const char	*default_file_getter()
{
	return "(unknow_file)";
}

static ull			default_int_getter()
{
	return 0;
}

static const char	*default_language_getter()
{
	return DEFAULT_LANGUAGE;
}

static float		default_language_version_getter()
{
	return DEFAULT_LANGUAGE_VERSION;
}

static void			default_str_setter(const char *s)
{
	(void)s;
}

static void 		default_int_setter(ull i)
{
	(void)i;
}

static void			default_float_setter(float f)
{
	(void)f;
}

void	compiler_init(compiler_ctx *ctx)
{
	*ctx = (compiler_ctx) {
    	.parsers = 0,
    	.preprocessors = 0,
   		.compilers = 0,
    	.exts = 0,
    	.source_path = 0,

    	.get_current_file = default_file_getter,
		.get_current_line = default_int_getter,
		.get_current_column = default_int_getter,
		.get_current_language = default_language_getter,
		.get_current_language_version = default_language_version_getter,

    	.set_current_file = default_str_setter,
		.set_current_line = default_int_setter,
		.set_current_column = default_int_setter,
		.set_current_language = default_str_setter,
		.set_current_language_version = default_float_setter,

		.is_new_line = 0
	};
}

void	compiler_destroy(compiler_ctx *ctx)
{
	return ; // todo : fix leaks
	ext_list 		*el = ctx->exts;

	while (el)
	{
		void (*f)() = dlsym(el->data, "on_unload_ext");
		if (f)
			f();
		el = el->next;
	}
	if (ctx->parsers)
		parser_list_free(ctx->parsers);
	if (ctx->preprocessors)
		preprocessor_list_free(ctx->preprocessors);
	if (ctx->compilers)
		compiler_list_free(ctx->compilers);
	if (ctx->exts)
		ext_list_free(ctx->exts);
	ctx->parsers = 0;
	ctx->preprocessors = 0;
	ctx->compilers = 0;
	ctx->exts = 0;
}