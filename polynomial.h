#ifndef POLY_HEADER
#define POLY_HEADER

/* Typedefs */
typedef struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
} polynomial;

/* Function prototypes */
polynomial *init_list(int coeff, unsigned int esp);
void list_destroy(polynomial *list);
void print_list(const polynomial *list);
char *poly_to_string(const polynomial *p);

void append(polynomial *list, int data);
void delete_from_list(polynomial **list, int position);

#endif
