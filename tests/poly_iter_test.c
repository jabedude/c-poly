#include <stdio.h>
#include "polynomial.h"

void neg(polynomial *p)
{
    p->coeff = -(p->coeff);
}

int main(void)
{
    polynomial *a = term_create(3, 2U);
    polynomial *b = term_create(-6, 1U);
    polynomial *c = term_create(1, 0U);
    a->next = b;
    b->next = c;
    printf("Poly one is -- %s\n", poly_to_string(a));

    printf("TESTING ITER(): Answer should be -3x^2 +6x -1\n");
    poly_iterate(a, neg);
    printf("%s\n", poly_to_string(a));

    return 0;
}
