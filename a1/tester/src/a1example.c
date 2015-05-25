/*
 * ------------------------------------------------------------------
 *  a2example.c - sample program demonstrating use of assignment 1
 *                ParameterManager library, reused code from
 * 				  a1example.c by David McCaughan
 *
 *  CIS*2750 - Software Systems Development and Integration - W13
 *  School of Computer Science
 *  University of Guelph
 *  Author: David McCaughan
 *  Edited: Jon Warren
 * ------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ParameterManager.h"


int main()
{
    ParameterManager *params;   /* parameter manager for student record */
    ParameterList* plist;

    if (!(params = PM_create(21)))
    {
        /* ERROR CREATING PARAMETER MANAGER */
        exit(0);
    }

    /*
     * register parameters of interest
     */

    PM_manage(params,"str1",STRING_TYPE,0);
    PM_manage(params,"str2",STRING_TYPE,1);
    PM_manage(params,"str3",STRING_TYPE,1);
    PM_manage(params,"str4",STRING_TYPE,0);
    PM_manage(params,"str5",STRING_TYPE,1);
    PM_manage(params,"str6",STRING_TYPE,1);
    PM_manage(params,"str7",STRING_TYPE,1);
    PM_manage(params,"str8",STRING_TYPE,0);
    PM_manage(params,"int1",INT_TYPE,1);
    PM_manage(params,"int2",INT_TYPE,0);
    PM_manage(params,"int3",INT_TYPE,1);
    PM_manage(params,"int4",INT_TYPE,0);
    PM_manage(params,"int5",INT_TYPE,0);
    PM_manage(params,"f1",REAL_TYPE,0);
    PM_manage(params,"f2",REAL_TYPE,0);
    PM_manage(params,"f3",REAL_TYPE,0);
    PM_manage(params,"b1",BOOLEAN_TYPE,1);
    PM_manage(params,"b2",BOOLEAN_TYPE,1);
    PM_manage(params,"b3",BOOLEAN_TYPE,0);
    PM_manage(params,"l1",LIST_TYPE,0);
    PM_manage(params,"l2",LIST_TYPE,1);
    PM_manage(params,"l3",LIST_TYPE,0);
    PM_manage(params,"l4",LIST_TYPE,1);

    if (!PM_parseFrom(params,stdin,'#'))
    {
        exit(0);
    }

/*  Warning, code is very sloppy and bulky beyond this point*/

    if (PM_hasValue(params,"str1"))
    {
		if (strcmp(PM_getValue(params,"str1").str_val,"String1") == 0)
		{
			printf("str1: Correct!\n");
		}
		else
		{
			printf("str1: Incorrect\n***Expected: String1***\n***Actually: %s***\n",PM_getValue(params,"str1").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str1: Incorrect\n***No value assigned to str1***\n");
		exit(0);
	}

	if (PM_hasValue(params,"str2"))
    {
		if (strcmp(PM_getValue(params,"str2").str_val,"String2") == 0)
		{
			printf("str2: Correct!\n");
		}
		else
		{
			printf("str2: Incorrect\n***Expected: String2***\n***Actually: %s***\n",PM_getValue(params,"str2").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str2: Incorrect\n***No value assigned to str2***\n");
		exit(0);
	}

	if (PM_hasValue(params,"str3"))
    {
		if (strcmp(PM_getValue(params,"str3").str_val,"String3") == 0)
		{
			printf("str3: Correct!\n");
		}
		else
		{
			printf("str3: Incorrect\n***Expected: String3***\n***Actually: %s***\n",PM_getValue(params,"str3").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str3: Incorrect\n***No value assigned to str3***\n");
		exit(0);
	}
	if (PM_hasValue(params,"str4"))
    {
		if (strcmp(PM_getValue(params,"str4").str_val,"String4") == 0)
		{
			printf("str4: Correct!\n");
		}
		else
		{
			printf("str4: Incorrect\n***Expected: String4***\n***Actually: %s***\n",PM_getValue(params,"str4").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str4: Incorrect\n***No value assigned to str4***\n");
		exit(0);
	}
	if (PM_hasValue(params,"str5"))
    {
		if (strcmp(PM_getValue(params,"str5").str_val,"String5") == 0)
		{
			printf("str5: Correct!\n");
		}
		else
		{
			printf("str5: Incorrect\n***Expected: String5***\n***Actually: %s***\n",PM_getValue(params,"str5").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str5: Incorrect\n***No value assigned to str5***\n");
		exit(0);
	}
	if (PM_hasValue(params,"str6"))
    {
		if (strcmp(PM_getValue(params,"str6").str_val,"String6") == 0)
		{
			printf("str6: Correct!\n");
		}
		else
		{
			printf("str6: Incorrect\n***Expected: String6***\n***Actually: %s***\n",PM_getValue(params,"str6").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str6: Incorrect\n***No value assigned to str6***\n");
		exit(0);
	}
	if (PM_hasValue(params,"str7"))
    {
		if (strcmp(PM_getValue(params,"str7").str_val,"String7") == 0)
		{
			printf("str7: Correct!\n");
		}
		else
		{
			printf("str7: Incorrect\n***Expected: String7***\n***Actually: %s***\n",PM_getValue(params,"str7").str_val);
			exit(0);
		}
	}
	else
	{
		printf("str7: Incorrect\n***No value assigned to str7***\n");
		exit(0);
	}

	if (PM_hasValue(params,"str8"))
    {
		printf("str8: Incorrect\n***A value was assigned to str8 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("str8: Correct!\n");
	}

	if (PM_hasValue(params,"int1"))
    {
		if (PM_getValue(params,"int1").int_val == 1)
		{
			printf("int1: Correct!\n");
		}
		else
		{
			printf("int1: Incorrect\n***Expected: 1***\n***Actually: %d***\n",PM_getValue(params,"int1").int_val);
			exit(0);
		}
	}
	else
	{
		printf("int1: Incorrect\n***No value assigned to int1***\n");
		exit(0);
	}
	if (PM_hasValue(params,"int2"))
    {
		if (PM_getValue(params,"int2").int_val == 2)
		{
			printf("int2: Correct!\n");
		}
		else
		{
			printf("int2: Incorrect\n***Expected: 2***\n***Actually: %d***\n",PM_getValue(params,"int2").int_val);
			exit(0);
		}
	}
	else
	{
		printf("int1: Incorrect\n***No value assigned to int1***\n");
		exit(0);
	}
	if (PM_hasValue(params,"int3"))
    {
		if (PM_getValue(params,"int3").int_val == 3)
		{
			printf("int3: Correct!\n");
		}
		else
		{
			printf("int3: Incorrect\n***Expected: 3***\n***Actually: %d***\n",PM_getValue(params,"int3").int_val);
			exit(0);
		}
	}
	else
	{
		printf("int3: Incorrect\n***No value assigned to int3***\n");
		exit(0);
	}
	if (PM_hasValue(params,"int4"))
    {
		printf("int4: Incorrect\n***A value was assigned to int4 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("int4: Correct!\n");
	}
	if (PM_hasValue(params,"int5"))
    {
		printf("int5: Incorrect\n***A value was assigned to int5 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("int5: Correct!\n");
	}

	if (PM_hasValue(params,"f1"))
    {
		if (PM_getValue(params,"f1").real_val == 3.75)
		{
			printf("f1: Correct!\n");
		}
		else
		{
			printf("f1: Incorrect\n***Expected: 3.540000***\n***Actually: %f***\n",PM_getValue(params,"f1").real_val);
			printf("NOTE: If the expected and actual values are the same and it still says incorrect, it's because your REAL_TYPE is of type float when it should be double\n");
			exit(0);
		}
	}
	else
	{
		printf("f1: Incorrect\n***No value assigned to f1***\n");
		exit(0);
	}

	if (PM_hasValue(params,"f2"))
    {
		if (PM_getValue(params,"f2").real_val == 0.25)
		{
			printf("f2: Correct!\n");
		}
		else
		{
			printf("f2: Incorrect\n***Expected: 0.25***\n***Actually: %f***\n",PM_getValue(params,"f2").real_val);
			exit(0);
		}
	}
	else
	{
		printf("f2: Incorrect\n***No value assigned to f2***\n");
		exit(0);
	}
	if (PM_hasValue(params,"f3"))
    {
		printf("f3: Incorrect\n***A value was assigned to f3 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("f3: Correct!\n");
	}


	if (PM_hasValue(params,"b1"))
    {
		if (PM_getValue(params,"b1").bool_val == 1)
		{
			printf("b1: Correct!\n");
		}
		else
		{
			printf("b1: Incorrect\n***Expected: 1***\n***Actually: %d***\n",PM_getValue(params,"b1").bool_val);
			exit(0);
		}
	}
	else
	{
		printf("b1: Incorrect\n***No value assigned to b1***\n");
		exit(0);
	}
	if (PM_hasValue(params,"b2"))
    {
		if (PM_getValue(params,"b2").bool_val == 0)
		{
			printf("b2: Correct!\n");
		}
		else
		{
			printf("b2: Incorrect\n***Expected: 0***\n***Actually: %d***\n",PM_getValue(params,"b2").bool_val);
			exit(0);
		}
	}
	else
	{
		printf("b2: Incorrect\n***No value assigned to b2***\n");
		exit(0);
	}

	if (PM_hasValue(params,"b3"))
    {
		printf("b3: Incorrect\n***A value was assigned to b3 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("b3: Correct!\n");
	}

	if (PM_hasValue(params,"l1"))
	{
		plist = PM_getValue(params,"l1").list_val;
		if ((strcmp(PL_next(plist),"item1") == 0) && (strcmp(PL_next(plist),"item2") == 0) && (strcmp(PL_next(plist),"item3") == 0) && (PL_next(plist) == NULL))
		{
			printf("l1: Correct!\n");
		}
		else
		{
			printf("l1: Incorrect\n***List values wrong or didn't end with NULL***\n");
		}
	}
	else
	{
		printf("l1: Incorrect\n***No value assigned to l1***\n");
		exit(0);
	}
	if (PM_hasValue(params,"l2"))
	{
		plist = PM_getValue(params,"l2").list_val;
		if ((strcmp(PL_next(plist),"item1") == 0) && (strcmp(PL_next(plist),"i t e m 2") == 0) && (strcmp(PL_next(plist),"item3") == 0) && (PL_next(plist) == NULL))
		{
			printf("l2: Correct!\n");
		}
		else
		{
			printf("l2: Incorrect\n***List values wrong or didn't end with NULL***\n");
		}
	}
	else
	{
		printf("l2: Incorrect\n***No value assigned to l2***\n");
		exit(0);
	}
	if (PM_hasValue(params,"l3"))
    {
		printf("l3: Incorrect\n***A value was assigned to l3 when it shouldn't have***\n");
		exit(0);
	}
	else
	{
		printf("l3: Correct!\n");
	}
	if (PM_hasValue(params,"l4"))
	{
		plist = PM_getValue(params,"l4").list_val;
		if (PL_next(plist) == NULL)
		{
			printf("l4: Correct!\n");
		}
		else
		{
			printf("l4: Incorrect\n***List should have value of NULL but it doesn't***\n");
		}
	}
	else
	{
		printf("l4: Incorrect\n***No value assigned to l4***\n");
		exit(0);
	}

    printf("All tests executed correctly, don't forget to run alongside Valgrind to test for memory leaks! Now freeing memory and exiting...\n");
    PM_destroy(params);

    return(1);

}
