#include<iostream>
#include<string>
using namespace std;

struct Node {
    string data;
    Node *prev, *next;
};

void ordered_insert(string item);
void remove_dup();
void print_list_twice();

Node *head = nullptr, *tail = nullptr; // 2중 연결리스트의 처음과 마지막 노드

int main() {
    int n;

    string word;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> word;
        ordered_insert(word);
    }

    print_list_twice();
    remove_dup();
    print_list_twice();
    return 0;
}

void ordered_insert(string item) {
    /* head와 tail이 가리키는 2중 연결리스트에 문자열들이 사전식 순서로 정렬된 순서를 유지하 도록 새로운 문자열 item을 삽입한다. */
    Node *head = nullptr;
    Node *tail = nullptr;
    Node *p = nullptr;

    Node *new_node = new Node;
    new_node->data = item;
    new_node->prev = nullptr;
    new_node->next = nullptr;

    if(p == nullptr && head == nullptr) {
        head = new_node;
        tail = new_node;
    }
    else {
        while(p != nullptr && item < p->data) {
            if(p->data > item) {
                if(p == head) { // 가장 앞에 삽입하는 경우우
                    new_node->next = head;
                    head->prev = new_node;
                    head = new_node;
                }
                else if(p == tail) { // 가장 뒤에 삽입하는 경우
                    new_node->prev = tail;
                    tail->next = new_node;
                    tail = new_node;
                }
                else {
                    new_node->prev = p;
                    new_node->next = p->next;
                    p->next->prev = new_node;
                    p->next = new_node;
                }
            }
            p = p->prev;
        }
    }
}

void remove_dup() {
    /* 2중 연결리스트에 저정된 문자열들 중에서 모든 중복된 문자열을 찾아 하나만 남기고 제거한다. */
}

void print_list_twice() {
    Node *p = head;
    while(p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;

    Node *q = tail;
    while(q != nullptr) {
        cout << q->data << " ";
        q = q->prev;        
    }
    cout << endl;
}