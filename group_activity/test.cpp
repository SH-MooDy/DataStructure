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

Node* func(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next;
    while(current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return head;
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