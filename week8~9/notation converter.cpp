#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <string>
#include <unordered_map>
using namespace std;
// 연산자 우선순위를 설정하는 함수
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// 중위 표기법을 후위 표기법으로 변환하는 함수
string infixToPostfix(const string &expression) {
    stack<char> operators;
    ostringstream postfix;
    
    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];

        // 공백 무시
        if (ch == ' ') continue;

        // 숫자 처리
        if (isdigit(ch)) {
            // 여러 자리 숫자를 처리하기 위해 연속된 숫자를 모두 읽음
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                postfix << expression[i];
                ++i;
            }
            postfix << ' ';
            --i; // 마지막 증가된 i를 조정
        }
        // 왼쪽 괄호는 스택에 넣기
        else if (ch == '(') {
            operators.push(ch);
        }
        // 오른쪽 괄호는 왼쪽 괄호가 나올 때까지 연산자를 pop
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // '(' 제거
        }
        // 연산자 처리
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // 스택에 남아있는 연산자들을 pop
    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }

    return postfix.str();
}

int main() {
    string expression;
    getline(cin, expression);
    string postfix = infixToPostfix(expression);
    cout << "Postfix: " << postfix << endl;
    return 0;
}
