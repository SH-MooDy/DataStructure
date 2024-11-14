#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>  // memset 사용
using namespace std;

const int MAX_CAPACITY = 100;
int GRID[MAX_CAPACITY][MAX_CAPACITY];
int RESET_GRID[MAX_CAPACITY][MAX_CAPACITY];
int N, k;

void read_file() {
  ifstream grid("input1.txt");
  grid >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      grid >> GRID[i][j];
    }
  }
  grid >> k;
  grid.close();
}

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_movable(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N && GRID[x][y] == 0;
}

int main() {
  read_file();
  int max_space = 0;       // 최대 칸 수
  pair<int, int> max_pos;  // 최대 칸 수 일때 위치

  // 모든 그리드의 위치에서 시작해본다
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (GRID[i][j] == 0) {
        queue<pair<int, int>> que;
        bool visited[MAX_CAPACITY][MAX_CAPACITY] = {false};  // 방문 체크
        que.push({i, j});
        visited[i][j] = true;

        int count_space = 1;  // 시작 위치 포함
        int year = 0;

        // BFS를 통해 확산 진행
        while (!que.empty() && year < k) {
          int level_size = que.size();
          cout << "Year: " << year + 1 << ", Level size: " << level_size << endl;

          for (int l = 0; l < level_size; l++) {
            pair<int, int> cur = que.front();
            que.pop();

            int cur_x = cur.first;
            int cur_y = cur.second;

            for (int dir = 0; dir < 4; dir++) {
              int new_x = cur_x + offset[dir][0];
              int new_y = cur_y + offset[dir][1];

              if (is_movable(new_x, new_y) && !visited[new_x][new_y]) {
                visited[new_x][new_y] = true;
                que.push({new_x, new_y});
                count_space++;
                cout << "Expanding to: (" << new_x << ", " << new_y << ")" << endl;
              }
            }
          }
          year++;
        }

        // 최대 확산 영역 갱신
        if (max_space < count_space) {
          max_space = count_space;
          max_pos = {i, j};
        }

        // 특정 위치에 대한 디버깅 출력
        if (i == 4 && j == 5) {
          cout << "Starting from (4,5), count_space: " << count_space << endl;
        }
        if (i == 4 && j == 6) {
          cout << "Starting from (4,6), count_space: " << count_space << endl;
        }
      }
    }
  }

  // 결과 출력
  cout << "최대 확산 위치: " << max_pos.first << " " << max_pos.second << endl;
  cout << "최대 확산 영역: " << max_space << endl;
  return 0;
}
