#include <iostream>
using namespace std;

const int MAX = 1000;

int floor(int arr[], int start_index, int K) {
  // 해당 정수가 없을 경우
  if (start_index == 0 && K < arr[start_index]) {
    return -1;
  }

  if (arr[start_index] > K) {
    return arr[start_index - 1];
  }

  floor(arr, start_index + 1, K);
}

int ceiling(int arr[], int end_index, int K) {
  
}

int main() {
  int N, K;
  int arr[MAX];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  cin >> K;

  cout << floor(arr, 0, K) << endl;
  // cout << ceiling(arr, N - 1, K) << endl;

  return 0;
}