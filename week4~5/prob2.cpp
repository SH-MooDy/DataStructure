#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node {
    string word; // 단어
    int count; // 단어의 등장 빈도
    Node *next;
};
Node *head = nullptr;

int wordTotal = 0; // 전체 단어의 개수

// 연결리스트 내용을 출력하는 함수
void print_list() {
    Node *p = head;
    while(p != nullptr) {
        cout << p->word << ": " << p->count << endl;
        p = p->next;
    }
}

// 중복 여부 확인 함수
bool check_dup(string word) {
    Node *p = head;
    while(p != nullptr) {
        if(p->word == word) {
            p->count += 1; // 중복된 단어의 count값 증가
            return true; // 중복이 발견된 경우 true 반환
        }
        p = p->next;
    }
    return false; // 중복이 없으면 false 반환
}

// 파일을 일고 연결리스트를 생성하는 함수
void read_file() {
    ifstream infile ("harry.txt");
    string word;

    while(infile >> word) {
        if(!check_dup(word)) {
            // 중복이 아니면 새노드 생성
            Node *q = new Node;
            q->word = word;
            q->count = 1;
            q->next = nullptr;

            if(head == nullptr)  { // 첫노드의 경우
                head = q;
            }
            else {
                Node *p = head;
                while(p->next != nullptr) {
                    p = p->next;
                }
                p->next = q; // 마지막 노드의 새 노드를 q로 설정
            }

        }
    }
    infile.close();
}

void sort_list() {
    if (head == nullptr || head->next == nullptr) { return; } // 리스트가 비어있거나 노드가 하나인 경우

    // 버블 정렬을 통해 정렬
    bool isSwaped = true;
    while (isSwaped) {
        Node *p = head; // 현재 노드
        Node *prev = nullptr; // 이전 노드
        isSwaped = false;

        while (p != nullptr && p->next != nullptr ) {
            Node *q = p -> next;
            if (p->word > q->word) { 
                if (prev == nullptr) {
                    head = q;
                }
                else {
                    prev->next = q;
                }
                
                p->next = q->next;
                q->next = p;
                isSwaped = true;
                
                prev = q;
            }
            else {
                prev = p;
                p = p->next;
            }

        }
    }

}

int main() {
    // (1)
    read_file(); // 파일에서 단어들을 읽어와 연결리스트 생성
    sort_list(); // 연결 리스트 정렬
    print_list(); // 연결 리스트 출력
    cout << endl;

    // (2)

    return 0;
}