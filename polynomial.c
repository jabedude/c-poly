#include <stdlib.h>
#include <stdio.h>

#include "polynomial.h"

polynomial *init_list(int coeff, unsigned int exp)
{
    polynomial *head = malloc(sizeof(polynomial));
    
    if (head) {
        head->coeff = coeff;
        head->exp   = exp;
        head->next  = NULL;
    }

    return head;
}

void list_destroy(polynomial *list)
{
    while (list) {
        polynomial *tmp = list->next;
        free(list);
        list = tmp;
    }
}

void print_list(const polynomial *list)
{
    if (!list) {
        printf("List empty\n");
        return;
    }
    
    if (list->coeff) {
        printf("%c%d", list->coeff > 0 ? '+' : '\0', list->coeff);
        if (list->exp > 1)
            printf("x^%d", list->exp);
        else if (list->exp == 1)
            printf("x");
        
        printf(" ");
    }
    
    print_list(list->next);
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
