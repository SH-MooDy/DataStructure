#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *add_first(Node* head, int d) {
    Node* p = new Node;
    p->data = d;
    p->next = head;
    return p;
}

struct Node {
    int data;
    Node *next;
};

Node* func(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next;
    
    while (current != nullptr) {
        next = current->next;   // 다음 노드 저장
        current->next = prev;   // 현재 노드의 next를 이전 노드로 변경
        prev = current;         // prev를 현재 노드로 업데이트
        current = next;         // current를 다음 노드로 이동
    }
    
    return prev;  // prev는 역순으로 뒤집힌 리스트의 새로운 head
}


int main() {
    vector<int> vals{1, 2, 3, 4, 5, 6};
    Node* head = nullptr;
    for (int d: vals)
        head = add_first(head, d);

    head = func(head);
    Node* p = head;
    while(p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    return 0;
}