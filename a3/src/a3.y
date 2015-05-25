%{

#include <stdio.h>
#include <string.h>
char* title = NULL;
char* filename = "";
%}

%union
{
	char *sval;
}

%token <sval>WORD
%token QUOTE
%token OBRACE
%token EBRACE
%token SEMICOLON
%token EQUALS
%token COMMENT
%token NLINE

%token <sval> TITLE
%%
statement	: statement assignment
		| assignment
		;


assignment	: TITLE EQUALS QUOTE{
	if(title == NULL)
							{
							}


}

%%

extern FILE *yyin;
int yyerror(char *s)
{
	printf("ERRRRR\n");
	return -1;
}
int main(int argc, char** argv)
{
	FILE* in;
	FILE* out;
	char* prName;
	char* subDir;
	if(argc != 4)
	{
		fprintf(stderr, "Usage: file.config projectName subDir/\n");
		fprintf(stderr, "\n");
		return -1;
	}
	filename = argv[1];
	prName = argv[2];
	subDir = argv[3];

	in = fopen(filename, "r");
	if(in == NULL)
	{
		fprintf(stderr, "The file could not be opened for reading ");
		return -1;
	}
        yyparse();
}
