#include <stdio.h>
#include "polynomial.h"

int main(void)
{
    polynomial *a = term_create(3, 2U);
    polynomial *b = term_create(-6, 1U);
    polynomial *c = term_create(1, 0U);

    a->next = b;
    b->next = c;
    
    printf("COMPARING poly_print and poly_to_string output\n");
    printf("First Poly -- ");
    poly_print(a);
    char *s = poly_to_string(a);
    printf("First Poly -- %s\n", s);

    return 0;
}
