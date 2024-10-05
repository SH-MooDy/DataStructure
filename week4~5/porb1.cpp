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
        getline(infile, line);
        stringstream ss(line);
        ss >> x >> y >> w >> h; // 스트링스트림으로 하나씩 받아오기

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
}

void sort_by_area() { 
    if (head == nullptr || head->next == nullptr) { retrun;} // 리스트가 비어있거나 노드가 하나인 경우
    
    // 버블 정렬을 통해 정렬
    bool isSwaped = true;
    while (isSwaped) {
        Node *p1 = head; // 현재 노드
        Node prev = nullptr; // 이전 노드
        isSwaped = false;

        while (p1 != nullptr && p1 != nullptr ) {
            Node *p2 = p1 -> next;
            int area1 = p1->w * p2->h;
            int area2 = p2->w * p2->h;
            if (area1 > area2) {
                if (prev == nullptr) {
                    p2 = head;
                    p1->next = p2->next;
                    p2->next = p1;
                }
                else {
                    
                }
            }
        }
    }
    

}

remove_rects(min_w, min_h){
    
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