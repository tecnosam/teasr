#ifndef MYIO

#define MYIO 1
#include <stdio.h>


char readc() {
    char c;
    scanf(" %c", &c);
    return c;
}

char printc(char c) {
    printf("%c", c);
}

#endif