#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

struct Node {
    int x, y, w, h;
    Node *next;
};
Node *head = nullptr;

void print_list() {
    Node *p = head;
    while(p!=nullptr) {
        cout << p->x << " " << p->y << " " << p->w << " " << p->h << endl;
        p = p->next;
    }
}

void read_file() {
    int num = 0;
    int x, y, w, h;
    string line;
    ifstream infile("rects.txt");

    infile >> num;
    infile.ignore(); // 개행문자 무시

    for(int i=0; i < num; i++) {
        infile >> x >> y >> w >> h;  

        Node *q = new Node;
        q->x = x;
        q->y = y;  
        q->w = w;
        q->h = h;
        q->next = nullptr;

        if(head == nullptr) { // 연결리스트 첫 생성의 경우
            head = q;
        } else { 
            Node *p = head;
            while(p->next != nullptr) { // 마지막 노드까지 이동
                p = p->next;
            }

            p->next = q; // 마지막 노드의 next를 새 노드로 설정
        }
    }
    infile.close();
}

void sort_by_area() { 
    if (head == nullptr || head->next == nullptr) { return; } // 리스트가 비어있거나 노드가 하나인 경우
    
    // 버블 정렬을 통해 정렬
    bool isSwaped = true;
    while (isSwaped) {
        Node *p = head; // 현재 노드
        Node *prev = nullptr; // 이전 노드
        isSwaped = false;

        while (p != nullptr && p->next != nullptr ) {
            Node *q = p -> next;
            int area1 = p->w * p->h;
            int area2 = q->w * q->h;

            // 앞선 노드의 넓이가 뒷 노드 보다 넓다면 노드 스왑
            if (area1 > area2) {
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

void remove_rects(int min_w, int min_h){
    if (head == nullptr) { return; } 
    Node *p = head;
    Node *prev = nullptr;
    
    while (p != nullptr) {
        if (p->w < min_w || p->h < min_h) {
            if(prev == nullptr) { // head를 삭제하는 경우
                head = p->next;
            }
            else { // 그 외 일반적인 경우
                prev->next = p->next;
            }
            Node *tmp = p;
            p = p->next;
            delete tmp; // 삭제 후 노드 메모리 해제 
        }
        else {
            prev = p;
            p = p->next;
        }
    }
}

int main() {
    // (1)
    read_file(); // 파일을 읽어서 파일에 저장된 순서대로 저장된 연결리스트를 구성한다.
    print_list(); // 파일에 저장된 순서대로 출력된다.
    cout << endl; // 한 줄을 띄운다.

    // (2)
    sort_by_area(); // 연결리스트의 노드들을 면적순으로 정렬한다.
    print_list(); // 정렬된 순서대로 출력한다.
    cout << endl;

    // (3)
    int min_w, min_h;
    cin >> min_w >> min_h;
    remove_rects(min_w, min_h);
    print_list();
    
    return 0;
}
