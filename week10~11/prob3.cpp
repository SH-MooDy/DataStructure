#include <iostream>
using namespace std;

const int MAX = 1000;
int data[MAX];

int twoSum(int begin, int end, int K) {
  if (begin >= end) {
    return 0;
  }
  int sum = data[begin] + data[end];
  if (sum == K) {
    return 1 + twoSum(begin + 1, end - 1, K);
  } else if (sum < K) {
    return twoSum(begin + 1, end, K);
  } else {
    return twoSum(begin, end - 1, K);
  }
}

int main() {
  int N, K;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> data[i];
  }
  cin >> K;

  int count = twoSum(0, N - 1, K);
  cout << count << endl;

  return 0;
}