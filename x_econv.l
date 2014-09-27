%{
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#define YY_DECL extern "C" int yylex()

#include "x_econv.tab.h"

%}

digit	[0-9]+
float	{digit}*"."{digit}*
word	[a-zA-Z]+
start_x	[(]
end_x	[)]
start_e [{]
end_e	[}]
comma	[,]
wc	{word}{comma}
fc	{float}{comma}

e_format   {start_e}{word}{float}+{word}{end_e}
x_format   {start_x}{wc}{fc}+{word}{end_x}

%%
[ \t\n] ;

Sphere|Cylinder|Box|Ball|Rod|Cuboid	{ yylval.c = strdup(yytext); return entity_type; }

Red|Green|Black|Wood|Iron|Wax           { yylval.c = strdup(yytext); return col_mat; }

{word}					{ yylval.c = strdup(yytext); return entity_name; }

{digit}*{float}*			{ yylval.f = atof(yytext); return values; }

. ;
