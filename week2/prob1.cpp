#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<string> strs;
    string word;

    while (1) {
        cin >> word;
        if (word == "exit") {
            break;
        }

        // 벡터를 정방향으로 탐색
        auto it = lower_bound(strs.begin(), strs.end(), word);

        // 중복된 단어가 있으면 삭제
        if (it != strs.end() && *it == word) {
            strs.erase(it);  // 단어 삭제
        } 
        else {
            // 중복이 없으면 해당 위치에 단어 삽입
            strs.insert(it, word);
        }

        // 벡터의 내용 출력
        for (const auto &s : strs) {
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}
