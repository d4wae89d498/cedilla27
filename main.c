#include "compiler.h"

int	main(int ac, char **av)
{
    char    		*exts = 0;
    int    			aci;
	compiler_ctx 	ctx;
	bool			do_compile = true;

	compiler_init(&ctx);
    if (ac < 3)
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
		else if (str_is(ctx.file, DEFAULT_FILE_NAME))
			ctx.file = av[aci];
		else 
			return !!print("error, only one source argument shall be written\n");
        aci += 1;
    }
	if (!exts)
		return !!print("error, --EXTS flags is missing\n");
	
	print("-----------------------------\n");
	print("do_compile :\t%i\n", do_compile);
	print("extensons :\t%s\n", exts);
	print("source :\t%s\n", ctx.file);
	print("-----------------------------\n");
    str_list *ext_list = explode(exts, skip_space);
	ctx.do_compile = false;
	while (ext_list)
	{
		if (!load_ext(&ctx, ac, av, ext_list->data))
			print ("Fail to load ext %s\n", ext_list->data);
		ext_list = ext_list->next;
	}
	str_list_free(ext_list);
	char *source = read_file(ctx.file);
	if (!source)
		return !!print("File error.\n");
	char *esource = preprocess_all(&ctx, source);
	free(source);
	if (!esource)
		return !!print("Preprocessing error.\n");
	if (do_compile)
	{
		ctx.do_compile = true;
		ctx.line = 1;
		ctx.column = 1;
		ast_node_list *nodes = parse_all(&ctx, esource);
		free(esource);
		if (!nodes)
		{
			return !!print("Parse error.\n");
		}
		char *out = compile_all(&ctx, nodes);	
		ast_node_list_free(nodes);
		if (out)
		{
			printf("%s\n", out);
			free(out);
		}
		else 
			return !!print ("Compilation error.'n");
	}
	else 
	{
		printf("%s\n", esource);
		free(esource);
	}
	compiler_destroy(&ctx);
	return 0;
}