#include "student_DB.h"


void StudentDB_Init(void)
{
    students.count = 0;
    students.student_list = NULL;
}

int Login(char* id, char* pw)
{
    student_info* target;

    target = students.student_list;

    while (target != NULL)// circular search
    {
        if ((strcmp(id, target->id) == 0) &&(strcmp(pw, target->pw) == 0))
        {
            printf("Log in success!\n");
            return 1;
        }
        target = target->next;
    }

    printf("student is not exist.\n");
    return 0;
}

void CreateAccount(char* name, char* id, char* pw)
{
    student_info* new_student = (student_info*)malloc(sizeof(student_info));
    if (new_student != NULL)
    {
        strcpy(new_student->name, name);
        strcpy(new_student->id, id);
        strcpy(new_student->pw, pw);

        if (students.student_list == NULL)// first insert
        {
            students.student_list = new_student;
            new_student->next = NULL;
        }
        else
        {
            new_student->next = students.student_list;
            students.student_list = new_student;
        }

        students.count++;
    }
}


student_info SearchStudent(char* id)
{
    student_info* target;
    student_info student;

    target = students.student_list;

    while (target != NULL)// circular search
    {
        if (strcmp(id, target->id) == 0)
        {
            strcpy(student.name, target->name);
            strcpy(student.id, target->id);
            strcpy(student.pw, target->pw);

            return student;
        }
        target = target->next;
    }
    printf("student is not exist.\n");
    return student;
}


int DeleteAccount(char* id)
{
    student_info* target, * prev;
    target = students.student_list;

    if (strcmp(id, target->id) == 0)// first node is delete node
    {
        students.count--;
        free(target);
        students.student_list = NULL;

        return 1;
    }
    prev = target;
    target = target->next;

    while (target != NULL)// circular search
    {
        if (strcmp(id, target->id) == 0)
        {
            students.count--;
            prev->next = target->next;
            free(target);
            return 1;
        }
        prev = target;
        target = target->next;
    }

    return 0;
}


void DisplayStudentInfo(student_info student)
{
    printf("=====student info=====\n");
    printf("name: %s\n", student.name);
    printf("ID: %s\n", student.id);
    printf("pw: %s \n", student.pw);
}


void DisplayStudentList(void)
{
    student_info* student;

    student = students.student_list;

    while (student != NULL)
    {
        DisplayStudentInfo(*student);
        student = student->next;
    }
}
