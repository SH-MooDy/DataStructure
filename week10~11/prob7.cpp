#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> lucky_numbers;

void read_file() {
  ifstream infile("lucky_numbers.txt");
  int num;
  while (infile >> num) {
    lucky_numbers.push_back(num);
  }
}

bool isLuckyNum(int k, int count) {
  for (int i = 0; i < lucky_numbers.size(); i++) {
    if ((i + 1) % count == 0) {
      if (lucky_numbers[i] == k) {
        return false;
      }

      lucky_numbers.erase(lucky_numbers.begin() + i);
    }
  }

  if (!isLuckyNum) {
    return false;
  }
  return true;
}

int main() {
  read_file();
  int k;
  cin >> k;

  if (isLuckyNum(k, 0)) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }
  return 0;
}