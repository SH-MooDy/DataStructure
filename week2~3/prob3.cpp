#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

// 이진 탐색 함수
int binarySearch(const vector<pair<string, string>>& dictionary, const string& target) {
    int low = 0, high = dictionary.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;  // 중간값 계산
        
        if (dictionary[mid].first == target) {
            return mid;  // 단어를 찾으면 그 위치를 반환
        } else if (dictionary[mid].first < target) {
            low = mid + 1;  // 오른쪽 절반 탐색
        } else {
            high = mid - 1;  // 왼쪽 절반 탐색
        }
    }
    return -1; // 찾지 못하면 -1 반환
}

int main(){
    vector<pair<string,string>> dict;
    ifstream infile("shuffled_dict.txt");
    string line;
    while(getline(infile, line)){
        string word, description;
        stringstream ss(line);
        getline(ss, word, '\t');
        getline(ss, description);
        dict.push_back({word, description});
    }

    // 정렬
    sort(dict.begin(), dict.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
        return a.first < b.first;  // 단어를 기준으로 정렬
    });

    string searchWord;
    cin >> searchWord;
    
    int index = binarySearch(dict, searchWord);

    if(index != -1){
        // 단어와 설명 출력
        cout << dict[index].first << ": " << dict[index].second << endl;

        // 설명에 등장하는 단어들 중에서 길이가 3 이상인 단어 다시 검색
        stringstream ss(dict[index].second);
        string token;
        vector<string> words; // 중복 방지를 위해 출력된 단어들을 저장하는 벡터

        while (ss >> token){
            if(token.length() >= 3){
                int foundIndex = binarySearch(dict, token);
                
                if(foundIndex != -1) {
                    // 중복 확인
                    if(find(words.begin(),words.end(), token) == words.end()){
                        cout << dict[foundIndex].first << ": " << dict[foundIndex].second << endl;
                        words.push_back(token); 
                    }
                }
            }
        } 
    }
    else{
        cout << "단어가 검색되지 않음" << endl;
    }
    return 0;
}