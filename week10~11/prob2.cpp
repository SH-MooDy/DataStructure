#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int MAZE[MAX_CAPACITY][MAX_CAPACITY];
int n;

struct Position {
  pair<int, int>;
  int dir;
  Position(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};
void read_file() {
  ifstream infile("input2.txt");
  infile >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      infile >> MAZE[i][j];
    }
  }

  infile.close();
}

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(pair<int, int> pos, int dir) {
  int x = pos.first + offset[dir][0];
  int y = pos.second + offset[dir][1];
  return x >= 0 && x < n && y >= 0 && y < n && MAZE[x][y] == 0;
}

pair<int, int> move_to(pair<int, int> pos, int dir) {
  return {pos.first + offset[dir][0], pos.second + offset[dir][1]};
}

int main() {
  read_file();
  queue<Position> que;
  Position cur(0, 0, 0);
  MAZE[cur.first][cur.second] = -1;
  que.push(cur);

  int curve_count = 0;

  while (!que.empty()) {
    cur = que.front();
    que.pop();
    for (int dir = 0; dir < 4; dir++) {
      if (movable(cur, dir)) {
        pair<int, int> p = move_to(cur, dir);
        MAZE[p.first][p.second] = MAZE[cur.first][cur.second] - 1;
        if (p.first == n - 1 && p.second == n - 1) {
          cout << "Found the path." << endl;
          return 0;
        }
        que.push(p);
      }
    }
  }
  cout << "No path exists." << endl;
  return 0;
}