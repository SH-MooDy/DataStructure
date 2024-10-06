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
    cout << wordTotal << endl;
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

// 파일을 읽고 연결리스트를 생성하는 함수
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
                p->next = q;
            }
            wordTotal++;
        }
    }
    infile.close();
}

// 연결리스트를 사전순으로 정렬하는 함수
void sort_list_by_dict() {
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

// 등장 빈도가 10 이하인 단어들을 삭제하는 함수
void remove_rare_words() {
    Node *p = head;
    Node *prev = nullptr;

    while(p != nullptr) {
        if(p->count <= 10) {
            if(prev == nullptr) {
                head = p->next;
            }
            else {
                prev->next = p->next;
            }
            Node *tmp = p;
            p = p->next;
            delete tmp;
            wordTotal--; // 노드가 삭제될 때마다 전체 단어 수 하나 줄이기
        }
        else {
            prev = p;
            p = p->next;
        }
    }
}

// 기존 연결리스트 삭제 함수
void delete_old_list(Node* listHead) {
    Node *p = listHead;
    while(p != nullptr)  {
        Node *q = p->next; // 다음 노드를 미리 저장
        delete p; // 현재 노드를 삭제
        p = q; // 다음 노드로 이동
    }
}

// 등장 빈도수로 정렬된 새로운 연결리스트를 만드는 함수
void sort_list_by_frequency() {
    Node *p = head; // 기존 연결리스트의 첫노드를 가리키는 포인터
    Node *sortedHead = nullptr; // 정렬된 연결리스트의 첫노드를 가리키는 포인터

    while(p != nullptr) {
        Node *newNode = new Node;
        newNode->word = p->word;
        newNode->count = p->count;
        newNode->next = nullptr;

        if(sortedHead == nullptr) {
            sortedHead = newNode; // 정렬된 리스트가 비어있으면 첫 노드로 설정
        }
        else {
            Node *sq = sortedHead;
            Node *sp = nullptr;

            // 내림차순으로 삽입할 위치를 찾음
            while (sq != nullptr && (sq->count > newNode->count || (sq->count == newNode->count && sq->word < newNode->word))) {
                sp = sq;
                sq = sq->next;
            }

            if(sp == nullptr) {
                // 삽입 위치가 첫 노드인 경우
                newNode->next = sortedHead;
                sortedHead = newNode;
            }
            else {
                newNode->next = sq;
                sp->next = newNode;
            }
        }
        p = p->next;
    }
    delete_old_list(head); // 기존 리스트 삭제
    head = sortedHead; // 기존 리스트의 head를 정렬된 리스트로 갱신
}
int main() {
    // (1)
    read_file(); // 파일에서 단어들을 읽어와 연결리스트 생성
    sort_list_by_dict(); // 사전식순으로 연결 리스트 정렬
    print_list();  
    cout << endl;

    // (2)
    remove_rare_words(); // 등장 빈도가 10이하인 단어들을 제거
    print_list();  
    cout << endl;

    // (3)
    sort_list_by_frequency(); // 등장 빈도를 기준으로 내림차순 정렬
    print_list(); 
    cout << endl;
    return 0;
}