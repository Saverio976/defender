#include <unistd.h>

void my_putstr(char *str)
{
    write(1, str, strlen(str));
}

int main()
{
    int a = 2;

    void (*print)(char *) = &my_putstr;
    print("abc\n");
}
