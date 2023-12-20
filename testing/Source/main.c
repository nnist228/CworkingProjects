#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>


int main()
{
    char a = 'a';
    const char* ptr = &a;

    const char* heyp[] = {"├", "е", "у"};

    printf("Deciaml code: %s and ptr:%d \n", heyp[a - a], (*ptr));

    return 0;
}