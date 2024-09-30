#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

struct Point2D {
    int x, y;
};

// 두 점 사이의 거리 제곱을 계산하는 함수
double calDistance(Point2D *p1, Point2D *p2) {
    return pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2);
}

int main() {
    int n = 0, size = 4, maxDistance = 0; // 점 개수, 배열 크기, 최대 거리 변수
    int maxP1Index = 0, maxP2Index = 0; // 가장 멀리 있는 두 점의 인덱스
    Point2D* Parr = new Point2D[size]; // 동적할당

    // 파일부터 입력 받기
    ifstream infile("input2.txt");
    infile >> n;
    
    for (int i = 0; i < n; i++) {
        // 배열 크기 조정
        if (i == size) {
            size *= 2; 
            Point2D* tmp = new Point2D[size];
            for (int j = 0; j < i; j++) {
                (tmp + j)->x = (Parr + j)->x;
                (tmp + j)->y = (Parr + j)->y;
            }
            delete[] Parr;
            Parr = tmp;
        }
        // 점의 좌표 입력 받기
        infile >> (Parr + i)->x >> (Parr + i)->y;

        for(int j = 0; j < i; j++) {
            int distance = calDistance(Parr + j, Parr + i); 
            // 현재 계산된 거리가 지금까지의 최대 거리보다 크면 갱신
            if (maxDistance < distance) { 
                maxDistance = distance; 
                maxP1Index = j; // 첫번째 점의 인덱스 저장
                maxP2Index = i; // 두번째 점의 인덱스 저장
            }
        }
    }
    
    // 출력
    cout << (Parr + maxP1Index)->x << " " << (Parr + maxP1Index)->y << endl;
    cout << (Parr + maxP2Index)->x << " " << (Parr + maxP2Index)->y << endl;
    cout << sqrt(maxDistance) << endl;

    delete[] Parr; // 메모리 해제
    return 0;
}
