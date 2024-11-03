#include<iostream>
#include<string>
using namespace std;

const int MAX_CAPACITY = 100;
class Stack {
private:
    int stack[MAX_CAPACITY];
    int top_pos = -1;

public:
    bool full() {
        return top_pos == MAX_CAPACITY - 1;
    }

    bool empty() {
        return top_pos == -1;
    }

    void push(int i) {
        if(full()) {
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

    int top() {
        if(empty()) {
            throw runtime_error("stacK_empty");
        }
        return stack[top_pos];
    }
};

int main() {
    Stack s1;
    string str;
    getline(cin, str);

    int i = 1; // 괄호의 번호를 메기기 위한 인덱스
    for(auto c : str) {
        if(c == '(') {
            s1.push(i);
            cout << i << " ";
            i++;
        }
        else if(c == ')') {
            cout << s1.top() << " ";
            s1.pop();
        }
    }

    return 0;
}