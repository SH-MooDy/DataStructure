#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

const int MAX_SIZE = 100;
const int PATH = 0;        /* 지나갈 수 있는 위치 */
const int WALL = 1;        /* 지나갈 수 없는 위치 */
const int VISITED = 2;     /* 이미 방문한 위치 */
const int BACKTRACKED = 3; /* 방문했다가 되돌아 나온 위치 */

int maze[MAX_SIZE][MAX_SIZE];
int n; /* 미로의 크기 */

void read_maze() {
  ifstream mazefile("maze.txt");
  mazefile >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      mazefile >> maze[i][j];
    }
  }
  mazefile.close();
}

void print_maze() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << maze[i][j] << " ";
    cout << endl;
  }
}

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(pair<int, pair<int, int>> pos, int dir) {
  int x = pos.second.first + offset[dir][0];
  int y = pos.second.second + offset[dir][1];
  return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == PATH;
}

pair<int, pair<int, int>> move_to(pair<int, pair<int, int>> pos, int dir) {
  return {
      0,
      {pos.second.first + offset[dir][0], pos.second.second + offset[dir][1]}};
}

int main() {
  read_maze();
  stack<pair<int, pair<int, int>>> s; /* 이동할 방향과 좌표를 저장하는 스택 */
  pair<int, pair<int, int>> cur = {0, {0, 0}}; /* 시작 위치와 처음 방향 */

  while (true) {
    maze[cur.second.first][cur.second.second] =
        VISITED; /* 현재 위치를 방문했다고 표시 */

    if (cur.second.first == n - 1 &&
        cur.second.second == n - 1) { /* 출구에 도착 */
      cout << "Found the path." << endl;
      break;
    }

    bool forwarded = false;
    while (cur.first < 4) { /* 현재 위치에서 지정된 방향 이후 방향부터 탐색 */
      if (movable(cur, cur.first)) {
        s.push(
            {cur.first + 1,
             {cur.second.first, cur.second.second}}); /* 현재 위치와 다음 시도할
                                                         방향을 저장 */
        cur = move_to(cur, cur.first); /* 지정된 방향으로 한 칸 이동 */
        cur.first = 0; /* 새 위치에서 다시 0부터 시작 */
        forwarded = true;
        break;
      }
      cur.first++;
    }

    if (!forwarded) { /* 더 이상 이동할 수 없는 경우 */
      maze[cur.second.first][cur.second.second] = BACKTRACKED;
      if (s.empty()) { /* 되돌아갈 위치가 없다면 */
        cout << "No path exists." << endl;
        break;
      }
      cur = s.top();
      s.pop(); /* 이전 위치로 되돌아감 */
    }
  }
  print_maze();
  return 0;
}
