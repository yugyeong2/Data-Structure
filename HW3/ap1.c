#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    int list[5]; //정수형 배열 list 선언
    int *plist[5] = {NULL,}; //정수형 포인터 배열 plist를 선언하고 NULL로 초기화

    plist[0] = (int *)malloc(sizeof(int)); //포인터 배열 plist의 0번째 인덱스를 int의 크기(4bytes)만큼 동적할당

    list[0] = 1; //배열 list의 0번째 인덱스에 1 대입
    list[1] = 100; //배열 list의 1번째 인덱스에 100 대입

    *plist[0] = 200; //배열 포인터 plist의 0번째 인덱스가 가리키는 곳에 200을 대입

    printf("list[0] = %d\n", list[0]); //list[0]의 값 1 출력
    printf("&list[0] = %p\n", &list[0]); //list[0]의 주소 출력
    printf("list = %p\n", list); //list의 주소 출력(배열의 이름은 주소)
    printf("&list = %p\n", &list); //list의 주소 출력
    //&list[0] = list = &list
    printf("----------------------------------------\n\n");

    printf("list[1] = %d\n", list[1]); //list[1]의 값 100 출력
    printf("&list[1] = %p\n", &list[1]); //list[1]의 주소 출력
    printf("*(list+1) = %d\n", *(list + 1)); //list의 주소에서 int의 크기만큼 1번(4bytes) 이동한 곳의 값 출력
    printf("list+1 = %p\n", list+1); //list의 주소에서 int의 크기(4bytes)만큼 이동한 주소 출력
    //&list[1] = list+1
    printf("----------------------------------------\n\n");
    
    printf("*plist[0] = %d\n", *plist[0]); //plist[0]이 가리키는 곳의 값 200 출력
    printf("&plist[0] = %p\n", &plist[0]); //plist[0]의 주소 출력
    printf("&plist = %p\n", &plist); //plist의 주소 출력
    printf("plist = %p\n", plist); //plist의 주소 출력(배열의 이름은 주소)
    //&plist[0] = &plist = plist
    printf("plist[0] = %p\n", plist[0]); //plist[0]의 값 출력(배열 포인터이기 때문에 주소가 저장된다)
    printf("plist[1] = %p\n", plist[1]); //plist[1]의 값 출력(할당되지 않았다)
    printf("plist[2] = %p\n", plist[2]); //plist[2]의 값 출력(할당되지 않았다)
    printf("plist[3] = %p\n", plist[3]); //plist[3]의 값 출력(할당되지 않았다)
    printf("plist[4] = %p\n", plist[4]); //plist[4]의 값 출력(할당되지 않았다)

    free(plist[0]); //plist[0]의 동적할당 해제
}