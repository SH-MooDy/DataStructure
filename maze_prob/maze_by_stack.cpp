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

struct Position {
    int x, y;
    int dir;  // 이동할 방향을 저장하기 위한 변수
    Position(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(Position pos, int dir) {
    int x = pos.x + offset[dir][0];
    int y = pos.y + offset[dir][1];
    return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == PATH;
}

Position move_to(Position pos, int dir) {
    return Position(pos.x + offset[dir][0], pos.y + offset[dir][1], 0);
}

int main() {
    read_maze();
    stack<Position> s;     /* 이동할 방향을 저장하는 스택 */
    Position cur(0, 0, 0); /* 시작 위치와 처음 방향 */

    while (true) {
        maze[cur.x][cur.y] = VISITED; /* 현재 위치를 방문했다고 표시 */

        if (cur.x == n - 1 && cur.y == n - 1) { /* 출구에 도착 */
            cout << "Found the path." << endl;
            break;
        }

        bool forwarded = false;
        while (cur.dir < 4) { /* 현재 위치에서 지정된 방향 이후 방향부터 탐색 */
            if (movable(cur, cur.dir)) {
                s.push(Position(
                    cur.x, cur.y,
                    cur.dir + 1)); /* 현재 위치와 다음 시도할 방향을 저장 */
                cur = move_to(cur, cur.dir); /* 지정된 방향으로 한 칸 이동 */
                cur.dir = 0; /* 새 위치에서 다시 0부터 시작 */
                forwarded = true;
                break;
            }
            cur.dir++;
        }

        if (!forwarded) { /* 더 이상 이동할 수 없는 경우 */
            maze[cur.x][cur.y] = BACKTRACKED;
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
