/* Ria Patel & Skylar White
 * Project 1 - Lib_info
 * Description: 
 * This program reads in music information from a file and formats the names of the artists
 * along with their albums and the songs included. It also displays the total time of each album 
 * and how many songs the artists have. 
 */


/*
	STEP ONE DONE!!!
	NOW ONTO STEP 2
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <deque>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std; 

struct Song { 
	string title;
	string time;  // was an int before. I changed it to string
	int track;
};

struct Album {
	map <int, Song > songs;
	string name;
	int time;
	int nsongs;  // optional variable but makes it easier
};

struct Artist {
	map <string, Album > albums;
	string name;
	int time;
	int nsongs;
};

int time_conversion(const string time);
string Remove_Underscore(string name);

int main(int argc, char **argv)
{
	stringstream ss; 
	ifstream fin; 
	string line, file, junk, trash = "H_III_I_"; 

	Song a; 
	Album b; 
	Artist c; 

	/* Check if there is a correct number of arguments */
	if (argc != 2) 
	{
		cerr << "Incorrect format\n";
		return -1;
	}

	/* Opens up the file specified and makes sure it can be opened */
	file = argv[1];
	fin.open(file.c_str()); 

	/* Checks to see if it can open the file specified */
	if (fin.fail()) 
	{
		cerr << "Cannot open file\n"; 
		return -1; 
	}

	/* Reads in everything from the file */
	while(getline(fin, line))
	{
		ss.str(line); 
		ss >> a.title >> a.time >> c.name >> b.name >> junk >> a.track; 

		//cout << "Title = " << a.title << "   Time = " << a.time << "   Artist = " << c.name <<  "   Album = " << b.name << "   Track # = " << a.track << "    junk = " << junk << endl; 
		
		// Converts the time to an int  
		time_conversion(a.time); 

		ss.clear();
	}
	
	return 0; 
}//end main

int time_conversion(const string time)
{
	string num1, num2; 
	int min, sec, total_time;
	bool change = false;

	for (int i = 0; i < (int)time.size(); i++)
	{
		/* Int & no colon */
		if (time[i] >= 48 && time[i] <= 57 && change == false) 
		{
			num1 += time[i]; 
		} 
		/* int & found colon */
		else if (time[i] >= 48 && time[i] <= 57 && change == true)
		{
			num2 += time[i]; 
		}
		/* found colon */
		else change = true;  
	}

	/* CONVERSIONS */
	min = stoi(num1); 
	sec = stoi(num2);
	total_time = (min * 60) + sec; 

	//TESTER STATEMENT TO SEE IF CONVERSION WORKED
	cout << "  total time = " << total_time << endl;

	min = 0; 
	sec = 0; 
	total_time = 0; 
	num1 = "";
	num2 = ""; 
	change = false; 

	return total_time; 
}//end time_conversion

string Remove_Underscore(string name)
{
	// FROM CS140-LAB7, CODE_PROCESSOR.CPP
	// 	map <string, Prize *>::const_iterator pit = Prizes.find(id); 

	/*
		STEP 3 & 4 COULD USE THIS, BUT THAT IS IF WE USE THE FIND FUNCTION

		if (uit	!= Names.end()) return false;
	*/


	// may screw up; to fix: change to const string &name
	for(int i = 0; i < (int)name.size(); i++){
		if(name[i] == '_'){
			name[i] = ' ';
		}
	}
	return name; 

}