#include "library_DB.h"


void LibDB_Init(void)
{
    library.book_cnt = 0;
    library.book_list = NULL;
}

void AddBook(char* name, char* author, int page, int price)
{
    book_info* new_book = (book_info*)malloc(sizeof(book_info));
    if (new_book != NULL)
    {
        strcpy(new_book->name, name);
        strcpy(new_book->author, author);
        new_book->page = page;
        new_book->price = price;

        if (library.book_list == NULL)// first insert
        {
            library.book_list = new_book;
            new_book->next = NULL;
        }
        else
        {
            new_book->next=library.book_list;
            library.book_list = new_book;
        }

        library.book_cnt++;
    }

}


book_info SearchBook(char* name)
{
    book_info* target;
    book_info book;

    target = library.book_list;

    while (target != NULL)// circular search
    {
        if (strcmp(name, target->name) == 0)
        {
            strcpy(book.author, target->author);
            strcpy(book.name, target->name);
            book.page = target->page;
            book.price = target->price;
            return book;
        }
        target = target->next;
    } 
    printf("2.book is not exist.\n");
    return book;
}

int DeleteBook(char* name)
{
    book_info* target, * prev;
    target = library.book_list;

    if (strcmp(name, target->name) == 0)// first node is delete node
    {
        library.book_cnt--;
        library.book_list = target->next;
        free(target);

        return 1;
    }
    prev = target;
    target = target->next;

    while (target != NULL)// circular search
    {
        if (strcmp(name, target->name) == 0)
        {
            library.book_cnt--;
            prev->next = target->next;
            free(target);
            return 1;
        }
        prev = target;
        target = target->next;
    }
    printf("book is not exist!\n");

    return 0;
}

void DisplayBook(book_info *book)
{
    printf("=====book info=====\n");
    printf("name: %s\n", book->name);
    printf("author: %s\n", book->author);
    printf("pages: %d pages\n", book->page);
    printf("price: %d won\n", book->price);
}

void DisplayBookList(void)
{
    book_info* book;

    book = library.book_list;
    if(book==NULL)
    {
        printf("book is empty!\n");
    }

    while (book != NULL)
    {
        DisplayBook(book);
        book = book->next;
    }
}
