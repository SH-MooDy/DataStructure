#include <iostream>
#include <fstream>
#include <string>
#define MAX 1000
using namespace std;

int main() {
    string wordList[MAX];
    int duplicate[MAX] = { 0 }; // 각 단어의 출현 빈도를 저장
    ifstream infile("input4.txt");
    string word;
    int n = 0; // 저장된 단어의 수

    while (infile >> word) {
        if (word.length() >= 2) {
            // 단어 앞뒤 특수 문자 제거
            int start = 0;
            int end = word.length() - 1;

            // 단어의 앞부분 특수문자 제거
            while (start <= end && !isalpha(word[start])) {
                start++;
            }

            // 단어의 뒷부분 특수문자 제거
            while (end >= start && !isalpha(word[end])) {
                end--;
            }

            string tmpWord = word.substr(start, end - start + 1); // 유효한 부분만 추출

            // 중복 확인
            bool isDuplicate = false;
            for (int i = 0; i < n; i++) {
                if (wordList[i] == tmpWord) {
                    duplicate[i] += 1; // 중복된 단어의 빈도 증가
                    isDuplicate = true;
                    break;
                }
            }

            // 중복이 아닐 시 단어 추가
            if (!isDuplicate && !tmpWord.empty()) {
                wordList[n] = tmpWord;
                duplicate[n] = 1; // 첫 등장시 빈도는 1
                n++;
            }
        }
    }

    // 정렬 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (wordList[j] > wordList[j + 1]) {  
                swap(wordList[j], wordList[j + 1]);
                swap(duplicate[j], duplicate[j + 1]);
            }
        }
    }

    // 정렬 후 결과 출력
    for (int i = 0; i < n; i++) {
        cout << wordList[i] << " " << duplicate[i] << endl;
    }

    infile.close();
    return 0;
}
