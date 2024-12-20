#include<iostream>
#include<vector>
#include<list>
#include<fstream>
#include<cassert>
#include<sstream>
#include<string>
using namespace std;

int id_counter = 0;  
struct Artist; 
struct Song {  
    int index;
    string title, album, mv_url;
    Artist *artist;
    Song() {}
    Song(string ti, Artist *art, string alb, string mv): title(ti), artist(art), album(alb), mv_url(mv) {
        index = id_counter++;  
    }
};

struct Artist {  
    string name;
    list<Song *> songs;
    Artist() {}
    Artist(string name): name(name) {}
};


list<Artist *> artist_directory[256];  

const int SONG_DIRECTORY_SIZE = 10;
list<Song *> song_directory[SONG_DIRECTORY_SIZE];

const string datafilename = "songs.csv";

string trim(string str) {
    int s = 0, t = str.length()-1;
    while(s<str.length() && isspace(str[s]))
        s++;
    while(t>=0 && isspace(str[t]))
        t--;

    if(s<=t)
        return str.substr(s,t-s+1);
    else    
        return "";
}

vector<string> split_line(string &line, char delimeter) {
    vector<string> tokens;
    stringstream sstream(line);
    string str;
    while(getline(sstream, str, delimeter))
        tokens.push_back(trim(str));
    return tokens;
}

Artist *find_artist(string name) {
    list<Artist *> artist_list = artist_directory[(unsigned char)name[0]];
    for (auto it = artist_list.begin(); it != artist_list.end(); it++) {
        if((*it)->name == name) {
            return *it;
        }
    }
    return nullptr;
}

vector<Artist *> find_artists_by_started_name(string name) {
    vector<Artist *> artists;
    list<Artist *> artist_list = artist_directory[(unsigned char)name[0]];
    for (auto it = artist_list.begin(); it != artist_list.end(); it++) {
        if((*it)->name.find(name) != string::npos) {
            artists.push_back(*it);
        }
    }
    return artists;
}

vector<Song *> find_songs(string song) {
    vector<Song *> songs;
    for(int i=0; i<SONG_DIRECTORY_SIZE; i++) {
        list<Song *> &song_list = song_directory[i];
        for(auto &s: song_list) {
            if(s->title.find(song) != string::npos) {
                songs.push_back(s);
            }
        }
    }
    return songs;
}

void print_artist(Artist *p) {
    cout << p->name << ":" << endl;
    for(auto s: p->songs) {
        cout << "    " << s->index << ":" << s->title << ", " << s->album << ", " << s->mv_url << endl;
    }
}

void print_found_songs(vector<Song *> songs) {
    for(auto s : songs) {
        cout << "    " << s->index << ":" << s->title << ", " << s->artist->name << ", " << s->album << ", " << s->mv_url << endl;
    }
}

void print_artist_directory() {
    for(int i=0; i<256; i++) {
        list<Artist *> &artist_list = artist_directory[i];
        for(auto ptr: artist_list) {
            print_artist(ptr);
        }
    }
}

Artist *add_artist(string name) {
    Artist *ptr_artist = new Artist(name);
    list<Artist *> &artist_list = artist_directory[(unsigned char)name[0]];
    artist_list.push_back(ptr_artist);
    return ptr_artist;
}

void add_song(string title, string artist, string album = "", string mv_url = "") {
    Artist *artist_ptr = find_artist(artist);
    if (artist_ptr == nullptr) {
        artist_ptr = add_artist(artist);
    }
    Song *song_ptr = new Song(title, artist_ptr, album, mv_url);
    artist_ptr->songs.push_back(song_ptr);
    list<Song *> &song_list = song_directory[song_ptr->index%SONG_DIRECTORY_SIZE];
    song_list.push_back(song_ptr);
}

void load_songs(string filename) {
    string line;
    ifstream songfile(filename);
    while(getline(songfile, line)) {
        vector<string> tokens = split_line(line, ',');
        assert(tokens.size()==4 || tokens.size()==3);  
        if(tokens.size()==4)
            add_song(tokens[0], tokens[1], tokens[2], tokens[3]);
        else
            add_song(tokens[0], tokens[1], tokens[2]);
    }
    songfile.close();
}

void print_song_directory() {
    for(int i=0; i<SONG_DIRECTORY_SIZE; i++) {
        list<Song *> &song_list = song_directory[i];
        for(auto s: song_list) {
            cout << "    " << s->index << ":" << s->title << ", " << s->artist->name << ", " << s->album << ", " << s->mv_url << endl;
        }
    }
}

void remove_song_by_index(int index) {
    int group_index = index % SONG_DIRECTORY_SIZE;
    list<Song *> &song_list = song_directory[group_index];

    for (auto it = song_list.begin(); it != song_list.end(); ) {
        if ((*it)->index == index) {
            cout << index << ", " << (*it)->title << ", " << (*it)->artist->name << " is deleted from the list." << endl;

            // 해당 노래를 아티스트의 노래 리스트에서도 삭제
            Artist *artist = (*it)->artist;
            artist->songs.remove(*it); 
            
            // 노래 삭제
            delete *it; 
            it = song_list.erase(it); 
            break; 
        } else {
            ++it; 
        }
    }
}

void remove_song_by_artist(string name) {
    vector<Artist *> artists = find_artists_by_started_name(name);

    for (auto &a : artists) {
        cout << "Want to remove \"" << a->name << "\"? (yes/no): ";
        string want_to_delete;
        cin >> want_to_delete;
        cin.ignore();

        if (want_to_delete == "yes" || want_to_delete == "y") {
            cout << "Artist \"" << a->name << "\" deleted." << endl;

            // 해당 아티스트의 노래들을 삭제
            for (auto it = a->songs.begin(); it != a->songs.end(); ) {
                Song *targeted_song = *it;

                // song_directory에서도 삭제
                int group_index = targeted_song->index % SONG_DIRECTORY_SIZE;
                list<Song *> &song_list = song_directory[group_index];

                // song_directory에서 노래 삭제
                song_list.remove(targeted_song);
                it = a->songs.erase(it);
                delete targeted_song;
            }

            // 아티스트 삭제
            list<Artist *> &artist_list = artist_directory[(unsigned char)a->name[0]];
            artist_list.remove(a); 
            delete a; 
        }
    }
}

void save_directory() {
    ofstream outfile(datafilename);
    for (auto &songs: song_directory) {
        for(auto &song: songs) {
            outfile << song->title << "," << song->artist->name << "," << song->album << "," << song->mv_url << endl;
        }
    }
    outfile.close();
}

int main() {
    load_songs(datafilename);

    string input, command, arguments1, arguments2;
    while(1) {
        cout << "$ ";
        getline(cin, input);
        stringstream ss(input);
        ss >> command >> arguments1 >> arguments2;
        //cout << command << " " <<  arguments1 << " " << arguments2 << endl;

        if (command == "exit") { break; }

        if(command == "list") {
            if(arguments1 == "-a") {
                print_artist_directory();
            }
            else {
                print_song_directory();
            }
        }
        else if(command == "add") {
            string title, artist, album = "", mv_url = "";
            cout << "Title: ";
            getline(cin, title);
            cout << "Artist: ";
            getline(cin, artist);
            cout << "Album: ";
            getline(cin, album);
            cout << "MV url: ";
            getline(cin, mv_url);
            add_song(title, artist, album, mv_url);
        }
        else if(command == "find") {
            if(arguments1 == "-a") {
                vector<Artist *> artists = find_artists_by_started_name(arguments2);
                if(!artists.empty()){
                    cout << "Found:" << endl;
                    for(auto a : artists) {
                        print_artist(a);
                    }
                }
                else {
                    cout << "Not found" << endl;
                }
            }
            else {
                vector<Song *> songs = find_songs(arguments1);
                if(!songs.empty()){
                    cout << "Found:" << endl;
                    print_found_songs(songs);
                }
                else {
                    cout << "Not found" << endl;
                }
            }
        }
        else if(command == "remove") {
            
            if(arguments1 == "-a") {
                remove_song_by_artist(arguments2);
            }
            else {
                remove_song_by_index(stoi(arguments1));
            }
        }
        else if(command == "save") {
            save_directory();
        }
    }
    return 0;
}