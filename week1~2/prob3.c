#include<stdio.h>
#include<string.h>
#define MAXWORDS 100
#define MAXLEN 30

int main() {
    char* words[MAXWORDS];
    int n;
    scanf("%d", &n);

    char buf[MAXLEN];
    for (int i = 0; i < n; i++) {
        // 방법1: words[i]가 초기화 되지 않았으므로 메모리를 할당 받지 않았다.
        //        따라서 words[i]가 가리키는 곳이 어디인지 알 수 없다.
        scanf("%s", words[i]); 

        // 방법2: 이 코드에선 모든 입력을 buf에 저장한 후 words[i]가 buf를 가리키게 만든다.
        //        이렇게 되면, 모든 words[i]가 같은 buf를 가리키게 되므로 마지막에 입력된 값으로 모든 값이 덮어써지게 된다.
        scanf("%s", buf);
        words[i] = buf;

        // 방법3: words[i]에 메모리가 따로 할당되지 않은 상태이다. 따라서  strcpy함수로 복사 할 수 없다.
        scanf("%s", buf);
        strcpy(words[i], buf); 

        // 올바른 방법:
        scanf("%s", buf);
        words[i] = strdup(buf);
    }
    for (int i = 0; i < n; i++)
        printf("%s\n", words[i]);
    return 0;
}