#include <iostream>
using namespace std;

const int MAX = 1000;

int twoSum(int data[], int begin, int end, int K, int count) {
  if (begin >= end) {
    return 0;
  } else {
    int sum = data[begin] + data[end];
    if (sum == K) {
      return twoSum(data, begin + 1, end - 1, K, count + 1);
    } else if (sum < K) {
      return twoSum(data, begin + 1, end, K, count);
    } else {
      return twoSum(data, begin, end - 1, K, count);
    }
  }
}
int main() {
  int data[MAX];
  int N, K, count = 0;

  // 정수 입력 부분
  for (int i = 0; i < N; i++) {
    cin >> data[i];
  }
  cin >> K;

  count = twoSum(data, 0, N, K, count);
  cout << count << endl;
  return 0;
}
