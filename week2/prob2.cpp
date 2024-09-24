#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> v;
    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {
        v.push_back(i);
    }

    for (auto it1 = v.begin(); it1 != v.end(); it1++) {
        // 내부 반복자를 it1+1로 설정
        for(auto it2 = it1 + 1; it2 != v.end();) {
            // it2가 it1으로 나누어 떨어지면
            if((*it2) % (*it1) == 0) {
                // it2 요소 삭제 후, 반복자를 업데이트
                it2 = v.erase(it2);  // 삭제된 위치의 다음 요소를 가리키는 반복자를 반환
            } else {
                ++it2;  // 삭제되지 않았을 경우 반복자를 증가
            }
        }
    }

    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
