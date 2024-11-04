#include<iostream>
using namespace std;

const int MAX_CAPACITY = 100000;
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
    int n = 0;
    cin >> n;

    for(int i=0; i<n; i++) {
        int num;
        cin >> num;
        s1.push(num);
    }

    
    return 0;
}