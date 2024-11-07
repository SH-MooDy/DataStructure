#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_CAPACITY = 1000000;

class Stack {
private:
    char stack[MAX_CAPACITY];
    int top_pos = -1;

public:
    bool full() {
        return top_pos == MAX_CAPACITY - 1;
    }

    bool empty() {
        return top_pos == -1;
    }

    void push(char i) {
        if (full()) {
            throw runtime_error("stack_full");
        }
        stack[++top_pos] = i;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("stack_empty");
        }
        top_pos--;
    }

    char top() {
        if (empty()) {
            throw runtime_error("stack_empty");
        }
        return stack[top_pos];
    }

    int size() {
        return top_pos + 1;
    }

    string getStackContent() {
        string result;
        for (int i = 0; i <= top_pos; i++) {
            result += stack[i];
        }
        return result;
    }
};

int main() {
    Stack s1;
    string num;
    int remove_digit;

    cin >> num;
    cin >> remove_digit;

    int digits_to_keep = num.size() - remove_digit;

    for (auto n : num) {
        while (!s1.empty() && s1.top() < n && remove_digit > 0) {
            s1.pop();
            remove_digit--;
        }
        s1.push(n);
    }

    // 스택의 상위 요소만 남겨놓기 위해 잘라냄
    string result = s1.getStackContent().substr(0, digits_to_keep);
    cout << result << endl;

    return 0;
}
