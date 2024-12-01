#include <fstream>
#include <iostream>
using namespace std;

const int MAX = 16;

int board[MAX][MAX];
int N;
pair<int, int> start;
pair<int, int> dest;

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void read_file() {
  ifstream infile("input8.txt");
  infile >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> board[i][j];
    }
  }
  infile >> start.first >> start.second;
  infile >> dest.first >> dest.second;
}

bool canMovePo(int x, int y) {
  // 목적지 도착시 true 반환
  if (x == dest.first && y == dest.second) {
    return true;
  }

  // 이미 방문했거나 장기판 밖인 경우
  if (x < 0 || x >= N || y < 0 || y >= N || board[x][y] == 2) {
    return false;
  }

  int tmp = board[x][y];  // 원상태 저장
  board[x][y] = 2;        // 방문 표시

  // 상하좌우 탐색
  for (int dir = 0; dir < 4; dir++) {
    int nx = x + offset[dir][0];
    int ny = y + offset[dir][1];

    // 건너뛸 말 찾기
    while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
      if (board[nx][ny] == 1) {  // 건너뛸 말 발견
        nx += offset[dir][0];
        ny += offset[dir][1];

        // 건너뛴 위치가 이동 가능한 경우
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && board[nx][ny] == 0) {
          if (canMovePo(nx, ny)) {
            return true;
          }
        }
        break;  // 건너뛴 말 뒤는 더 이상 탐색X
      }
      nx += offset[dir][0];
      ny += offset[dir][1];
    }
  }

  board[x][y] = tmp;  // 원상복구
  return false;
}

int main() {
  read_file();

  if (canMovePo(start.first, start.second)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}
