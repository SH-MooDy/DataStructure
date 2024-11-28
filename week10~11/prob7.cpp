#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXNUM = 1000000;

void filterNumbers(vector<int>& numbers, int step) {
  if (step > numbers.size()) {
    return;  // 더 이상 제거할 숫자가 없으면 종료
  }

  vector<int> filtered;
  for (int i = 0; i < numbers.size(); i++) {
    if ((i + 1) % step != 0) {
      filtered.push_back(numbers[i]);
    }
  }

  numbers = filtered;
  filterNumbers(numbers, step + 1);
}

int main() {
  int k;
  cin >> k;

  vector<int> numbers(MAXNUM);
  for (int i = 1; i <= MAXNUM; i++) {
    numbers[i - 1] = i;
  }

  filterNumbers(numbers, 2);  // 2단계부터 시작

  // k가 남아 있는지 확인
  if (find(numbers.begin(), numbers.end(), k) != numbers.end()) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }

  return 0;
}
