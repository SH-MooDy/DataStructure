#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int GRID[MAX_CAPACITY][MAX_CAPACITY];
int RESET_GRID[MAX_CAPACITY][MAX_CAPACITY];
int N, k;

void print_test() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << GRID[i][j] << " ";
    }
    cout << endl;
  }
}

void read_file() {
  ifstream grid("input1.txt");
  grid >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      grid >> GRID[i][j];
      RESET_GRID[i][j] = GRID[i][j];  // RESET_GRID 초기화
    }
  }
  grid >> k;
  grid.close();
}

void reset_GRID() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      GRID[i][j] = RESET_GRID[i][j];
    }
  }
}

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(pair<int, int> pos, int dir) {
  int x = pos.first + offset[dir][0];
  int y = pos.second + offset[dir][1];
  return x >= 0 && x < N && y >= 0 && y < N && GRID[x][y] == 0;
}

pair<int, int> move_to(pair<int, int> pos, int dir) {
  return {pos.first + offset[dir][0], pos.second + offset[dir][1]};
}

int main() {
  read_file();
  int max_space = 0;       // 최대 칸 수
  pair<int, int> max_pos;  // 최대 칸 수 일때 위치

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (GRID[i][j] == 0) {
        reset_GRID();  // 초기 상태로 복원
        queue<pair<int, int>> que;
        pair<int, int> cur(i, j);  // 현재 위치
        GRID[cur.first][cur.second] = -1;
        que.push(cur);

        int count_space = 1;  // 현재 위치 포함
        int year = 0;

        while (!que.empty() && year < k) {
          int level_size = que.size();
          for (int l = 0; l < level_size; l++) {
            cur = que.front();
            que.pop();
            for (int dir = 0; dir < 4; dir++) {
              if (movable(cur, dir)) {
                pair<int, int> p = move_to(cur, dir);
                GRID[p.first][p.second] = -1;
                que.push(p);
                count_space++;
              }
            }
          }
          year++;
        }

        if (max_space < count_space) {
          max_space = count_space;
          max_pos = {i, j};
        }

        if (i == 4 && j == 5) {
          cout << "4,5인 경우" << count_space << endl;
        }
        if (i == 4 && j == 6) {
          cout << "4,6인 경우" << count_space;
        }
      }
    }
  }

  cout << max_pos.first << " " << max_pos.second << endl;
  cout << max_space << endl;
  return 0;
}
