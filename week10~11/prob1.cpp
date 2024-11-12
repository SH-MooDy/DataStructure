#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 100;
int GRID[MAX_CAPACITY][MAX_CAPACITY];
int N, k;

void read_file() {
  ifstream grid("input1.txt");
  gird >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      grid >> GRID[i][j];
    }
  }
  grid >> k;
}

int main() {
  read_file();
  queue<pair<int, int>> q1;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (GRID[i][j] == 0) {
      }
    }
  }

  return 0;
}