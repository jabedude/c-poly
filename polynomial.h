#ifndef POLY_HEADER
#define POLY_HEADER

#include <stdbool.h>

#define ADDITION 1
#define SUBTRACTION 2

/* Typedefs */
typedef struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
} polynomial;

/* Function prototypes */
polynomial *term_create(int coeff, unsigned int esp);
void poly_destroy(polynomial *list);
void poly_print(const polynomial *list);
char *poly_to_string(const polynomial *p);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);
bool poly_equal(const polynomial *a, const polynomial *b);
double poly_eval(const polynomial *a, double x);
void poly_iterate(polynomial *p, void (*transform)(struct term *));


void append(polynomial *list, int data);
void delete_from_list(polynomial **list, int position);

#endif
