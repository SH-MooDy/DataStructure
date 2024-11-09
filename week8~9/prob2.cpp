#include <iostream>
using namespace std;

const int MAX_CAPACITY = 100000;

class Stack {
 private:
  int stack[MAX_CAPACITY];
  int top_pos = -1;
  int count = 0;

 public:
  bool full() { return top_pos == MAX_CAPACITY - 1; }

  bool empty() { return top_pos == -1; }

  void push(int i) {
    if (full()) {
      throw runtime_error("stack_full");
    }
    stack[++top_pos] = i;
    count++;
  }

  void pop() {
    if (empty()) {
      throw runtime_error("stack_empty");
    }
    top_pos--;
    count--;
  }

  int top() {
    if (empty()) {
      throw runtime_error("stacK_empty");
    }
    return stack[top_pos];
  }

  int size() { return count; }
};

int main() {
  int N;
  cin >> N;

  Stack s1;

  for (int i = 0; i < N; i++) {
    int num;
    cin >> num;

    while (!s1.empty() && s1.top() <= num) {
      s1.pop();
    }

    s1.push(num);
    cout << s1.size() << " ";
  }
  return 0;
}