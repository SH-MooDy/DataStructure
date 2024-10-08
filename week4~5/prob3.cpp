#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Term {
    int coef;
    int expo;
    Term *next = nullptr;

    Term() {}

    Term(int c, int e):coef(c), expo(e) {}
    Term(int c, int e, Term *p): coef(c), expo(e), next(p) {}
};

struct Polynomial {
    char name;
    Term *first = nullptr;
    int size = 0;
    Polynomial() {}
    Polynomial(char name):name(name) {}
};

vector<Polynomial> polys;
void add_term(Polynomial &poly, int c, int e);
vector<Polynomial>::iterator find_poly(char name);
void print_term(Term *pTerm);
void print_poly(Polynomial &p);
void handle_print(char name);
int calc_term(Term *term, int x);
int calc_poly(Polynomial poly, int x);
void handle_calc(char name, int x);
void clear_poly(Polynomial &p);
void insert_polynomial(Polynomial p);
void handle_add(char name, int c, int e);
void addpoly(Polynomial pol, char name1, char name2);
void multiplypoly(Polynomial po1, char name1, char name2);

int main(){
    string command, arg1, arg2, arg3;
    while(1) {
        cout << "$ ";
        cin >> command;
        if(command == "print") {
            cin >> arg1;
            handle_print(arg1[0]);
        }
        else if (command == "calc") {
            cin >> arg1 >> arg2;
            handle_calc(arg1[0], stoi(arg2));
        }
        else if (command == "define") {
            cin >> arg1;
            Polynomial pol(arg1[0]);
            insert_polynomial(pol);
        }
        else if (command == "add") {
            cin >> arg1 >> arg2 >> arg3;
            handle_add(arg1[0], stoi(arg2), stoi(arg3));
        }
        else if (command == "addpoly") {
            cin >> arg1 >> arg2 >> arg3;
            Polynomial pol(arg1[0]);
            addpoly(pol, arg2[0], arg3[0]);
        }
        else if (command == "multiplypoly") {
            cin >> arg1 >> arg2 >> arg3;
            Polynomial pol(arg1[0]);
            multiplypoly(pol, arg2[0], arg3[0]);
        }
        else if (command == "exit")
            break;

    }
    return 0;
}

void add_term(Polynomial &poly, int c, int e) {
    if(c == 0)
        return;
    Term *p = poly.first, *q = nullptr;
    while (p != nullptr && p->expo > e) {
        q = p;
        p = p->next;
    }
    if (p!=nullptr && p->expo == e) { // 동일 차수의 항이 존재하는 경우
        p->coef += c;
        if (p->coef == 0) { // 더했더니 계수가 0이 되는 경우
            if (q==nullptr) // q의 다음 노드를 삭제, q가 nullptr인 경우 첫번째노드 삭제
                poly.first = p->next;
            else
                q->next = p->next;
            poly.size--;
            delete p; // 불필요해진 노드 p를 delete한다.
        }
        return;
    }
    if (q==nullptr) // 맨 앞에 삽입하는 경우
        poly.first = new Term(c, e, poly.first);
    else // q의 뒤, p의 앞에 삽입 (p는 null일수도 있음)
        q->next = new Term(c, e, p);

    poly.size++;
}

vector<Polynomial>::iterator find_poly(char name) {
    for (auto it=polys.begin(); it!=polys.end(); it++) {
        if (it->name == name)
            return it;
    }
    return polys.end();
}

void print_term(Term *pTerm) {
    if (pTerm->expo == 0)
        cout << pTerm->coef; // 지수가 0이면 상수만 출력
    else if (pTerm->expo == 1)
        cout << pTerm->coef << "x"; // 지수가 1이면 x만 출력
    else
        cout << pTerm->coef << "x^" << pTerm->expo; // 일반적인 경우
}

void print_poly(Polynomial &p) {
    cout << p.name << " = ";
    Term *t = p.first;

    // 첫 번째 항은 따로 출력 (첫 항의 앞에 + 기호가 붙지 않게 하기 위함)
    if (t != nullptr) {
        print_term(t);
        t = t->next;
    }

    // 나머지 항들은 앞에 +를 붙여서 출력
    while (t != nullptr) {
        if(t->coef >= 0){
            cout << "+";
        }
        print_term(t);
        t = t->next;
    }
    
    cout << endl;
}

void handle_print(char name) {
    auto it = find_poly(name);
    if (it == polys.end())
        cout << "No such polynomial exists." << endl;
    else
        print_poly(*it);
}

int calc_term(Term *term, int x) { // 하나의 항의 값을 계산하는 함수
    int result = term->coef;
    for (int i=0; i<term->expo; i++) {
        result *= x;
    }
    return result;
}

int calc_poly(Polynomial poly, int x) { // 다항식의 값을 계산하는 함수
    int result = 0;
    Term *t = poly.first;
    while(t != nullptr) {
        result += calc_term(t, x); // 각각의 항의 값을 계산하여 더함
        t = t->next;
    }
    return result;
}

void handle_calc(char name, int x) {
    auto it = find_poly(name);
    if (it==polys.end()) 
        cout << "No such polynomial exists." << endl;
    else    
        cout << calc_poly(*it, x) << endl;
}

void clear_poly(Polynomial &p) {
    Term *t = p.first, *tmp;
    while (t!=nullptr) {
        tmp = t;
        t = t->next;
        delete tmp;
    }
    p.first = nullptr;
}

void insert_polynomial(Polynomial p) {
    auto it = find_poly(p.name);
    if (it == polys.end()) {
        polys.push_back(p);
    }
    else {
        clear_poly(*it);
        *it = p; // 덮어씌우기
    }
}

void handle_add(char name, int c, int e) {
    auto it = find_poly(name);
    if (it == polys.end()) {
        cout << "No such polynomial exists." << endl;
        return;
    }
    add_term(*it, c, e);
}

void addpoly(Polynomial pol, char name1, char name2) {
    auto it1 = find_poly(name1); 
    auto it2 = find_poly(name2);

    if (it1 == polys.end() || it2 == polys.end()) {
        return;
    }

    Term *p1 = it1->first;
    Term *p2 = it2->first;

    // 첫번째 다항식의 모든 항을 새로운 다항식에 추가
    while(p1 != nullptr) {
        add_term(pol, p1->coef, p1->expo);
        p1 = p1->next;
    }

    // 두번째 다항식의 모든 항을 새로운 다항식에 추가
    while(p2 != nullptr) {
        add_term(pol, p2->coef, p2->expo);
        p2 = p2->next;
    }

    insert_polynomial(pol);

}

void multiplypoly(Polynomial pol, char name1, char name2) {
    auto it1 = find_poly(name1); 
    auto it2 = find_poly(name2);

    if (it1 == polys.end() || it2 == polys.end()) {
        return;
    }
    
    Term *p1 = it1->first;

    // 이중 반복문으로 각항을 곱한 후 추가
    while(p1 != nullptr) {
            Term *p2 = it2->first;
        while(p2 != nullptr) {
            add_term(pol, p1->coef * p2->coef, p1->expo + p2->expo);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    insert_polynomial(pol);
}