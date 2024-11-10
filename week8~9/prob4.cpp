#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

const int MAX_SIZE = 100;
const int BACKGROUND = 0;     // 배경 픽셀
const int IMAGE = 1;          // 이미지 픽셀
const int VISITED_IMAGE = 2;  // 방문한 이미지 픽셀

int input_IMG[MAX_SIZE][MAX_SIZE];
int n;

struct Position {
  int x, y;
  int dir;  // 이동할 방향을 저장하기 위한 변수
  Position(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};

int offset[8][2] = {
    {-1, 0},  {0, 1},  {1, 0},  {0, -1},  // 상, 우, 하, 좌
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}    // 대각선
};

bool movable(Position pos, int dir) {
  int x = pos.x + offset[dir][0];
  int y = pos.y + offset[dir][1];
  return x >= 0 && x < n && y >= 0 && y < n && input_IMG[x][y] == IMAGE;
}

Position move_to(Position pos, int dir) {
  return Position(pos.x + offset[dir][0], pos.y + offset[dir][1], 0);
}

void read_images(ifstream &infile) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      infile >> input_IMG[i][j];
    }
  }
}

int main() {
  ifstream infile("input.txt");
  int T;
  infile >> T;
  for (int i = 0; i < T; i++) {
    infile >> n;
    read_images(infile);

    // 이미지 탐색 루프
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (input_IMG[j][k] == IMAGE) {
          stack<Position> s;      // 위치를 저장할 스택
          Position cur(j, k, 0);  // 이미지 시작 위치
          int count_image = 1;  // 이미지 픽셀의 수를 저장하는 변수

          input_IMG[cur.x][cur.y] = VISITED_IMAGE;

          while (true) {
            bool forwarded = false;  // 움직였는지 여부를 나타내는 플래그

            // 현재 위치에서 8방향으로 탐색
            while (cur.dir < 8) {
              if (movable(cur, cur.dir)) {
                s.push(Position(
                    cur.x, cur.y,
                    cur.dir + 1));  // 현재 위치와 다음 시도할 방향을 저장
                cur = move_to(cur, cur.dir);              // 이동
                input_IMG[cur.x][cur.y] = VISITED_IMAGE;  // 방문 표시
                count_image++;  // 이미지 픽셀 증가
                cur.dir = 0;    // 새 위치에서 다시 0부터 시작
                forwarded = true;
                break;
              }
              cur.dir++;
            }

            if (!forwarded) {   // 더 이상 이동할 수 없는 경우
              if (s.empty()) {  // 되돌아 갈 수 없다면
                break;
              }
              cur = s.top();
              s.pop();  // 이전 위치로 돌아감
            }
          }
          cout << count_image << " ";
        }
      }
    }
    cout << endl;
  }

  infile.close();
  return 0;
}
