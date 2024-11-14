#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int MAZE[MAX_CAPACITY][MAX_CAPACITY];
int MIN_CURVE[MAX_CAPACITY][MAX_CAPACITY];  // �ּ� ���� ���� �����ϴ� �迭
int N;

struct Position {
  pair<int, int> pos;
  int dir;          // ���� �̵� ������ ����
  int curve_count;  // ������� ���� ���� ����
  Position(int x, int y, int dir, int curve_count)
      : pos(x, y), dir(dir), curve_count(curve_count) {}
};

void read_file() {
  ifstream infile("input2.txt");
  infile >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> MAZE[i][j];
      MIN_CURVE[i][j] = INT_MAX;  // �ʱⰪ�� �ִ밪
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
  Position start(0, 0, -1, 0);  // ù ĭ�� ������ �����Ƿ� -1�� �ʱ�ȭ
  MIN_CURVE[0][0] = 0;
  que.push(start);

  int curve_count = 0;
  int min_curved = 0;

  while (!que.empty()) {
    Position cur = que.front();
    que.pop();

    // ������ ���� ��
    if (cur.pos.first == N - 1 && cur.pos.second == N - 1) {
      cout << cur.curve_count << endl;
      return 0;
    }

    for (int dir = 0; dir < 4; dir++) {
      if (movable(cur.pos, dir)) {
        pair<int, int> p = move_to(cur.pos, dir);
        int new_cureve_count = cur.curve_count;

        // ���� ����� �ٸ� ���
        if (cur.dir != -1 && cur.dir != dir) {
          new_cureve_count++;
        }

        // �� ���� ���� ���� ������ ��츸 ť�� Ǫ��
        if (new_cureve_count < MIN_CURVE[p.first][p.second]) {
          MIN_CURVE[p.first][p.second] = new_cureve_count;
          que.push(Position(p.first, p.second, dir, new_cureve_count));
        }
      }
    }
  }
  cout << "No path exists." << endl;
  return 0;
}