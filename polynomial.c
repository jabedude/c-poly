#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "polynomial.h"

/* Static prototypes */
static int term_count(const polynomial *eqn);
static polynomial *_poly_op(const polynomial *a, const polynomial *b, int op);
static void _poly_neg(polynomial *p);
static void _poly_rm_end(polynomial *p);

polynomial *term_create(int coeff, unsigned int exp)
{
    polynomial *head = malloc(sizeof(polynomial));

    if (head) {
        head->coeff = coeff;
        head->exp   = exp;
        head->next  = NULL;
    }

    return head;
}

void poly_destroy(polynomial *list)
{
    while (list) {
        polynomial *tmp = list->next;
        free(list);
        list = tmp;
    }
}

void poly_print(const polynomial *list) /* TODO: just call poly_to_string */
{
    if (list == NULL) {
        printf("List empty\n");
        return;
    }

    if (list->coeff) {
        printf("%c%d", list->coeff > 0 ? '+' : '\0', list->coeff);
        if (list->exp > 1)
            printf("x^%d", list->exp);
        else if (list->exp == 1)
            printf("x");
        else if (list->exp == 0) {
            putchar('\n');
            return;
        }

        printf(" ");
    }

    if (list->next)
        poly_print(list->next);
    else {
        putchar('\n');
        return;
    }
}

char *poly_to_string(const polynomial *p) /* TODO: exact number of bytes needed */
{
    if (!p) {
        printf("List empty\n");
        return NULL;
    }

    polynomial *tmp = (polynomial *) p;
    int len = term_count(tmp);
    //printf("DEBUG: count is %d\n", len);
    //char *s = malloc(sizeof(char) * (len * 5) + 1);
    char *s = (char *) "";

    for (int i = 0; i < len; i++) {
        asprintf(&s, "%s%c%d", s, tmp->coeff > 0 ? '+' : '\0', tmp->coeff);
        if (tmp->exp > 1)
            asprintf(&s, "%sx^%d ", s, tmp->exp);
        else if (tmp->exp == 1)
            asprintf(&s, "%sx ", s);
        tmp = tmp->next;
    }
/*
    while (tmp) {
        asprintf(&s, "%c%d ", tmp->coeff > 0 ? '+' : '\0', tmp->coeff);
        if (tmp->exp > 1)
            asprintf(&s, "x^%d ", tmp->exp);
        else if (tmp->exp == 1)
            asprintf(&s, "x ");
        tmp = tmp->next;
    }
*/
    return s;
}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    polynomial *a_head = (polynomial *) a;
    polynomial *b_head = (polynomial *) b;
    polynomial *ret = term_create(0,0U);
    polynomial *head = ret;

    while (a_head->next && b_head->next) {

        if (a_head->exp > b_head->exp) { /* If a is greater than b */
            ret->coeff = a_head->coeff;
            ret->exp = a_head->exp;
            a_head = a_head->next;
        } else if (b_head->exp > a_head->exp) { /* If b is greater than a */
            ret->coeff = b_head->coeff;
            ret->exp = b_head->exp;
            b_head = b_head->next;
        } else { /* Exponents are the same */
            ret->exp = a_head->exp;
            ret->coeff = a_head->coeff + b_head->coeff;
            //ret->coeff = (op == ADDITION) ? (a_head->coeff + b_head->coeff) : (a_head->coeff - b_head->coeff);
            a_head = a_head->next;
            b_head = b_head->next;
        }

        ret->next = term_create(0, 0U);
        ret = ret->next;
    }

    if (a_head->coeff && b_head->coeff) {
            ret->exp = a_head->exp;
            ret->coeff = a_head->coeff + b_head->coeff;
            //ret->coeff = (op == ADDITION) ? (a_head->coeff + b_head->coeff) : (a_head->coeff - b_head->coeff);
            a_head = a_head->next;
            b_head = b_head->next;

            ret->next = term_create(0, 0U);
            ret = ret->next;

            return head;
    }

    while (a_head->next || b_head->next) {
        if (a_head->next) {
            ret->coeff = a_head->coeff;
            ret->exp = a_head->exp;
            a_head = a_head->next;
        }
        if (b_head->exp > a_head->exp) {
            ret->coeff = b_head->coeff;
            ret->exp = b_head->exp;
            b_head = b_head->next;
        }

        ret->next = term_create(0, 0U);
        ret = ret->next;
    }

    return head;
}

void poly_iterate(polynomial *p, void (*transform)(struct term *))
{
    while (p) {
        (*transform)(p);
        p = p->next;
    }
}

double poly_eval(const polynomial *a, double x)
{
    double ret = 0, d;
    polynomial *tmp = (polynomial *) a;

    while (tmp) {
        d = x;
        if (tmp->exp) {
            d = pow(x, tmp->exp);
            d *= tmp->coeff;
            ret += d;
        } else {
            ret += tmp->coeff;
        }
        tmp = tmp->next;
    }

    return ret;
}

bool poly_equal(const polynomial *a, const polynomial *b)
{
    char *a_str = poly_to_string(a);
    char *b_str = poly_to_string(b);

    int ret = strcmp(a_str, b_str);
    free(a_str);
    free(b_str);

    return ret ? false : true;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    return _poly_op(a, b, SUBTRACTION);
/*
    polynomial *tmp = (polynomial *) b;
    poly_print(tmp);
    poly_iterate(tmp, _poly_neg);
    printf("NEG\n");
    poly_print(tmp);
    return poly_add(a, tmp);
*/
}

void append(polynomial *list, int data)
{
    polynomial *ptr = list;

    while (ptr->next != NULL)
        ptr = ptr->next;

    polynomial *new = malloc(sizeof(polynomial));
    new->coeff = data;
    new->next = NULL;

    ptr->next = new;
}

void delete_from_list(polynomial **list, int position)
{
    int c = 0;
    polynomial *ptr = *list, *tmp;

    if (*list == NULL) {
        printf("Error, list empty\n");
        return;
    }

    /* Deletion from begining */
    if (position == 0) {
        *list = (*list)->next;
        free(ptr);
        return;
    } else {
        while ((ptr->next != NULL) && (c < position)) {
            c++;
            tmp = ptr;
            ptr = ptr->next;
        }
        if (!ptr) {
            printf("Index error\n");
            return;
        } else {
            tmp->next = ptr->next;
            free(ptr);
            return;
        }
    }

}

static int term_count(const polynomial *eqn)
{
    int c = 0;
    polynomial *tmp = (polynomial *) eqn;

    while (tmp) {
        c++;
        tmp = tmp->next;
    }

    return c;
}

static void _poly_neg(polynomial *p)
{
    p->coeff = -(p->coeff);
}

static polynomial *_poly_op(const polynomial *a, const polynomial *b, int op)
{
    polynomial *a_head = (polynomial *) a;
    polynomial *b_head = (polynomial *) b;
    polynomial *ret = term_create(0,0U);
    polynomial *head = ret;

    while (a_head->next && b_head->next) {

        if (a_head->exp > b_head->exp) { /* If a is greater than b */
            //ret->coeff = a_head->coeff;
            ret->coeff = (op == ADDITION) ? (a_head->coeff) : -(a_head->coeff);
            ret->exp = a_head->exp;
            a_head = a_head->next;
        } else if (b_head->exp > a_head->exp) { /* If b is greater than a */
            //ret->coeff = b_head->coeff;
            ret->coeff = (op == ADDITION) ? (b_head->coeff) : -(b_head->coeff);
            ret->exp = b_head->exp;
            b_head = b_head->next;
        } else { /* Exponents are the same */
            ret->exp = a_head->exp;
            //ret->coeff = a_head->coeff + b_head->coeff;
            ret->coeff = (op == ADDITION) ? (a_head->coeff + b_head->coeff) : (a_head->coeff - b_head->coeff);
            a_head = a_head->next;
            b_head = b_head->next;
        }

        ret->next = term_create(0, 0U);
        ret = ret->next;
    }

    if (a_head->coeff && b_head->coeff) {
            ret->exp = a_head->exp;
            //ret->coeff = a_head->coeff + b_head->coeff;
            ret->coeff = (op == ADDITION) ? (a_head->coeff + b_head->coeff) : (a_head->coeff - b_head->coeff);
            a_head = a_head->next;
            b_head = b_head->next;

            //ret->next = term_create(0, 0U);
            //ret = ret->next;
            if (!(ret->coeff) && !(ret->exp))
                _poly_rm_end(head);

            return head;
    }

    while (a_head->next || b_head->next) {
        if (a_head->next) {
            ret->coeff = a_head->coeff;
            ret->exp = a_head->exp;
            a_head = a_head->next;
        }
        if (b_head->exp > a_head->exp) {
            ret->coeff = b_head->coeff;
            ret->exp = b_head->exp;
            b_head = b_head->next;
        }

        ret->next = term_create(0, 0U);
        ret = ret->next;
    }

    if (!(ret->coeff) && !(ret->exp))
        _poly_rm_end(head);

    return head;
}

static void _poly_rm_end(polynomial *p)
{
    polynomial *tmp = p, *t;

    while (tmp->next) {
        t = tmp;
        tmp = tmp->next;
    }
    free(t->next);
    t->next = NULL;
}
