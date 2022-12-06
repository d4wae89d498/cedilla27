NAME=ext.so

all: $(NAME)

$(NAME): ext.c ../../compiler ../../compiler.h
	cc -shared -fPIC ext.c -o ext.so

clean:
	rm -rf ext.so

re: clean all