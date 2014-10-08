#include "main_class.h"

/* Function to ask for the output files
*/
int select::start_function(int c, string f_name)
{
        ch = c;

	exp_f_name = f_name;
//Creates a new output file with user defined name
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

/* To get the highest index of the array
*/
int select::total_values(int no_of_values)
{
	no = no_of_values;
	return no;
}

/* Store all the string values in array
*/
void select::store_string_values(string s, int i, char c)
{
	if(c == 't')		//For the type of entity
	    type[i] = s;
	else if(c == 'n')	//For the name of the entity
	    name[i] = s;
	else			//For the color and material of the entity
	    col_mat[i] = s;
}


/* To store all numeric values.
*/
void select::store_values(float s, int i)
{
	values[i] = s;
}

/* Functions to write ECAD file
*/

/* Function to write the type of entity
*/
void select::WriteEcad_type(string s[1024], int i)
{
// Reads the text file in which the entity type of both the formats are stored
        ifstream read("type.txt", ios::in);
        string input_str;

// Tries to match the type in the file and finds the corresponding value in the file
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

/* Writes the name of the entity
*/
void select::WriteEcad_name(string s[1024], int i)
{
        ofstream f(exp_f_name.c_str(), ios::app);
	if (s[i] != "")
	 f << s[i] << endl;
}

/* Writes the material of entity
*/
void select::WriteEcad_material(string s[1024], int i)
{
// Reads the file in which the colors and corresponding materials are mentioned
        ifstream read("col_mat.txt", ios::in);
        string input_str1, input_str2, neglect;

// Compares the color and write its corresponding material 
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

/* Function to write all the numeric values
*/
void select::WriteEcad_values(float s)
{
        ofstream f(exp_f_name.c_str(), ios::app);
	if (s >=0 || s < 0)
	f << s << endl;
}

/* Functions to write XCAD file
*/

/* Function to write type of the entity
*/
void select::WriteXcad_type(string s[1024], int i)
{
// Reads the text file in which the entity type of both the formats are stored
	ifstream read("type.txt", ios::in);
        string input_str1, input_str2, neglect;

// Compares the color and write its corresponding material 
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

/* Function to write name of the entity
*/
void select::WriteXcad_name(string s[1024], int i)
{
        ofstream f(exp_f_name.c_str(), ios::app);
        if (s[i] != "")
	f << s[i] << ", ";
}

/* Function to write the color of the entity
*/
void select::WriteXcad_color(string s[1024], int i)
{
// Reads the file in which the colors and corresponding materials are mentioned
	ifstream read("col_mat.txt", ios::in);
        string input_str1, neglect, input_str2;

// Compares the color and write its corresponding material 
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

/* Function to write all the numeric values
*/
void select::WriteXcad_values(float s)
{
        ofstream f(exp_f_name.c_str(), ios::app);
        if(s >= 0 || s < 0)
	f << s << ", ";
}

/* Calculates all the parameters and call write functions
*/
void select::Write_file()
{
	if(ch == 1)
	{
	    for(int j = 0; j < no; j++)
	    {
		WriteEcad_type(type, j);	// Writes type of the entity
		WriteEcad_name(name, j);	// Writes name of the entity
		if(type[j] == "Sphere")
		{
		    float x1, x2, y, z;

		// Calculates the two diametrically opposite point
		    x1 = values[j] + (values[j+3]/2);
		    y = values[j+1];
		    z = values[j+2];
		    x2 = x1 - values[j+3];

		// Writes these coordinates in the file
		    WriteEcad_values(x1);
                    WriteEcad_values(y);
                    WriteEcad_values(z);

                    WriteEcad_values(x2);
                    WriteEcad_values(y);
                    WriteEcad_values(z);
		}
		else if(type[j] == "Cylinder")
		{
		    float c_x, c_y, c_z, dc_x, dc_y, dc_z, l, r, r_x, r_y, r_z, d;

		// Calculates centroid of cylinder
		    c_x = values[j] + (values[j+3])/2;
 		    c_y = values[j+1] + (values[j+4])/2;
		    c_z = values[j+2] + (values[j+5])/2;

		// Calculates length of cylinder
		    l = sqrt( pow((values[j]-values[j+3]),2) + pow((values[j+1]-values[j+4]),2) + pow((values[j+2]-values[j+5]),2) );

		// Calculate radius of cylinder
		    r = values[j+6]/2;

		// Calculates the direction ratios of axis of cylinder
		    r_x = values[j+3] - values[j];
		    r_y = values[j+4] - values[j+1];
		    r_z = values[j+5] - values[j+2];

		    d = sqrt( pow(r_x, 2) + pow(r_y, 2) + pow(r_z, 2) );

		// Calculates the direction cosines of axis of cylinder
		    dc_x = r_x/d;
		    dc_y = r_y/d;
		    dc_z = r_z/d;

		// Write coordinates of centroid
		    WriteEcad_values(c_x);
                    WriteEcad_values(c_y);
                    WriteEcad_values(c_z);

		// Write direction cosines of axis of cylinder
                    WriteEcad_values(dc_x);
                    WriteEcad_values(dc_y);
                    WriteEcad_values(dc_z);

		// Write length and radius of cylinder
                    WriteEcad_values(l);
                    WriteEcad_values(r);
		}
		else if(type[j] == "Box")
		{
		    float c_x, c_y, c_z, l_x, l_y, l_z, dc_x, dc_y, dc_z, r_x, r_y, r_z, d;

		// Calculate length of cuboid along coordinate axis
		    l_x = values[j];
                    l_y = values[j+1];
                    l_z = values[j+2];

		// Calculate centroid of cuboid
		    c_x = values[j+3] + (values[j])/2;
                    c_y = values[j+4] + (values[j+1])/2;
                    c_z = values[j+5] + (values[j+2])/2;

                    d = sqrt( pow(l_x, 2) + pow(l_y, 2) + pow(l_z, 2) );

		// Calculate direction cosines of longitudinal axis of cuboid 
                    dc_x = l_x/d;
                    dc_y = l_y/d;
                    dc_z = l_z/d;

		// Write coordinates of centroid
                    WriteEcad_values(c_x);
                    WriteEcad_values(c_y);
                    WriteEcad_values(c_z);

		// Write lengths along axis
                    WriteEcad_values(l_x);
                    WriteEcad_values(l_y);
                    WriteEcad_values(l_z);

		// Write direction cosines of longitudinal axis 
                    WriteEcad_values(dc_x);
                    WriteEcad_values(dc_y);
                    WriteEcad_values(dc_z);

		}

		WriteEcad_material(col_mat, j+1);	// Write material of entity
	    }
	}
	else
	{
	    for (int j = 0; j < no; j++)
	    {
		WriteXcad_type(type, j);	// Write type of entity
		WriteXcad_name(name, j);	// write name of entity

		if (type[j] == "Ball")
		{
		    float c_x, c_y, c_z, d;

		// Calculate center of sphere
		    c_x = (values[j] + values[j+3])/2;
		    c_y = (values[j+1] + values[j+4])/2;
		    c_z = (values[j+2] + values[j+5])/2;

		// Calculate diameter of sphere
                    d = sqrt( pow((values[j]-values[j+3]),2) + pow((values[j+1]-values[j+4]),2) + pow((values[j+2]-values[j+5]),2) );

		// Write the coordinates of center
                    WriteXcad_values(c_x);
                    WriteXcad_values(c_y);
                    WriteXcad_values(c_z);

		// Write diameter of sphere
		    WriteXcad_values(d);
		}

		else if (type[j] == "Rod")
		{
		    float s_x, s_y, s_z, e_x, e_y, e_z, d, k;

		// Calculate diameter of cylinder
		    d = 2*values[j+7];

		    k = sqrt( pow( (values[j+6])/2, 2) / ( pow( values[j+3], 2) + pow( values[j+4], 2) + pow( values[j+5], 2) ) );

		// Calculate start point of axis of cylinder
		    s_x = values[j] + (values[j+3]*k);
                    s_y = values[j+1] + (values[j+4]*k);
                    s_z = values[j+2] + (values[j+5]*k);

		// Calculate end point of axis of cylinder
                    e_x = values[j] - (values[j+3]*k);
                    e_y = values[j+1] - (values[j+4]*k);
                    e_z = values[j+2] - (values[j+5]*k);

		// Write start point of axis of cylinder
                    WriteXcad_values(s_x);
                    WriteXcad_values(s_y);
                    WriteXcad_values(s_z);

		// Write end point of axis of cylinder
                    WriteXcad_values(e_x);
                    WriteXcad_values(e_y);
                    WriteXcad_values(e_z);

		// Write diameter of cylinder
		    WriteXcad_values(d);
		}

		else if(type[j] == "Cuboid")
		{
		    float l_x, l_y, l_z, s_x, s_y, s_z, r_x, r_y, r_z;

		// Calculate lengths along axis
		    l_x = values[j+3];
                    l_y = values[j+4];
                    l_z = values[j+5];

		// Calculate start point of cuboid
		    s_x = values[j] - (l_x/2);
                    s_y = values[j] - (l_y/2);
                    s_z = values[j] - (l_z/2);

		// Calculate rotation about coordinate axis in degrees
		    r_x = (acos(values[j+6])*180*7)/22;
		    r_y = (acos(values[j+7])*180*7)/22;
		    r_z = (acos(values[j+8])*180*7)/22;

		// Write lengths along axis
                    WriteXcad_values(l_x);
                    WriteXcad_values(l_y);
                    WriteXcad_values(l_z);

		// Write start point of cuboid
                    WriteXcad_values(s_x);
                    WriteXcad_values(s_y);
                    WriteXcad_values(s_z);

		// Write rotation angles
                    WriteXcad_values(r_x);
                    WriteXcad_values(r_y);
                    WriteXcad_values(r_z);

		}

		WriteXcad_color(col_mat, j+1);	// Writes color of entity
	    }
	}
}

