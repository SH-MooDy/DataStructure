#include <fstream>
#include <iostream>
using namespace std;

const int MAX = 16;

int board[MAX][MAX];

void read_file() {
  ifstream infile("input8.txt");
  int N;
  infile >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      infile >> board[i][j];
    }
  }
}
int main() {
  read_file();
  return 0;
}