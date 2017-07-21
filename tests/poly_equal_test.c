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

    printf("TESTING EQUAL(): Answer should be false\n");
    bool x = poly_equal(a, d);
    printf(x ? "true\n" : "false\n");

    polynomial *h = term_create(3, 2U);
    polynomial *i = term_create(-6, 1U);
    polynomial *j = term_create(1, 0U);
    h->next = i;
    i->next = j;
    printf("Poly three is -- %s\n", poly_to_string(h));

    printf("TESTING EQUAL(): Answer should be true\n");
    x = poly_equal(a, h);
    printf(x ? "true\n" : "false\n");

    return 0;
}
