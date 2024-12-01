#include <iostream>
using namespace std;

const int MAX = 1000;

int floor(int arr[], int start_index, int K, int size) {
  // 해당 정수가 없을 경우
  if (start_index == 0 && K < arr[start_index]) {
    return -1;
  }

  if (arr[start_index] > K) {
    return arr[start_index - 1];
  }

  // 탐색이 배열끝까지 이루어졌을 경우
  if (start_index >= size - 1) {
    return arr[start_index];
  }

  return floor(arr, start_index + 1, K, size);
}

int ceiling(int arr[], int end_index, int K, int size) {
  if (end_index == size - 1 && K > arr[end_index]) {
    return -1;
  }

  if (arr[end_index] < K) {
    return arr[end_index + 1];
  }

  if (end_index <= 0) {
    return arr[end_index];
  }

  return ceiling(arr, end_index - 1, K, size);
}

int main() {
  int N, K;
  int arr[MAX];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  cin >> K;

  int size = sizeof(arr) / sizeof(arr[0]);

  cout << floor(arr, 0, K, N) << endl;
  cout << ceiling(arr, N - 1, K, N) << endl;

  return 0;
}
