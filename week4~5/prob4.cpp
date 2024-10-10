#include<iostream>
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
    /* head와 tail이 가리키는 2중 연결리스트에 문자열들이 사전식 순서로 정렬된 순서를 유지하도록 새로운 문자열 item을 삽입한다. */
    Node *p = head;

    Node *new_node = new Node;
    new_node->data = item;
    new_node->prev = nullptr;
    new_node->next = nullptr;

    if (head == nullptr) { // 리스트가 비어있을 때
        head = new_node;
        tail = new_node;
    }
    else {
        // 삽입 위치를 찾기 위해 순차적으로 탐색
        while (p != nullptr && p->data < item) {
            p = p->next;
        }

        if (p == nullptr) { // 삽입 위치가 리스트의 끝인 경우
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        else if (p == head) { // 삽입 위치가 리스트의 맨 앞인 경우
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        else { // 삽입위치가 일반적인 경우
            new_node->prev = p->prev;
            new_node->next = p;
            p->prev->next = new_node;
            p->prev = new_node;
        }
    }
}


void remove_dup() {
    /* 2중 연결리스트에 저장된 문자열들 중에서 모든 중복된 문자열을 찾아 하나만 남기고 제거한다. */
    Node *p = head;

    if (head == nullptr) { // 리스트가 비어있는 경우
        return;
    }

    while (p != nullptr && p->next != nullptr) {
        if (p->data == p->next->data) { // 중복된 문자열이 발견된 경우
            Node *dup = p->next;  
            p->next = dup->next;
            
            if (dup->next != nullptr) {
                dup->next->prev = p; // 중복 노드의 다음 노드가 있는 경우, 그 노드의 이전 노드를 p로 지정
            } else {
                tail = p;  
            }
        } else {
            p = p->next;  
        }
    }
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