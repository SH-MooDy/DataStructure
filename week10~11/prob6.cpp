#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string binary_sequence;
int K;
vector<string> result;

// 두 문자열에서 서로 다른 문자의 개수를 리턴하는 함수
int countDifferent(const string& str1, const string& str2) {
  int length = min(str1.size(), str2.size());
  int count = 0;

  for (int i = 0; i < length; ++i) {
    if (str1[i] != str2[i]) {
      ++count;
    }
  }

  count += abs(static_cast<int>(str1.size()) - static_cast<int>(str2.size()));
  return count;
}

void findBinarySequences(string sequence, int i) {
  if (sequence.length() == binary_sequence.length()) {
    if (countDifferent(sequence, binary_sequence) == K) {
      result.push_back(sequence);
    }
    return;
  }

  findBinarySequences(sequence + "0", i + 1);
  findBinarySequences(sequence + "1", i + 1);
}

int main() {
  cin >> binary_sequence >> K;

  findBinarySequences("", 0);

  for (const auto& s : result) {
    cout << s << endl;
  }
  return 0;
}
