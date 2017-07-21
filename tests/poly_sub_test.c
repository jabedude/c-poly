#include <stdio.h>
#include "polynomial.h"

int main(void)
{
    polynomial *a = term_create(3, 2U);
    polynomial *b = term_create(-6, 1U);
    polynomial *c = term_create(1, 0U);
    a->next = b;
    b->next = c;
    printf("Poly one is -- %s\n", poly_to_string(a));

    polynomial *d = term_create(50, 3U);
    polynomial *e = term_create(8, 2U);
    polynomial *f = term_create(10, 1U);
    polynomial *g = term_create(4, 0U);
    d->next = e;
    e->next = f;
    f->next = g;
    printf("Poly two is -- %s\n", poly_to_string(d));

    printf("TESTING SUB(): Answer should be -50x^3 -5x^2 -16x -3\n");
    poly_print(poly_sub(a, d));

    return 0;
}
