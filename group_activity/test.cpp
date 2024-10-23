#include<iostream>
using namespace std;

int main(){
    double a = 0.75;
unsigned int *pA = (unsigned int*)&a;
printf("%08x\n", *(pA+1));
printf("%08x\n", *pA);
    printf("%d", c);
    return 0;
}