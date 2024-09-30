#include<iostream>
#define MAX 10000 // 배열의 최대 크기를 정의
using namespace std;

int main() {
    int arr[MAX]; // 크기가 MAX인 정수형 배열을 선언
    int n; // 사용자로부터 입력받을 수를 저장할 변수
    cin >> n; // 상한값을 입력받음

    // 2부터 n까지의 숫자로 배열을 초기화
    for (int i = 0; i < n - 1; i++) {
        arr[i] = i + 2;
    }

    int removed = 0; // 제거된 요소의 수를 추적하는 변수

    for (int i = 0; i < n; i++) {
        // 배열의 남은 요소들을 반복
        for (int j = i + 1; j < n - removed; j++) {

            // 만약 arr[j]가 arr[i]로 나누어 떨어진다면 소수가 아님
            if (arr[j] % arr[i] == 0) {
                removed++; // 제거된 요소 수를 증가

                // arr[j]를 제거하기 위해 요소들을 왼쪽으로 이동
                for (int k = j; k < n - removed; k++) {
                    arr[k] = arr[k + 1];
                }

                // 현재 위치에 있는 새로운 요소를 다시 확인하기 위해 j를 감소
                j--;
            }
        }
    }

    // 남아있는 요소들(소수들)을 출력
    for (int i = 0; i < n - removed; i++) {
        cout << arr[i] << endl;
    }

    return 0;
}

