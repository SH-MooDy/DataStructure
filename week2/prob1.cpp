#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<string> strs;
    string word;
    while (1) {
        cin >> word;
        if (word == "exit") { break; }

        // 벡터에 중복된 단어를 가리키는 이터레이터
        auto it = find(strs.begin(), strs.end(), word);

        // 중복이 있으면 중복 단어 제거, 없으면 벡터에 단어 추가 후 정렬
        if (it != strs.end()) {
            strs.erase(it);
        }
        else {
            strs.push_back(word);
            sort(strs.begin(), strs.end());
            
        }

        for (auto s : strs) {
            cout << s << " ";
        }
        cout << endl;
    }
    return 0;
}