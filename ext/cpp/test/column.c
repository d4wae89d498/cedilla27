#include <libc.h>
#include <assert.h>
int main()
{
    assert(__COLUMN__ == 12);
    printf ("OK\n");
}
