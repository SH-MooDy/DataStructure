#include <iostream>
#include <string>
using namespace std;

bool is_palindrome(string str, int start_index, int end_index) {
  if (start_index >= end_index) {
    return true;
  }
  if (str[start_index] != str[end_index]) {
    return false;
  }
  return is_palindrome(str, start_index + 1, end_index - 1);
}

int main() {
  string str;
  cin >> str;
  if (is_palindrome(str, 0, str.length() - 1)) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
