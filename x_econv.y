%{
#include "main_class.h" // class for writing files
#include <iostream>
#include <fstream>
using namespace std;

extern "C" int yylex ();	// Function for lexical analysis
extern "C" int yyparse (void);	// Function for parsing
extern "C" FILE *yyin;		// Pointer for input file

void yyerror(const char *s1);	// Error handling function
#define YYDEBUG 1		// Bison debugger initialisation

select s1;			// Object of class
int i  = 0;			// Index of array

int in (int i)			// Function to return index
{ 
        return i;
}

%}

/*
%union is used to declare the types for various tokens used. 
It is particularly used when we need to used more than one type
*/
%union{
	float f;
	char *c;
}

/* Token declaration with appropriate type
*/
%token <c> entity_type entity_name col_mat
%token <f> values

%%

/* Grammer rules
*/
converter:
	converter entity_type { s1.store_string_values($2, i, 't'); }
        | converter entity_name { s1.store_string_values($2, i, 'n'); }
        | converter col_mat { s1.store_string_values($2, i, 'c'); }
        | converter values { s1.store_values($2, i); in(i); i++; }
        | entity_type { s1.store_string_values($1, i, 't'); }
	| entity_name { s1.store_string_values($1, i, 'n'); }
	| col_mat { s1.store_string_values($1, i, 'c'); }
	| values { s1.store_values($1, i); in(i); i++; }

%%

int main(int argc, char **argv)	// Definition of main function
{
	int c;
	string arg, out_file;
	if(argc > 1)
	{
            if(!(yyin = fopen(argv[2], "r"))) /*open the first argument file and put it in yyin FILE variable */
	    {
                perror(argv[1]);
                return (1);
            }

	    arg = argv [1];
	    if( arg.compare("ecad") == 0 )
		c = 1;
            else if( arg.compare("xcad") == 0 )
		c = 2;

	    out_file = argv[3];
	}
	
	s1.start_function(c, out_file);

	while(!feof(yyin)) /*until input file doesn't end */
	{
//          yydebug = 1;
            yyparse(); /*keep on calling above grammar rules */
	}
	
	s1.total_values(i);
	s1.Write_file();
        s1.start_end_func("*", 20);
}

void yyerror(const char *s1)	// Definition of function handling error
{
	cout << "Parser error! Message: " << s1 << endl;
	exit(-1);
}
