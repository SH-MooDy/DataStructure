#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node {
    string word; // 단어
    int count; // 등장 빈도
    Node *next;
};
Node *head = nullptr;

int count_All_words = 0; // 전체 단어의 개수

void read_file() {
    ifstream infile ("harry.txt");
    string word;
    while(infile >> word) {

        
    }
}

void sort_list() {

}

void print_list() {
    Node *p = head;
    while(head != nullptr) {
        cout << p->word << ": " << p->count << endl;
        p = p->next;
    }
}

void 
int main() {
    // (1)
    read_file(); // 파일에서 단어들을 읽어와 연결리스트 생성
    sort_list(); // 연결 리스트 정렬
    pring_list(); // 연결 리스트 출력
    

    return 0;
}