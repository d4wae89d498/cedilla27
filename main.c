#include "compiler.h"

int	main(int ac, char **av)
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
	if (do_compile)
	{
	}
	return 0;
}