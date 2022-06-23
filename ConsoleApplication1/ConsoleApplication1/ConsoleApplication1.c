/**
 * @file ConsoleApplication1.c
 * @author isaiah IM (isaiahim0214@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022 isaiah im all right reserved
 * 
 */

#include "checkout.h"
#include "library_DB.h"
#include "student_DB.h"
#include <stdio.h>

#define CREATE_ACCOUNT          1
#define ADD_BOOK                2
#define DELETE_BOOK             3
#define PRINT_BOOKLIST          4
#define CHECKOUT_BOOK           5
#define RETURN_BOOK             6
#define PRINT_CHECKOUT_LIST     7

int main(void)
{
    int menu;
    student_info student;
    book_info book;

    /**DB initialize */
    StudentDB_Init();
    CheckoutDB_Init();
    LibDB_Init();

    do
    {
        printf("\n==============\n");
        printf("menu:\n");
        printf("1: create account\n");
        printf("2: add book\n");
        printf("3: delete book\n");
        printf("4: print book list\n");
        printf("5: checkout book\n");
        printf("6: return book\n");
        printf("7: print checkout list\n");
        printf("0: quit\n");
        printf("menu> ");
        scanf("%d", &menu);
        rewind(stdin);
        printf("\n\n");
        
        switch(menu)
        {
            case CREATE_ACCOUNT:
            {
                printf("user name> ");
                gets(student.name);
                rewind(stdin);

                printf("user ID> ");
                gets(student.id);
                rewind(stdin);

                printf("user PW> ");
                gets(student.pw);
                rewind(stdin);

                CreateAccount(student.name, student.id, student.pw);
            }
            break;

            case ADD_BOOK:
            {
                printf("book name> ");
                gets(book.name);
                rewind(stdin);

                printf("book author> ");
                gets(book.author);
                rewind(stdin);

                printf("page> ");
                scanf("%d", &book.page);
                rewind(stdin);

                printf("price> ");
                scanf("%d", &book.price);
                rewind(stdin);

                AddBook(book.name, book.author, book.page, book.price);
            }
            break;

            case DELETE_BOOK:
            {
                printf("book name> ");
                gets(book.name);
                fflush(stdin);

                DeleteBook(book.name);
            }
            break;

            case PRINT_BOOKLIST:
            {
                DisplayBookList();
            }
            break;

            case CHECKOUT_BOOK:
            {
                printf("book name> ");
                gets(book.name);
                rewind(stdin);

                printf("user name> ");
                gets(student.name);
                rewind(stdin);

                printf("user ID> ");
                gets(student.id);
                rewind(stdin);

                printf("user PW> ");
                gets(student.pw);
                rewind(stdin);

                CheckoutBook(book.name, student);
            }
            break;

            case RETURN_BOOK:
            {
                printf("return book name> ");
                gets(book.name);
                rewind(stdin);

                ReturnBook(book.name);
            }

            break;

            case PRINT_CHECKOUT_LIST:
            {
                DisplayCheckoutList();
            }
            break;

            case 0:
            {
                printf("terminate program.\n");
            }
            break;
            
            default:
            {
                printf("input error!\n");
            }
        }

    } while (menu!=0);
    
    return 0;
}