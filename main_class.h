#ifndef MAIN_CLASS_H
#define MAIN_CLASS_H

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

class select 
{
	public:
	string exp_f_name, f_name, type[1024], name[1024], col_mat[1024];
	float values[1024];
	int ch;
	int no;

	int start_function();
	void start_end_func(string symbol, int times);
	void store_string_values(string s, int i, char c );
	void store_values(float s, int i);
	int total_values(int i);
	void Write_file();

        void WriteEcad_type(string s[1024], int i);
	void WriteEcad_name(string s[1024], int i);
	void WriteEcad_material(string s[1024], int i);
        void WriteEcad_values( float s );

        void WriteXcad_type(string s[1024], int i);
        void WriteXcad_name(string s[1024], int i);
        void WriteXcad_color(string s[1024], int i);
        void WriteXcad_values( float s );

};

#endif
