#include <libc.h>
#include <assert.h>

int main()
{
	assert(!strcmp(__FILE__, "test/file.c"));
    printf ("OK\n");

}
