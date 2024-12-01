#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

const int MAX_SIZE = 100;
int maze[MAX_SIZE][MAX_SIZE];
int N, count_route = 0;

const int PATHWAY = 0;  // 지나갈 수 있는 길
const int WALL = 1;     // 벽
const int PATH = 2;     // 방문한 길

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void read_maze() {
  ifstream infile("input2.txt");
  infile >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> maze[i][j];
    }
  }

  infile.close();
}

void findMazePath(int x, int y) {
  // 범위를 벗어나는 경우
  if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATHWAY) {
    return;
  }

  // 도착한 경우
  if (x == N - 1 && y == N - 1) {
    count_route++;
    return;
  }

  maze[x][y] = PATH;  // 현재 방문 위치

  for (int i = 0; i < 4; i++) {
    int nx = x + offset[i][0];
    int ny = y + offset[i][1];

    findMazePath(nx, ny);
  }

  // 경로 복원
  maze[x][y] = PATHWAY;
}

int main() {
  read_maze();
  findMazePath(0, 0);
  cout << count_route << endl;
  return 0;
}