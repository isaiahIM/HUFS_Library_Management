#ifndef _LIBRARY_DB__H
#define _LIBRARY_DB__H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 50


typedef struct BookInfoStructure
{
    char name[STR_MAX];
    char author[STR_MAX];
    int page;
    int price;
    struct BookInfoStructure* next;
} book_info;

typedef struct LibraryDBStructure
{
    int book_cnt;
    book_info* book_list;// total book list
} lib_DB;

lib_DB library;

void LibDB_Init(void);
void AddBook(char* name, char* author, int page, int price);
int DeleteBook(char* name);
book_info SearchBook(char* name);
void DisplayBook(book_info *book);
void DisplayBookList(void);

#endif