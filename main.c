#include "compiler.h"

int	main(int ac, char **av)
{
    bool    do_compile = true;
    char    *exts = 0;
    char    *source_path = 0;
    ull     aci;

	
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
		else if (!source_path)
			source_path = av[aci];
		else 
			return !!print("error, only one source argument shall be written\n");
        aci += 1;
    }
	if (!exts)
		return !!print("error, --EXTS flags is missing\n");
	atexit(compiler_destroy);
	print("-----------------------------\n");
	print("cedilla compiler 0.0\n");
	print("-----------------------------\n");
	print("do_compile :\t%i\n", do_compile);
	print("extensons :\t%s\n", exts);
	print("source :\t%s\n", source_path);
	print("-----------------------------\n");
    str_list *ext_list = explode(exts, skip_space);
	while (ext_list)
	{
		print("loading ext=[%s] ...\n", ext_list->data);
		load_ext(ac, av, ext_list->data);
		ext_list = ext_list->next;
	}
	str_list_free(ext_list);
	char *source = read_file(source_path);
	if (!source)
		return !!print("File error.\n");
	char *esource = preprocess(source);
	free(source);
	if (!esource)
		return !!print("Preprocessing error.\n");
	if (do_compile)
	{
		ast_node_list *nodes = parse_all(esource);
		free(esource);
		if (!nodes)
		{
			return !!print("Parse error.\n");
		}
		char *out = compile(nodes);	
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
	return 0;
}