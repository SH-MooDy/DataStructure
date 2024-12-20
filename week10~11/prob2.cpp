#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int MAZE[MAX_CAPACITY][MAX_CAPACITY];
int MIN_CURVE[MAX_CAPACITY][MAX_CAPACITY];  // 최소 꺽임 수를 저장하는 배열
int N;

struct Position {
  pair<int, int> pos;
  int dir;          // 이전 이동 방향을 저장
  int curve_count;  // 현재까지 꺽인 수를 저장
  Position(int x, int y, int dir, int curve_count)
      : pos(x, y), dir(dir), curve_count(curve_count) {}
};

void read_file() {
  ifstream infile("input2.txt");
  infile >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> MAZE[i][j];
      MIN_CURVE[i][j] = INT_MAX;  // 초기값은 최대값
    }
  }

  infile.close();
}

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};  // 상, 우, 하, 좌 방향

// 현재 위치에서 해당 방향으로 이동 가능한지 확인
bool movable(pair<int, int> pos, int dir) {
  int x = pos.first + offset[dir][0];
  int y = pos.second + offset[dir][1];
  return x >= 0 && x < N && y >= 0 && y < N && MAZE[x][y] == 0;
}

// 현재 위치에서 해당 방향으로 이동
pair<int, int> move_to(pair<int, int> pos, int dir) {
  return {pos.first + offset[dir][0], pos.second + offset[dir][1]};
}

int main() {
  read_file();
  queue<Position> que;
  Position start(0, 0, -1, 0);  // 첫 칸은 방향이 없으므로 -1로 초기화
  MIN_CURVE[0][0] = 0;
  que.push(start);

  int result = INT_MAX;  // 최종 최소 꺽임 수

  while (!que.empty()) {
    Position cur = que.front();
    que.pop();

    // 도착지 도착 시
    if (cur.pos.first == N - 1 && cur.pos.second == N - 1) {
      result = min(result, cur.curve_count);  // 최소 꺽임 수 갱신
      continue;
    }

    // 네 방향 탐색
    for (int dir = 0; dir < 4; dir++) {
      if (movable(cur.pos, dir)) {
        pair<int, int> p = move_to(cur.pos, dir);
        int new_cureve_count = cur.curve_count;

        // 이전 방향과 다른 경우 꺽인 횟수 증가
        if (cur.dir != -1 && cur.dir != dir) {
          new_cureve_count++;
        }

        // 더 적은 꺽은 수로 도달한 경우에만 큐에 푸쉬
        if (new_cureve_count < MIN_CURVE[p.first][p.second]) {
          MIN_CURVE[p.first][p.second] = new_cureve_count;
          que.push(Position(p.first, p.second, dir, new_cureve_count));
        }
      }
    }
  }

  if (result == INT_MAX) {
    cout << "No path exists." << endl;  // 경로가 없을 경우
  } else {
    cout << result << endl;  // 최소 꺽임 수 출력
  }

  return 0;
}
