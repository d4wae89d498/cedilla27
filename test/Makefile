SRCS	= $(shell ls *.c)
BINS 	= $(SRCS:.c=)
CFLAGS 	= -g -fsanitize=address

all: $(BINS)

%:	%.c Makefile ../compiler.o
	cc $(CFLAGS) $< ../compiler.o ../lib/ft/libft.a -o $@

run: $(BINS)
	$(subst $() $(),$() $()&&$() $(),$(addprefix ./, $(BINS)))

clean:
	rm -rf $(BINS)

re: clean all

.PHONY: run all re clean
.SUFIXES:

