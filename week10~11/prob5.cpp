#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int MAZE[MAX_CAPACITY][MAX_CAPACITY];
int N;

struct Position {
  pair<int, int> pos;
  int dir;  // 이전 이동 방향을 저장
  Position(int x, int y, int dir) : pos(x, y), dir(dir) {}
};

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

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(pair<int, int> pos, int dir) {
  int x = pos.first + offset[dir][0];
  int y = pos.second + offset[dir][1];
  return x >= 0 && x < N && y >= 0 && y < N && MAZE[x][y] == 0;
}

pair<int, int> move_to(pair<int, int> pos, int dir) {
  return {pos.first + offset[dir][0], pos.second + offset[dir][1]};
}

int main() {
  read_file();
  queue<Position> que;
  Position start(0, 0, -1);  // 첫 칸은 방향이 없으므로 -1로 초기화
  que.push(start);

  while (!que.empty()) {
    Position cur = que.front();
    que.pop();

    // 도착지 도착 시
    if (cur.pos.first == N - 1 && cur.pos.second == N - 1) {
      cout << cur.curve_count << endl;
      return 0;
    }

    for (int dir = 0; dir < 4; dir++) {
      if (movable(cur.pos, dir)) {
        pair<int, int> p = move_to(cur.pos, dir);
      }
    }
  }
  cout << "No path exists." << endl;
  return 0;
}