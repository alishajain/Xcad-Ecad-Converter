#include "main_class.h"

int select::start_function()
{
	start_end_func("*", 20);
        cout << "Enter the file format you want to convert\n";
        cout << "1 - Convert XCAD format to ECAD\n";
        cout << "2 - Convert ECAD format to XCAD\n";
        cin >> ch;

        cout << "Enter the name of file you want to output\n";
        cin >> f_name;

        if (ch == 1)
        {
	    exp_f_name = f_name + ".ecad";
	}
        else if(ch == 2)
        {
	    exp_f_name = f_name + ".xcad";
	}

        ofstream f(exp_f_name.c_str(), ios::out);
	return ch;
}

void select::start_end_func(string symbol, int times)
{
        for(int n = 0; n < times; n++)
        {
            cout << symbol;
        }
        cout << endl;
}

int select::total_values(int no_of_values)
{
	no = no_of_values;
	return no;
}
void select::store_string_values(string s, int i, char c)
{
	if(c == 't')
	    type[i] = s;
	else if(c == 'n')
	    name[i] = s;
	else
	    col_mat[i] = s;
}

void select::store_values(float s, int i)
{
	values[i] = s;
}

//////////////////WRITE ECAD FILE/////////////////////////
void select::WriteEcad_type(string s[1024], int i)
{
        ifstream read("type.txt", ios::in);
        string input_str;

        while(!read.eof())
        {
            input_str = "0";
            read >> input_str;

            ofstream f(exp_f_name.c_str(), ios::app);
            if ( s[i].compare(input_str.c_str()) == 0)
            {
                string neglect = ":";
                read >> input_str;
                if(neglect.compare(input_str.c_str()) == 0)
                    read >> input_str;
                    f << input_str << "{" << "\n";
            }
        }
        read.close();

}

void select::WriteEcad_name(string s[1024], int i)
{
        ofstream f(exp_f_name.c_str(), ios::app);
        f << s[i] << endl;
}

void select::WriteEcad_material(string s[1024], int i)
{
        ifstream read("col_mat.txt", ios::in);
        string input_str1, input_str2, neglect;

        while(!read.eof())
        {
                read >> input_str1 >> neglect >> input_str2;
                ofstream f(exp_f_name.c_str(), ios::app);
                if ( s[i].compare(input_str2.c_str()) == 0)
                        {
                            f << input_str1 << "}\n\n"; break;
                        }
        }
        read.close();
}

void select::WriteEcad_values(float s)
{
        ofstream f(exp_f_name.c_str(), ios::app);
	f << s << endl;
}
//////////////////////////////WRITE XCAD FILE////////////////////
void select::WriteXcad_type(string s[1024], int i)
{
	ifstream read("type.txt", ios::in);
        string input_str1, input_str2, neglect;

        while(!read.eof())
        {
                read >> input_str1 >> neglect >> input_str2;
                ofstream f(exp_f_name.c_str(), ios::app);

                if ( s[i].compare(input_str2.c_str()) == 0)
                        {
                            f << input_str1 << "("; break;
                        }
        }
        read.close();
}

void select::WriteXcad_name(string s[1024], int i)
{
        ofstream f(exp_f_name.c_str(), ios::app);
        f << s[i] << ',';
}

void select::WriteXcad_color(string s[1024], int i)
{
	ifstream read("col_mat.txt", ios::in);
        string input_str1, neglect, input_str2;
        while(!read.eof())
        {
            read >> input_str1 >> neglect >> input_str2;
            ofstream f(exp_f_name.c_str(), ios::app);
            if ( s[i].compare(input_str1.c_str()) == 0)
            {
		    f << input_str2 << ")\n\n";;
	    }
        }
        read.close();
}

void select::WriteXcad_values(float s)
{
        ofstream f(exp_f_name.c_str(), ios::app);
        f << s << ',';
}

////////////////////////////////////////////////////////////////////

void select::Write_file()
{
	if(ch == 1)
	{
	    for(int j = 0; j < no; j++)
	    {
		WriteEcad_type(type, j);
		WriteEcad_name(name, j);
		if(type[j] == "Sphere")
		{
		    int x1, x2, y, z;
		    x1 = values[j] + (values[j+3]/2);
		    y = values[j+1];
		    z = values[j+2];
		    x2 = x1 - values[j+3];
		    WriteEcad_values(x1);
                    WriteEcad_values(y);
                    WriteEcad_values(z);

                    WriteEcad_values(x2);
                    WriteEcad_values(y);
                    WriteEcad_values(z);
		}
		else if(type[j] == "Cylinder")
		{
		    int c_x, c_y, c_z, dc_x, dc_y, dc_z, l, r;
		    c_x = (values[j] + values[j+3])/2;
		    c_y = (values[j+1] + values[j+4])/2;
		    c_z = (values[j+2] + values[j+5])/2;
		    
		    l = sqrt( (values[j]-values[j+3])*2 + (values[j+1]-values[j+4])*2 + (values[j+2]-values[j+5])*2 );
		    r = values[j+6]/2;

		    WriteEcad_values(c_x);
                    WriteEcad_values(c_y);
                    WriteEcad_values(c_z);

/*                    WriteEcad_values(dc_x);
                    WriteEcad_values(dc_y);
                    WriteEcad_values(dc_z);
*/
                    WriteEcad_values(l);
                    WriteEcad_values(r);
		}
		else if(type[j] == "Box")
		{
		    int c_x, c_y, c_z, l_x, l_y, l_z, dc_x, dc_y, dc_z;
		    l_x = values[j];
                    l_y = values[j+1];
                    l_z = values[j+2];

		    c_x = values[j+1] + values[j+4];
                    c_x = values[j+2] + values[j+5];
                    c_x = values[j+3] + values[j+6];

                    WriteEcad_values(c_x);
                    WriteEcad_values(c_y);
                    WriteEcad_values(c_z);

                    WriteEcad_values(l_x);
                    WriteEcad_values(l_y);
                    WriteEcad_values(l_z);
/*
                    WriteEcad_values(dc_x);
                    WriteEcad_values(dc_y);
                    WriteEcad_values(dc_z);
*/
		}

		WriteEcad_material(col_mat, j+1);
	    }
	}
	else
	{
	    for (int j = 0; j < no; j++)
	    {
		WriteXcad_type(type, j);
		WriteXcad_name(name, j);

		if (type[j] == "Ball")
		{
		    int c_x, c_y, c_z, d;
                    WriteEcad_values(c_x);
                    WriteEcad_values(c_y);
                    WriteEcad_values(c_z);

		    WriteEcad_values(d);
		}

		else if (type[j] == "Rod")
		{
		    int s_x, s_y, s_z, e_x, e_y, e_z, d;
		    d = 2*values[j+7];

                    WriteEcad_values(s_x);
                    WriteEcad_values(s_y);
                    WriteEcad_values(s_z);

                    WriteEcad_values(e_x);
                    WriteEcad_values(e_y);
                    WriteEcad_values(e_z);

		}

		else if(type[j] == "Cuboid")
		{
		    int l_x, l_y, l_z, s_x, s_y, s_z, r_x, r_y, r_z;

                    WriteEcad_values(l_x);
                    WriteEcad_values(l_y);
                    WriteEcad_values(l_z);

                    WriteEcad_values(s_x);
                    WriteEcad_values(s_y);
                    WriteEcad_values(s_z);

                    WriteEcad_values(r_x);
                    WriteEcad_values(r_y);
                    WriteEcad_values(r_z);

		}

		WriteXcad_color(col_mat, j+1);
	    }
	}
}

