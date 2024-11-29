#include <fstream>
#include <iostream>
using namespace std;

const int MAX = 16;

int board[MAX][MAX];
pair<int, int> start;
pair<int, int> dest;

void read_file() {
  ifstream infile("input8.txt");
  int N;
  infile >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> board[i][j];
    }
  }

  infile >> start.first;
  infile >> start.second;
  infile >> dest.first;
  infile >> dest.second;
}

bool isFindToken(int x, int y) {
  for (int dir = 0; i < 4; i++) {
  }
}

bool canMovePo() {}

int main() {
  read_file();

  if (canMovePo) {
    cout << "Yes" << Endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}