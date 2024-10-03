#include<iostream>
#include<fstream>

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
    // rects.txt 파일을 읽어서 사각형들을 파일에 저장된 순서대로  
    // head가 가리키는 연결리스트에 저장한다.
}

void sort_by_area() { 
    // head가 가리키는 연결리스트를 면적순으로 정렬한다.  
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