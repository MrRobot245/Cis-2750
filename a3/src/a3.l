%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*    return(WORD );
[a-zA-Z][a-zA-Z0-9_]*    return(TITLE );
\                      return(QUOTE );
\{                      return(OBRACE );
\}                      return(EBRACE );
;                       return(SEMICOLON );
=                       return(EQUALS );
#                       return(COMMENT );
\n                      return(NLINE);
[ \t]+                  /* ignore whitespace */;
%%
