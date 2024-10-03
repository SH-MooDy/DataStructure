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
    infile.ignore() // 개행문자 무시

    for(int i=0; i<num; i++) {
        getline(infile, line);
        stringstream ss(line);
        ss >> x >> y >> w >> h; // 스트링스트림으로 하나씩 받아오기

        Node *q = new Node;
        q->x = x;
        q->y = y;  
        q->w = w;
        q->h = h;
        q->next = nullptr;

        if(n == 0) { // 연결리스트 첫 생성의 경우
            head = q;.
        } else { 
            Node *p = head; // head부터 시작
            if(p->next != nullptr) { // 마지막 노드까지 이동
                p = p->next;
            }

            p->next = q; // 마지막 노드의 next를 새 노드로 설정
        }
    }
}

void sort_by_area() { 
    // head가 가리키는 연결리스트를 면적순으로 정렬한다.  
}

int main() {
    // (1)
    read_file(); // 파일을 읽어서 파일에 저장된 순서대로 저장된 연결리스트를 구성한다.
    print_list(); // 파일에 저장된 순서대로 출력된다.
v  
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