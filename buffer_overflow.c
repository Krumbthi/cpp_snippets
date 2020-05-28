#include <stdio.h>
#include <string.h>

int main()
{
    char buf[10];
    memcpy(buf, "fnord", 6);
    memcpy(buf, "fnordfnordfn", 11);

    return 0;
}
