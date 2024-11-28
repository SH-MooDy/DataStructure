#include <iostream>
#include <vector>
using namespace std;

bool isLuckyNum(int n) {
  vector<int> numbers;
  for (int i = 1; i <= 1000000; i++) {
    numbers.push_back(i);
  }

  int step = 2;
  while (step <= numbers.size()) {
    vector<int> filtered;
    for (int i = 0; i < numbers.size(); i++) {
      if ((i + 1) % step != 0) {
        filtered.push_back(numbers[i]);
      }
    }
    numbers = filtered;

    if (n < numbers.size() && numbers[n - 1] == n) {
      break;
    }

    step++;
  }

  // 행운수 여부 확인
  for (int num : numbers) {
    if (num == n) {
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  cin >> n;

  if (isLuckyNum(n)) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }

  return 0;
}
