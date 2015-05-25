/*
* ------------------------------------------------------------------
*  ParameterManager.c - Functions to parse a file and tokenzie values
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
#include <ctype.h>
#include "ParameterManager.h"
// Creates a new parameter manager object
// PRE: size is a positive integer (see note 1 below)
// POST: Returns a new parameter manager object initialized to be empty (i.e. managing no parameters) on success, NULL otherwise (memory allocation failure)
//
ParameterManager * PM_create(int size)
{
    ParameterManager *node = malloc(sizeof(struct ParameterManager));

    node->next=NULL;
    if(size >=2)
    {
        //Add to back
        for(int i=1; i< size;i++)
        {
            ParameterManager *nNode = malloc(sizeof(struct ParameterManager));
            nNode->next=NULL;
            while (node)
            {
                if(node->next == NULL)
                {
                    node->next = nNode;
                    break;
                }
                node = node->next;
            }

        }

    }
    //free(nNode);
    return node;
}

// Destroys a parameter manager object
// PRE: n/a
// POST: all memory associated with parameter manager p is freed; returns 1 on success, 0 otherwise
//
int PM_destroy(ParameterManager *p)
{
    void * PM;
    ParameterManager *current = p;
    while (current!=NULL)
    {
        PM = current;
        free(PM);
        current = current->next;
    }
    if(p==NULL)
    {
        return 0;
    }
    else{
        return 1;
    }
}

// Extract values for parameters from an input stream (see note 2 below)
// PRE: fp is a valid input stream ready for reading that contains the desired parameters
// POST: All required parameters, and those optional parameters present, are assigned values that are consumed from fp,
int PM_parseFrom(ParameterManager *p, FILE *fp, char comment)
{
    char * line=(char*)calloc(256, sizeof(char));
    char * line2=(char*)calloc(256, sizeof(char));
    char * extra=(char*)calloc(256, sizeof(char));
    char * extraCat=(char*)calloc(256, sizeof(char));
    char * concat = (char*)calloc(4096, sizeof(char));
    char * token;
    int rVal=0;
    char chars[2] = {comment , '\0'};
    char delimit[5] = "";
    strcpy(delimit,chars);
    int check1=0;
    int check2=0;
    int singleOrNot=0;
    //Read first line, throw out any gargage text
    while(fgets (line,256, fp))
    {
        singleOrNot=0;
        check1=0;
        check2=0;
        //Dont bother with empty lines or Comments
        if(line[0]==comment || line[0]=='\n')
        {
        }
        else
        {
            line=stripLine(line,comment);
            RemoveSpaces(line);
            //printf("Single: {%s}\n",line);
            // Check to see if the line has both a ; and =, if so, single line is valid
            for(int i=0;i<strlen(line);i++)
            {
                if(line[i]==';')
                {
                    check1++;

                }
                else if(line[i]=='=')
                {
                    check2++;
                }

            }
            if(check1==check2 && check1>=2)
            {
                //memset(extra, 0, 256);
                extra=line;
                while((token = strtok_r(extra, ";", &extra)))
                {
                    tokenize(token,p);
                }
                continue;
            }
            if(check1==1 && check2==1)
            {

                check1=0;
                check2=0;
                rVal=1;
                singleOrNot=1;

                tokenize(line,p);
                memset(line, 0, 256);
            }

            //If single line is not valid, read uo to 1000 lines, concatinate them, and check that concatinated
            //line for both ; and =
            else
            {
                concatPoint(concat,line);
                for(int t=0;t<1000;t++)
                {

                    check1=0;
                    check2=0;
                    fgets (line2,256, fp);
                    if(line2[0]==comment || line2[0]=='\n')
                    {
                    }
                    else
                    {
                        line2=stripLine(line2,comment);
                        concatPoint(concat,line2);
                        RemoveSpaces(concat);
                        // printf("Concat %s\n",concat);

                        for(int q=0;q<strlen(concat);q++)
                        {
                            if(concat[q]==';')
                            {
                                check1+=1;
                                //Fix for pName on same line
                                if(isalpha(concat[q+1]))
                                {
                                    fgets (extraCat,256, fp);
                                    if(extraCat[0]==comment || extraCat[0]=='\n')
                                    {
                                    }
                                    else
                                    {

                                        extra=stripLine(extraCat,comment);

                                        concatPoint(concat,extraCat);
                                        RemoveSpaces(concat);
                                        memset(extraCat, 0, 256);
                                        extraCat=strtok(concat,";");
                                        extraCat=strtok(NULL,";");
                                        tokenize(extraCat,p);
                                        break;
                                    }
                                }
                            }
                            else if(concat[q]=='=')
                            {
                                check2+=1;
                            }
                        }
                        if(check1==check2 && check1>=2)
                        {
                            //   memset(extra, 0, 256);
                            extra=concat;
                            while((token = strtok_r(extra, ";", &extra)))
                            {
                                tokenize(token,p);
                            }
                            continue;
                        }
                        if(check1>=2)
                        {
                            printf("More than one End line character\n");
                        }
                        if(check1 >=2 || check2 >=2)
                        {

                            printf("Parse Error -TYPE- Line not delimited correctly\n");
                            printf("Parse Error -INFO- Error line Contains: {%s}\n",concat);
                            exit(0);
                        }
                        else if(check1==1 && check2==1)
                        {
                            //    printf("ConCat: %s\n",concat);
                            check1=0;
                            rVal=1;
                            check2=0;
                            tokenize(concat,p);
                            memset(concat, 0, 4096);
                            memset(line2, 0, 256);
                            break;
                        }

                    }
                }
            }

        }

    }
    //Check to see if all parameters have been found andhave been set
    struct ParameterManager *PM=p;
    while (PM)
    {
        //    printf("Name: %s HasSet:%d Req:%d\n",PM->pName,PM->hasSet,PM->req);
        if(PM->hasSet == 0 && PM->req==1)
        {
            printf("Not all pararmaters found! \n");
            rVal=0;
            break;
        }
        PM = PM->next;
    }
    //free (line);
    //free (line2);
    //free (concat);
    //Return 0, or 1
    return (rVal);
}


// Register parameter for management
// PRE: pname does not duplicate the name of a parameter already managed
// POST: Parameter named pname of type ptype (see note 3 below) is registered with p as a parameter;
int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required)
{
    //Check to see if pname exists and hasSet is set
    int exists=0;
    int rVal=1;
    struct ParameterManager *head=p;
    struct ParameterManager *new = malloc(sizeof(struct ParameterManager));
    //Duplicate check
    while(head!=NULL)
    {
        if((strcmp(pname,head->pName) == 0))
        {
            printf("Name already Exists!\n");
            exists=1;
            rVal=0;
            free(new);
            break;
        }
        head=head->next;
    }
    head=p;
    //Case for new parameter
    if(exists==0)
    {
        new->req=required;
        new->type=ptype+1;
        new->next=NULL;
        strcpy(new->pName,pname);
        while (head)
        {
            if(head->next == NULL)
            {
                head->next = new;
                break;
            }
            head = head->next;
        }
    }

    return (rVal);
}
//Pre: A Dirty string
//Post:A Clean string
//Take away any comments
char * stripLine (char *line, char comment)
{
    char chars[2] = {comment , '\0'};
    char delimit[5] = "";
    strcpy(delimit,chars);
    line=strtok(line, "\n");

    for(int i=0;i<strlen(line);i++)
    {
        if(line[i]==comment)
        {
            line = strtok (line, delimit);
            break;
        }
    }
    //printf("line %s\n",line);
    return line;
}
//Pre: A clean string to Tokenize
//Post: Matching variable for pName
//Tokenize string and pase it into the corect variable
void tokenize(char * line, ParameterManager *p)
{
    //Get the value before =, search it up, then set the applicable value
    //based on what type it should be
    //printf("Tokenize Got: %s\n",line);
    ParameterManager *PM=p;
    char * pre;
    char * post;
    //This is the single line case
    pre = strtok(line, "=");
    post = strtok(NULL, "=;");
    //    printf("Pre: %s Post:%s\n",pre,post);
    while(PM!=NULL)
    { //Check the name, then set the value
        if((strcmp(pre,PM->pName) == 0))
        {
            PM->hasSet=1;
            if(PM->type==1)
            {
                PM->iVal=atoi(post);
            }
            if(PM->type==2)
            {
                PM->rVal=atof(post);
            }

            //Specical case for converting true/false to 1/0
            if(PM->type==3)
            {
                if(strcmp("true",post)==0)
                {
                    PM->bVal=1;
                }
                else
                {
                    PM->bVal=0;
                }
            }
            if(PM->type==4)
            {
                strcpy(PM->sVal,post);
            }
            if(PM->type==5)
            {
                strcpy(PM->lVal,post);
            }
            break;
        }
        PM = PM->next;
    }
}
// Test if a parameter has been assigned a value
// PRE: pname is currently managed by p
// POST: Returns 1 if pname has been assigned a value, 0 otherwise (no value, unknown parameter)
//
int PM_hasValue(ParameterManager *p, char *pname)
{
    //Check to see if pname exists and hasSet is set
    struct ParameterManager *PM=NULL;
    PM = p;
    int rVal=0;
    char * pName=PM->pName;
    //printf("PNAME: %s\n",pName);
    while(PM!=NULL)
    {
        char * pName=PM->pName;
        rVal=0;
        if((strcmp(pname,pName) == 0))
        {
            if(PM->hasSet==1)
            {
                rVal=1;
            }
            break;
        }
        PM = PM->next;
    }
    return (rVal);
}
//Pre: Line with spaces
//Post: Line without spaces
void RemoveSpaces(char* source)
{
    //Go threw line and take out any spaces, special case for ""
    char* i = source;
    char* j = source;
    int string=0;
    while(*j != 0)
    {
        *i = *j++;
        //Dont mess with quotes
        if(*i=='"')
        {
            string++;
        }
        if(*i != ' ' || string%2!=0)
        {
            i++;
        }
    }
    *i = '\0';
}

void concatPoint (char *original, char *add)
{
    while(*original)
    original++;

    while(*add)
    {
        *original = *add;
        add++;
        original++;
    }
    *original = '\0';
}
// Obtain the value assigned to pname
// PRE: pname is currently managed by p and has been assigned a value
// POST: Returns the value (see note 4 below) assigned to pname; result is undefined if pname has not been assigned a value or is unknown
//
union param_value PM_getValue(ParameterManager *p, char *pname)
{
    //Decalare everything it can return
    ParameterManager *PM=p;
    char * concat;
    char * token;
    union param_value un;
    int int_val;
    float real_val;
    Boolean bool_val;   /* see additional types section below */
    char *str_val;
    int found=0;
    ParameterList *list_val=malloc(sizeof(struct ParameterList));
    while(PM!=NULL)
    {
        char * pName=PM->pName;
        //Check list for required name, based on type return that value
        if((strcmp(pname,pName) == 0))
        {
            found=1;
            //printf("Getting TYPE: %d\n",PM->type);

            if(PM->type==1)
            {
                un.int_val=PM->iVal;
            }
            else if(PM->type==2)
            {
                un.real_val=PM->rVal;
            }
            else if(PM->type==3)
            {
                un.bool_val=PM->bVal;
            }
            else if(PM->type==4)
            {
                concat=PM->sVal;
                token=strtok(concat,"\"");
                un.str_val=token;
            }
            else if(PM->type==5)
            {
                concat=PM->lVal;
                concat=strtok(concat,"{}");
                //printf("%s\n",concat);
                list_val->list=concat;
                list_val->ran=0;
                un.list_val=list_val;
            }
            break;
        }
        PM = PM->next;
    }
    if(found==0)
    {
        printf("ERROR, Paramater {%s} not found!\n",pname);
        printf("Most likely called before PM_Manage\n");
        exit(0);
    }
    return (un);
}
// Obtain the next item in a parameter list
// PRE: n/a
// POST: Returns the next item in parameter list l, NULL if there are no items remaining in the list (see note below)
char * PL_next(ParameterList *l)
{

    char * token=l->list;
    //Keep track of how many times it has run
    //Then tokenize NULL that many times
    if(l->ran==0)
    {
        token = strtok(token, ",\"");
        l->ran=1;
    }
    else
    {
        for(int i=0;i<l->ran;i++)
        token = strtok(NULL, ",\"");
    }
    return (token);


}
