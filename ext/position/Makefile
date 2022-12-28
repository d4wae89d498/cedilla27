NAME=ext.so

all: $(NAME)

$(NAME): ext.c ../../compiler.h ../../compiler.c
	cc -fsanitize=address -shared -fPIC ext.c ../../compiler.o ../../lib/ft/libft.a -o ext.so

clean:

fclean: clean
	rm -rf ext.so

re: clean all