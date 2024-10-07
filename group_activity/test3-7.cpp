#include<iostream>
using namespace std;

struct Node {
    int value;
    Node *next;
};

void rearrange(Node *list) {
    Node *p, *q;
    int temp;
    
    if (list == nullptr || list->next == nullptr) 
        return;

    p = list;        // 첫 번째 노드
    q = list->next;  // 두 번째 노드

    while (q != nullptr) {
        // 두 노드의 값 교환
        temp = p->value;
        p->value = q->value;
        q->value = temp;
        
        // 다음 짝 노드로 이동
        p = q->next;               // p는 q의 다음 노드를 가리킴
        q = (p != nullptr ? p->next : nullptr); // q는 p의 다음 노드를 가리킴 (p가 null이면 q도 null)
    }
}

void print_list(Node *head) {
    Node *p = head;
    while (p != nullptr) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

int main() {
    // 연결 리스트 생성
    Node *head = new Node{1, nullptr};
    head->next = new Node{2, nullptr};
    head->next->next = new Node{3, nullptr};
    head->next->next->next = new Node{4, nullptr};
    head->next->next->next->next = new Node{5, nullptr};
    head->next->next->next->next->next = new Node{6, nullptr};
    head->next->next->next->next->next->next = new Node{7, nullptr};

    cout << "Before rearrange: ";
    print_list(head);

    rearrange(head);

    cout << "After rearrange: ";
    print_list(head);

    return 0;
}
