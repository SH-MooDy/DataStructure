#include<iostream>
#include<fstream>
#include<string>
#define MAX 1000
using namespace std;

int main() {
    string wordList[MAX];
    ifstream infile("input4.txt");
    string word;
    int n = 0; // 배열의 인덱스

    // 파일로부터 단어를 하나씩 받아오기
    while (infile >> word) {
        // 길이가 2이상인 단어만 인식
        if (word.length() >= 2) {

            bool isDuplicate = false; // 중복여부를 나타내는 플래그
            for (int i = 0; i < n; i++) {
            
                // 중복 발견시 duplicate를 true로 변경 후 for문 탈출
                if (wordList[i] == word) {
                    isDuplicate = true;
                    break; 
                }
            }
            // 중복되지 않은 단어인 경우만 출력 및 배열에 추가
            if (!isDuplicate) {
                cout << word << endl;
                wordList[n++] = word;
            }
        }
    }
    infile.close();
    return 0;
}