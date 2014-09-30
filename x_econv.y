%{
#include "main_class.h" //class for writing files
#include <iostream>
#include <fstream>
using namespace std;

extern "C" int yylex ();
extern "C" int yyparse (void);
extern "C" FILE *yyin;

void yyerror(const char *s1);
#define YYDEBUG 1

select s1;
int i  = 0;

int in (int i)
{ 
        return i;
}

%}

%union{
	float f;
	char *c;
}

%token <c> entity_type entity_name col_mat
%token <f> values


%%

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

int main() 
{
	s1.start_function();
	string imp_f_name, f_name;
	cout << "Enter the name of file you want to input\n";
	cin >> f_name;

	if (s1.ch == 1)
	{	imp_f_name = f_name + ".xcad";	}
	else if (s1.ch == 2)
	{	imp_f_name = f_name + ".ecad";	}

	FILE *myfile = fopen(imp_f_name.c_str(), "r");

	if (!myfile) {
		cout << "I can't open file" << endl;
		return -1;
	}
	yyin = myfile;
	do{
//		yydebug = 1;
		yyparse();
	} while (!feof(yyin));

	s1.total_values(i);
	s1.Write_file();
        s1.start_end_func("*", 20);
}

void yyerror(const char *s1) {
cout << "Parser error! Message: " << s1 << endl;
	exit(-1);
}
