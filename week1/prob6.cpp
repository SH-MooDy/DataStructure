#include<iostream>
#include<string>
using namespace std;

int main() {
	string sentence;
	while (1) {
		cout << "$ ";
		getline(cin, sentence);

		// exit 입력 시 종료
		if (sentence == "exit") { break; }

		int countWord = 0; // 단어 수
		bool isWord = false; // 단어인지 여부

		// 단어 수 세기
		for (char c : sentence) {
			if (!isspace(c)) {
				// 공백이 아니면서 앞선 상태가 단어가 아니였을 경우 단어수 증가, 단어인지 여부 true로 설정
				if (!isWord) {
					countWord++;
					isWord = true;
				}
			} 
			else {
				isWord = false; // 공백인 경우 단어 인지 여부 false로 변경
			}
		}
		cout << sentence << ":" << sentence.length() << ":" << countWord << endl;
	}
	// 스트링 스트림 활용하는 방법 공부하기
	return 0;
}