NAME=ext.so

all: $(NAME)

$(NAME): ext.c ../../compiler ../../compiler.h
	cc -shared -fPIC ext.c ../../compiler.o -o ext.so

clean:

fclean: clean
	rm -rf ext.so

re: clean all