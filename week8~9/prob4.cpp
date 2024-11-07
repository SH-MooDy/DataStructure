#include<iostream>
#include<stack>
#include<fstream>
using namespace std;

const int MAX_SIZE = 100;

const int BACKGROUND = 0; // 배경 픽셀
const int IMAGE = 1; // 이미지 픽셀
const int VISITED_IMAGE = 2; // 방문한 이미지 픽셀
const int BACKTRACKED_IMAGE = 3; // 방문헀다가 되돌아 나온 이미지 픽셀

int input_IMG[MAX_SIZE][MAX_SIZE];

struct Position {
    int x, y;
    Position() {}   
    Position(int x, int y): x(x), y(y) {}
};

void read_images(int size, ifstream &infile) {    
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            infile >> input_IMG[i][j];
        }
    }
}

int offset[4][2] = {{-1, 0}.
                    {0, 1},
                    {1, 0}.
                    {0, -`1}};

bool movable(Position pos, int dir, int n) {
    int x = pos.x + offset[dir][0];
    int y = pos.y + offset[dir][1];
    return x>=0 && x<n && y>=0 && input_IMG[x][y]==0;
}

Position move_to(Position pos, int dir) {
    return Position(pos.x + offset[dir][0], pos.y + offset[dir][1]);
}

int main() {
    pair<int, int> position = 0,0; // 현재 좌표를 나타내는 pair
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

/*
    대충 계획
    1. 배경부터 스캔
    2. 만약 이미지 픽셀(1)을 찾으면 근처에 연결된 이미지 픽셀들을 서칭
    3. 서칭하면서 
*/