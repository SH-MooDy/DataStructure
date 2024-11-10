#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

const string OPERATORS = "+-*/^()";
const int PRECEDENCE[] = {1, 1, 2, 2, 3, -1, -1};  // ^ 연산자 추가 (우선순위 3)
stack<char> operator_stack;
stack<double> operand_stack;

string::size_type is_operator(char ch) { return OPERATORS.find(ch); }

int precedence(char op) { return PRECEDENCE[is_operator(op)]; }

void apply_operator(char op) {
  double rhs = operand_stack.top();
  operand_stack.pop();
  double lhs =
      operand_stack.empty() ? 0 : operand_stack.top();  // 음수 처리 위해
  if (!operand_stack.empty()) operand_stack.pop();

  switch (op) {
    case '+':
      operand_stack.push(lhs + rhs);
      break;
    case '-':
      operand_stack.push(lhs - rhs);
      break;
    case '*':
      operand_stack.push(lhs * rhs);
      break;
    case '/':
      operand_stack.push(lhs / rhs);
      break;
    case '^':
      operand_stack.push(pow(lhs, rhs));
      break;
    default:
      cout << "Error: Unknown operator " << op << endl;
      exit(1);
  }
}

void process_op(char op) {
  if (operator_stack.empty() || op == '(') {
    operator_stack.push(op);
  } else {
    char top_op = operator_stack.top();
    if (precedence(op) > precedence(top_op)) {
      operator_stack.push(op);
    } else {
      while (!operator_stack.empty() && precedence(op) <= precedence(top_op)) {
        operator_stack.pop();
        if (top_op == '(') break;
        apply_operator(top_op);
        if (!operator_stack.empty()) top_op = operator_stack.top();
      }
      if (op != ')') {
        operator_stack.push(op);
      }
    }
  }
}

double evaluate(string infix) {
  stringstream token_stream;
  for (size_t i = 0; i < infix.length(); ++i) {
    char c = infix[i];
    if (isspace(c)) continue;

    if (isdigit(c) ||
        (c == '.' || (c == '-' && (i == 0 || is_operator(infix[i - 1]))))) {
      token_stream << c;
      while (i + 1 < infix.length() &&
             (isdigit(infix[i + 1]) || infix[i + 1] == '.')) {
        token_stream << infix[++i];
      }
      double number = stod(token_stream.str());
      operand_stack.push(number);
      token_stream.str("");
      token_stream.clear();
    } else if (is_operator(c) != string::npos) {
      process_op(c);
    } else {
      cout << "Error: Invalid character '" << c << "' in expression." << endl;
      exit(1);
    }
  }

  while (!operator_stack.empty()) {
    char op = operator_stack.top();
    if (op == '(') {
      cout << "Error: Unmatched parenthesis." << endl;
      exit(1);
    }
    operator_stack.pop();
    apply_operator(op);
  }

  return operand_stack.top();
}

int main() {
  string expr;
  cout << "Enter an infix expression: ";
  getline(cin, expr);
  cout << "Result: " << evaluate(expr) << endl;
  return 0;
}
