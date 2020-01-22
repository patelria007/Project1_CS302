/* Ria Patel & Skylar White
 * Project 1 - Lib_info
 * Description: 
 * This program reads in music information from a file and formats the names of
 * the artists along with their albums and the songs included. It also displays
 * the total time of each album and how many songs the artists have. 
 * ------------------------------------------------------------------------------
 * PLEASE NOTE: 
 * Some functions are very long, so we decided to condense them on multiple lines
 * for convenience purposes.
 * 
 */

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std; 

/* Provided by write up */
struct Song { 
	string title;
	string time;  //Changed to string, but it was an int in the writeup
	int track;
};

struct Album {
	map <int, Song*> songs;
	string name;
	int time;
	int nsongs;  
};

struct Artist {
	map <string, Album*> albums; 
	string name;
	int time;
	int nsongs;
};

/* List of Functions */
int time_conversion(const string time);	//Conversion from string to int
string int_to_string(const int time);	//Conversion from int to string
string Remove_Underscore(string name);
void Add_Artist(map <string, Artist*> &artists, string artist_name);
void Add_Album(map <string, Album*> &albums, map <string, Artist*> &artists,
	string album_name, string artist_name);
void Add_Songs(map <int, Song*> &songs, string title, string time, int track, 
	Album* cover, Artist* person);
void Self_Destruct(map <string, Artist*> artists); //Deletes all memory declared

int main(int argc, char **argv)
{
	stringstream ss; 
	ifstream fin; 
	string line, file, junk; 

	Song *a, aa; 
	Album *b, bb; 
	Artist *c, cc;

	/* All of the maps and their iterators */
	map<string, Artist*> artists;
	map<string, Album*> albums; 
	map<int, Song*> songs; 
	map <string, Artist*>::const_iterator arit;	//Pointer for artist struct
	map <string, Album*>::const_iterator ait;	//Pointer for album struct
	map <int, Song*>::const_iterator sit; 	//Pointer for song struct

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
		
		/* Parses each line of the file */
		ss.str(line); 
		ss >> a->title >> a->time >> c->name >> b->name >> junk >> a->track; 
		
		/* Removes the underscores in all of the strings */
		c->name = Remove_Underscore(c->name);
		b->name = Remove_Underscore(b->name);
		a->title = Remove_Underscore(a->title);


		Add_Artist(artists, c->name);
		
		/* Creates a pointer to the current artist */	
		arit = artists.find(c->name);
		Add_Album(arit->second->albums, artists, b->name, c->name);

		/* Creates a pointer to the current album */
		ait = arit->second->albums.find(b->name);
		Add_Songs(ait->second->songs, a->title, a->time, a->track, ait->second,
			 arit->second); 

		ss.clear();
	}	
		
	/* Adds all of the album total times under the correct artist */
	for (arit = artists.begin(); arit != artists.end(); arit++) {
		for (ait = arit->second->albums.begin(); ait != arit->second->albums.end();
			 ait++) arit->second->time += ait->second->time;
	}
	
	/* Prints all artists, albums, and songs to standard input */
	for (arit = artists.begin(); arit != artists.end(); arit++) 
	{
		cout << arit->first << ": "<< arit->second->nsongs << ", " << 
			int_to_string(arit->second->time) << '\n';
		for (ait = arit->second->albums.begin(); ait != arit->second->albums.end(); ait++)
		{
			cout << "        " << ait->first << ": " << ait->second->nsongs << ", " 
				 << int_to_string(ait->second->time) << endl;
			for (sit = ait->second->songs.begin(); sit != ait->second->songs.end(); sit++)
				cout << "                " << sit->first << ". " << sit->second->title 
					 << ": " << sit->second->time << endl; 
				
		}
	}

	/* Deletes all of the songs, albums, and artists to prevent memory leaks */
	Self_Destruct(artists);
	
	return 0; 
}//end main

int time_conversion(const string time)
{
	string num1, num2; 
	int min, sec, total_time;
	bool change = false;

	
	/* When it finds the colon, it ends adding to num1 string and starts num2 string */
	for (int i = 0; i < (int)time.size(); i++)
	{
		/* Found an int & no colons */
		if (time[i] >= 48 && time[i] <= 57 && change == false) 
		{
			num1 += time[i]; 
		} 
		/* Found an int & a colon */
		else if (time[i] >= 48 && time[i] <= 57 && change == true)
		{
			num2 += time[i]; 
		}
		else change = true;  // Boolean signals a switch to the num2 string
	}

	
	/* 
		Conversions - Used http://www.cplusplus.com/reference/string/stoi/ 
		to see syntax of stoi function 
	*/
	min = stoi(num1); 
	sec = stoi(num2);
	total_time = (min * 60) + sec; 

	return total_time; 
}//end time_conversion

string int_to_string(const int time)
{
	int min, sec; 
	string converted; 
	
	/* Converts the total seconds into minutes and seconds */
	min = time / 60; 
	sec = time % 60; 

	if (sec < 10) {
		/* Just adds a 0 in front of the single digit to fix formatting issues */
		converted = to_string(min) + ":0" + to_string(sec); 
	} else {
		/* 
			Used http://www.cplusplus.com/reference/string/to_string/ 
			to see syntax of to_string function */
		converted = to_string(min) + ":" + to_string(sec); 
	}

	return converted; 
}//end string int_to_string

string Remove_Underscore(string name)
{
	/* Finds the underscore and removes it */
	for(int i = 0; i < (int)name.size(); i++){
		if(name[i] == '_'){
			name[i] = ' ';
		}
	}
	return name; 
}//end Remove_Underscore

void Add_Artist(map <string, Artist*> &artists, string artist_name) 
{
	map <string, Artist*>::const_iterator ait = artists.find(artist_name); 

	/* Check if the artist is already there. If they are, then return */
	if (ait != artists.end()) return; 
	
	/* Creates the new artist by adding their name, total album times, and total songs they have */
	Artist* person; 	
	person = new Artist; 
	person->name = artist_name;
	person->time = 0; //Initialized to 0, but will be fixed in a later function
	person->nsongs = 0; //Same thing

	/* Inserts artist into the artist map */
	artists[artist_name] = person;
	
	return;
}//end Add_Artist

void Add_Album(map <string, Album*> &albums, map <string, Artist*> &artists, 
			   string album_name, string artist_name)
{
	map <string, Album*>::const_iterator ait = albums.find(album_name); 
	map <string, Artist*>::const_iterator arit = artists.find(artist_name);

	/* Check if the artist is already there. If they are, then return */
	if (ait != albums.end()) return; 

	/* 
		Creating new albums for an artist by adding the album name, the total
		 album song time, and the number of songs in it 
	*/
	Album* cover;
	cover = new Album; 
	cover->name = album_name;
	cover->time = 0; 
	cover->nsongs = 0;

	/* Inserts the album into the album map under the specific artist */
	artists[artist_name]->albums.insert(make_pair(album_name, cover)); 
	
	return;
}//end Add_Album

void Add_Songs(map <int, Song*> &songs, string title, string time,
			   int track, Album* cover, Artist* person)
{
	map <int, Song*>::const_iterator sit = songs.find(track);

	/* Check if the track number exists */
	if (sit != songs.end()) return; 
	 
	/* 
		Creates the new song by adding the title, song time, and the track 
		number in the album 
	*/ 
	Song* song;
	song = new Song; 
	song->title = title;
	song->track = track;
	song->time = time;

	/* 	
		Inserts the song into the song map under the correct album & add to the
	 	total number of songs in the album & artist 
	*/
	songs[track] = song; 
	cover->nsongs++;
	cover->time += time_conversion(time);
	
	person->nsongs++; 
}//end Add_Songs

void Self_Destruct(map <string, Artist*> artists)
{
	Song *song; 
	Album *album; 
	Artist *artist; 

	/* Map iterators */
	map <string, Artist*>::const_iterator arit;
	map <string, Album*>::const_iterator ait; 
	map <int, Song*>::const_iterator sit; 

	/* 
		Goes through all of the maps, starting with the songs map, to delete 
		each song, album, and artist. 
		Purpose: To prevent memory leaks
	*/
	for (arit = artists.begin(); arit != artists.end(); arit++) 
	{
		for (ait = arit->second->albums.begin(); ait != arit->second->albums.end(); ait++)
		{
			for (sit = ait->second->songs.begin(); sit != ait->second->songs.end(); sit++)
			{
				song = sit->second;
				delete song;
			}
			album = ait->second;
			delete album;
		}
		artist = arit->second;
		delete artist;
	}
}//end Self_Destruct