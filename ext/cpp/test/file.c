#include "../../../compiler.h"
#include <assert.h>
#define A 42
int main()
{
	assert(__LINE__ == 6);
	print ("TEST OK\n");
}
