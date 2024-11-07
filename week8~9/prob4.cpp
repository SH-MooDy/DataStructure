#include<iostream>
#include<stack>
#include<fstream>
using namespace std;

const int MAX_SIZE = 100;

/*
const int PATH = 0; // 지나갈 수 있는 위치
const int WALL = 1; // 지나갈 수 없는 위치
const int VISITED = 2; // 이미 방문한 위치
const int BACKTRACKED = 3; // 방문했다가 되돌아 나온 위치
*/
const int BACKGROUND = 0; // 배경 픽셀
const int IMAGE = 1; // 이미지 픽셀
const int VISITED_BACK = 2; // 방문한 배경 픽셀
const int VISITED_IMAGE = 3; // 방문한 이미지 픽셀
const int BACKTRACKED_IMAGE; // 방문헀다가 되돌아 나온 이미지 픽셀

int input_IMG[MAX_SIZE][MAX_SIZE];

void read_images(int size, ifstream &infile) {    
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            infile >> input_IMG[i][j];
        }
    }
}

int main() {
    pair<int, int> position; // 좌표를 나타내는 pair
    ifstream infile("input.txt");
    int T, N;
    infile >> T;
    for(int i=0; i<T; i++) {
        infile >> N;
        read_images(N, infile);
        stack<pair<int, int>> s1; // 좌표를 저장하는 스택

        while(true) {

        }
    }

    infile.close();
    return 0;
}