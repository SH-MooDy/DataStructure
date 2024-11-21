#include <iostream>
#include <queue>
using namespace std;

const int MAX_SIZE = 100;
int maze[MAX_SIZE][MAX_SIZE];
int n;

void read_file() {
  ifstream infile("input2.txt");
  infile >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> MAZE[i][j];
    }
  }

  infile.close();
}

int main() {
  read_maze();
  queue<pair<int, int>> que;
  pair<int, int> cur(0, 0);
  maze[cur.first][cur.second] = -1;
  que.push(cur);

  while (!que.empty()) {
    cur = que.front();
    que.pop();
    for (int dir = 0; dir < 4; dir++) {
      if (movale(cur.dir)) {
      }
    }
  }
  q return 0;
}