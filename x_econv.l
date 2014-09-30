%{
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define YY_DECL extern "C" int yylex()

#include "x_econv.tab.h"

%}

/* name definitions */
digit	[0-9]+
float	{digit}*"."{digit}*
word	[a-zA-Z]+

%%
[ \t\n] ;	/* Ignores white spaces and end line */

Sphere|Cylinder|Box|Ball|Rod|Cuboid	{ yylval.c = strdup(yytext); return entity_type; }

Red|Green|Black|Wood|Iron|Wax           { yylval.c = strdup(yytext); return col_mat; }

{word}					{ yylval.c = strdup(yytext); return entity_name; }

{digit}*{float}*			{ yylval.f = atof(yytext); return values; }

. ;
