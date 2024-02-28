#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    int list[5]; //정수형 배열 list 선언
    int *plist[5]; //정수형 포인터 배열 plist 선언

    list[0] = 10; //배열 list의 0번째 배열에 10을 대입
    list[1] = 11; //배열 list의 1번째 배열에 11을 대입

    plist[0] = (int*)malloc(sizeof(int)); //포인터 배열 plist의 0번째 인덱스를 int의 크기(4bytes)만큼 동적할당

    printf("list[0] \t= %d\n", list[0]); //list[0]의 값 10 출력
    printf("list \t\t= %p\n", list); //list의 주소 출력(배열의 이름은 주소)
    printf("&list[0] \t= %p\n", &list[0]); //list[0]의 주소 출력
    printf("list + 0 \t= %p\n", list+0); //list의 주소에서 int의 크기만큼 0번(0bytes) 이동한 주소 출력
    printf("list + 1 \t= %p\n", list+1); //list의 주소에서 int의 크기만큼 1번(4bytes) 이동한 주소 출력
    printf("list + 2 \t= %p\n", list+2); //list의 주소에서 int의 크기만큼 2번(8bytes) 이동한 주소 출력
    printf("list + 3 \t= %p\n", list+3); //list의 주소에서 int의 크기만큼 3번(12bytes) 이동한 주소 출력
    printf("list + 4 \t= %p\n", list+4); //list의 주소에서 int의 크기만큼 4번(16bytes) 이동한 주소 출력
    printf("&list[4] \t= %p\n", &list[4]); //list[4]의 주소 출력(list[4] = list+4)

    free(plist[0]); //plist[0]의 동적할당 해제
}