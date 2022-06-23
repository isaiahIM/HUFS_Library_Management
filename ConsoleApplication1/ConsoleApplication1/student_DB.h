#ifndef _STUDENT_DB__H
#define _STUDENT_DB__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 50

typedef struct StudentInfoStructure
{
    char name[STR_MAX];
    char id[STR_MAX];
    char pw[STR_MAX];
    struct StudentInfoStructure* next;
} student_info;

typedef struct StudentDBStructure
{
    int count;
    student_info* student_list;// total student list
} student_DB;

student_DB students;

void StudentDB_Init(void);
int Login(char* id, char* pw);
void CreateAccount(char* name, char* id, char* pw);
int DeleteAccount(char* id);
student_info SearchStudent(char* id);
void DisplayStudentInfo(student_info student);
void DisplayStudentList(void);

#endif