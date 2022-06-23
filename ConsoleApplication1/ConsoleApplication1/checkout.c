#include "checkout.h"

void CheckoutDB_Init(void)
{
    checkouts.count=0;
    checkouts.checkout_list=NULL;
}

int CheckoutBook(char *book_name, student_info student)//???
{
    student_info checkouted_student;
    lib_DB student_bookDB;
    book_info book;
    checkout_info* target;

    book_info* new_book = (book_info*)malloc(sizeof(book_info));
    checkout_info* new_checkout=(checkout_info*)malloc(sizeof(checkout_info));

    /**log in */
    if(Login(student.id, student.pw)==0)
    {
        printf("login fail!\n");
        return 0;
    }

    /**check book is exist in DB */
    book=SearchBook(book_name);
    if(strcmp(book.name, book_name)!=0)
    {
        printf("book not exist!\n");
        return 0;
    }

    if(checkouts.checkout_list==NULL)// first checkout start
    {
        if (new_book != NULL)
        {
            if (new_checkout != NULL)
            {
                /**copy book info */
                strcpy(new_book->name, book.name);
                strcpy(new_book->author, book.author);
                new_book->page = book.page;
                new_book->price = book.price;

                /**copy student info */
                strcpy(new_checkout->student.id, student.id);
                strcpy(new_checkout->student.pw, student.pw);
                strcpy(new_checkout->student.name, student.name);

                new_checkout->checkout_books.book_cnt=1;
                new_checkout->next=NULL;

                /**link in database */
                checkouts.checkout_list=new_checkout;// error!
                new_book->next = NULL;
                new_checkout->checkout_books.book_list = new_book;
                
                return 0;
            }
        }
    }
    else
    {
        /**check book is checkouted */
        if(SearchCheckoutBook(book_name)==1)// check book is checkouted
        {
            printf("book is checkouted.\n");
            return 0;
        }

        /**copy book info */
        strcpy(new_book->name, book.name);
        strcpy(new_book->author, book.author);
        new_book->page = book.page;
        new_book->price = book.price;

        /**search checkout id position */
        target=checkouts.checkout_list;
        while(target!=NULL)
        {
            if(strcmp(student.id, target->student.id)==0)// target ID is equal.
            {
                if (target->checkout_books.book_list == NULL)// first insert in ID
                {
                    target->checkout_books.book_list = new_book;
                    new_book->next = NULL;
                }
                else
                {
                    new_book->next=target->checkout_books.book_list;
                    target->checkout_books.book_list = new_book;
                }
                target->checkout_books.book_cnt++;
                return 1;
            }
            target=target->next;
        }
        /**checkout ID is not exist */

        /**copy student info */
        strcpy(new_checkout->student.id, student.id);
        strcpy(new_checkout->student.pw, student.pw);
        strcpy(new_checkout->student.name, student.name);
        new_checkout->checkout_books.book_cnt=1;
        
        /**link in database */
        new_checkout->next=checkouts.checkout_list;
        new_checkout->checkout_books.book_list = new_book;
        checkouts.count+=1;
    }
}


int ReturnBook(char* name)
{
    checkout_info *target;
    book_info *book_target, *prev;

    if(checkouts.checkout_list==NULL)
    {
        printf("can't return!. this book is not checkouted.\n");
        return 0;
    }

    if(SearchCheckoutBook(name)==0)// check book is not checkouted.
    {
        printf("book is returned.\n");
        return 0;
    }

    target=checkouts.checkout_list;
    book_target=target->checkout_books.book_list;
    if (strcmp(name, book_target->name) == 0)// first node is delete node
    {
        checkouts.count--;
        free(book_target);
        target->checkout_books.book_list=NULL;
        return 1;
    }

    prev = book_target;
    book_target = book_target->next;

    while (target != NULL)
    {
        while (book_target != NULL)// circular search
        {
            if (strcmp(name, book_target->name) == 0)// return book find
            {
                checkouts.count--;
                prev->next=book_target->next;
                free(book_target);
                return 1;
            }
            prev=book_target;
            book_target=book_target->next;
        }
        target = target->next;
        book_target=target->checkout_books.book_list;
        prev=book_target;
    }

    return 0;
}

int SearchCheckoutBook(char *book_name)
{
    checkout_info* target;
    book_info* book_target;

    if(checkouts.checkout_list==NULL)
    {
        printf("checkout list is not exist.\n");
        return 0;
    }

    target=checkouts.checkout_list;
    book_target = checkouts.checkout_list->checkout_books.book_list;

    while (target != NULL)
    {
        while (book_target != NULL)// circular search
        {
            if (strcmp(book_name, book_target->name) == 0)
            {
                return 1;
            }
            book_target=book_target->next;
        }
        target = target->next;
    }
    printf("book is not checkout.\n");

    return 0;
}

int SearchCheckoutID(char *id)
{
    checkout_info* target;

    target=checkouts.checkout_list;

    while (target != NULL)
    {
        if(strcmp(id, target->student.id)==0)
        {
            return 1;
        }
        target = target->next;
    }
    printf("not checkout students.\n");
    return 0;
}

void DisplayCheckoutBook(book_info *book)
{
    DisplayBook(book);
}

void DisplayCheckoutList(void)
{
    checkout_info *checkout;
    book_info *book;

    if(checkouts.checkout_list==NULL)
    {
        printf("checkout list is empty!\n");
        return 0;
    }
    checkout=checkouts.checkout_list;
    book=checkout->checkout_books.book_list;

    while(checkout!=NULL)
    {
        printf("checkout student:\n");
        DisplayStudentInfo(checkout->student);

        while (book != NULL)
        {
            DisplayCheckoutBook(book);
            book = book->next;
        }
        checkout=checkout->next;
    }
}