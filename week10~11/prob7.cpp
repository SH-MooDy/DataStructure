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
  infile.close();
}

bool isLuckyNum(int k, int step) {
  // step이 배열보다 크면 종료
  if (step > lucky_numbers.size()) {
    return true;
  }

  vector<int> remained_numbers;  // 제거되지 않은 숫자를 저장할 벡터
  for (int i = 0; i < lucky_numbers.size(); i++) {
    if ((i + 1) % step == 0) {
      if (lucky_numbers[i] == k) {
        return false;
      }
    } else {
      remained_numbers.push_back(lucky_numbers[i]);
    }
  }

  // 다음 단계로 이동
  lucky_numbers = remained_numbers;
  return isLuckyNum(k, step + 1);
}

int main() {
  read_file();
  int k;
  cin >> k;

  if (isLuckyNum(k, 2)) {  // step은 2부터 시작
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }

  return 0;
}
