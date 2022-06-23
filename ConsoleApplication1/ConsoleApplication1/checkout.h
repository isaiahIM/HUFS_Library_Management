#ifndef _CHECKOUT__H
#define _CHECKOUT__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student_DB.h"
#include "library_DB.h"

#define STR_MAX 50

typedef struct CheckoutInfoStructure
{
    lib_DB checkout_books;
    student_info student;
    struct CheckoutInfoStructure* next;
} checkout_info;

typedef struct CheckoutDBStructure
{
    int count;
    checkout_info* checkout_list;// total student list
} checkout_DB;

checkout_DB checkouts;

void CheckoutDB_Init(void);
int CheckoutBook(char *book_name);
int ReturnBook(char *name);
int SearchCheckoutBook(char *book_name);
int SearchCheckoutID(char *id);
void DisplayCheckoutBook(checkout_info *checkout);
void DisplayCheckoutList(void);

#endif