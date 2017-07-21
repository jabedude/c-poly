#ifndef POLY_HEADER
#define POLY_HEADER

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

void append(polynomial *list, int data);
void delete_from_list(polynomial **list, int position);

#endif
