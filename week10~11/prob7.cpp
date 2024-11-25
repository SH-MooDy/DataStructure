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
  // 종료 조건: 제거 기준(step)이 배열 크기 이상이면 종료
  if (step > lucky_numbers.size()) {
    return true;
  }

  // 현재 단계에서 제거 작업 수행
  vector<int> filtered_numbers;
  for (int i = 0; i < lucky_numbers.size(); i++) {
    if ((i + 1) % step != 0) { // step 기준에 해당하지 않는 숫자만 남김
      filtered_numbers.push_back(lucky_numbers[i]);
    } else if (lucky_numbers[i] == k) {
      // k가 제거 대상이라면 행운의 숫자가 아님
      return false;
    }
  }

  // lucky_numbers 갱신
  lucky_numbers = filtered_numbers;

  // 다음 단계로 이동
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
