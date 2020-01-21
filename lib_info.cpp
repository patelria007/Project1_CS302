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
	map <int, Song*> songs;
	string name;
	int time;
	int nsongs;  // optional variable but makes it easier
};

struct Artist {
	map <string, Album*> albums; 
	string name;
	int time;
	int nsongs;
};

int time_conversion(const string time);
string Remove_Underscore(string name);
string Add_Artist(map <string, Artist*> &artists, string artist_name, Artist* person);
string Add_Album(map <string, Album*> &albums, map <string, Artist*> &artists, string album_name, string artist_name, Artist* person, Album* cover);
void Add_Songs(map <int, Song*> &songs, string title, int time, int track, Song* song);


int main(int argc, char **argv)
{
	stringstream ss; 
	ifstream fin; 
<<<<<<< HEAD
	string line, file, junk; 
	Song *a, aa; 
	Album *b, bb; 
	Artist *c, cc;
	map<string, Artist*> artists;
	map<string, Album*> albums; 
	map<int, Song*> songs; 

	//Iterator?
	map <string, Artist*>::const_iterator arit;
	map <string, Album*>::const_iterator ait; 
	map <int, Song*>::const_iterator sit; 

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
		/* Making pointers to the structs declared */		
		a = &aa;
		b = &bb;
		c = &cc;
		
		ss.str(line); 
		ss >> a->title >> a->time >> c->name >> b->name >> junk >> a->track; 
	
		cout << Add_Artist(artists, c->name, c) << c->name << endl;
		
<<<<<<< HEAD
		arit = artists.find(c->name);

		cout << Add_Album(arit->second->albums, artists, b->name, c->name, c, b) << b->name << endl;

		ait = arit->second->albums.find(b->name);

		Add_Songs(ait->second->songs, a->title, time_conversion(a->time), a->track, a); 

		// Converts the time to an int  
		time_conversion(a.time); 

		ss.clear();
	}	
	
	for (arit = artists.begin(); arit != artists.end(); arit++) 
	{
		for (ait = arit->second->albums.begin(); ait != arit->second->albums.end(); ait++)
		{
			cout << "Album title: " << ait->first << endl;
			for (sit = ait->second->songs.begin(); sit != ait->second->songs.end(); sit++)
				cout << "\t" << sit->first << ". " << sit->second->title << ": " << sit->second->time << endl; 
		}
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
	//cout << "  total time = " << total_time << endl;

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
	/* Finds the underscore and removes it */
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
}//end Remove_Underscore

string Add_Artist(map <string, Artist*> &artists, string artist_name, Artist* person) 
{
	map <string, Artist*>::const_iterator ait = artists.find(artist_name); 

	/* Check if the artist is already there. If they are, then "Old Artist" */
	if (ait != artists.end()) return "Old Artist: "; 
	
	/* Creating the new artist by adding their name, total song time, and number of songs they have */	
	person = new Artist; 
	person->name = artist_name;
	person->time = 0; // will fix later
	person->nsongs = 0; //for right now, will fix later

	/* Inserts artist into the artist map */
	artists[artist_name] = person;
	
	return "New Artist: ";
}//end Add_Artist

string Add_Album(map <string, Album*> &albums, map <string, Artist*> &artists, string album_name, string artist_name, Artist* person, Album* cover) 
{
	map <string, Album*>::const_iterator ait = albums.find(album_name); 
	map <string, Artist*>::const_iterator arit = artists.find(artist_name);

	/* Check if the artist is already there. If they are, then "Old Artist" */
	if (ait != albums.end()) 
	{
		// do Add_Song function here
		return "Old Album: "; 
	}
	/* Creating new albums for an artist by adding the album name, the total album song time, and the number of songs in it */
	cover = new Album; 
	cover->name = album_name;
	cover->time = 0; // will fix later
	cover->nsongs = 0; //for right now, will fix later

	/* Inserts the album into the album map under the specific artist */
	artists[artist_name]->albums.insert(make_pair(album_name, cover)); 
	
	// Add_Song function here
	
	return "New Album: ";
}//end Add_Album

void Add_Songs(map <int, Song*> &songs, string title, int time, int track, Song* song)
{
	map <int, Song*>::const_iterator sit = songs.find(track);

	/* Check if the track number exists */
	if (sit != songs.end()) return; 
	 
	/* Creates the new song by adding the title, song time, and the track number in the album */ 
	song = new Song; 
	song->title = title;
	song->track = track;
	song->time = time;

	/* Inserts the song into the song map under the correct album */
	songs[track] = song; 
	
}