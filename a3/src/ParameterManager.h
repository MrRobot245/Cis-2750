/*
 * ------------------------------------------------------------------
 *  ParameterManager.h - Holds all the function definitions
 *
 *  CIS*2750 - Software Systems Development and Integration
 *  School of Computer Science
 *  University of Guelph
 *  Author: Nathan Reymer
 * ------------------------------------------------------------------
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//All Function definitions defined in the spec, and ones of my own creation
typedef enum { false, true } Boolean;
typedef enum { INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, STRING_TYPE, LIST_TYPE, NO_TYPE } param_t;
typedef struct ParameterList
{
    char * list;
    int ran;

} ParameterList;
typedef struct ParameterManager
{
        int iVal;
        float rVal;
        Boolean bVal;
        char sVal[1000];
        char pName[100];
        char lVal[1000];
        int hasSet;
        int req;
        int type;
        struct ParameterManager *next;
} ParameterManager;

union param_value
{
    int           int_val;
    double         real_val;
    Boolean       bool_val;   /* see additional types section below */
    char          *str_val;
    ParameterList *list_val;  /* see additional types section below */
};
ParameterManager * PM_create(int size);
int PM_destroy(ParameterManager *p);
char * PL_next(ParameterList *l);
int PM_parseFrom(ParameterManager *p, FILE *fp, char comment);
int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required);
int PM_hasValue(ParameterManager *p, char *pname);
union param_value PM_getValue(ParameterManager *p, char *pname);
char * PL_next(ParameterList *l);
void RemoveSpaces(char* source);
void tokenize(char * line, ParameterManager *p);
char * stripLine (char * line, char comment);
void concatPoint (char *original, char *add);
