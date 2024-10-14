#include<iostream>
#include<vector>

using namespace std;

int id_counter = 0;

struct song {
    int index;
    string title, album, my_url;
    Artist *artist;
    Song() {}
    Song(string ti, Artist *art, string alb, string mv): title(ti), artist(art), album
, my_url(mv) {
    
}};
int main() {

    return 0;
}