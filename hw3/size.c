#include<stdio.h>
#include<stdlib.h>

void main()
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    int **x; //정수형 이중포인터 x 선언

    printf("sizeof(x) = %lu\n", sizeof(x)); //이중포인터 x의 크기 출력
    printf("sizeof(*x) = %lu\n", sizeof(*x)); //이중포인터 x가 가리키는 곳의 크기 출력(x가 이중포인터이므로, x가 가리키는 곳도 포인터)
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //이중포인터 x가 가리키는 곳이 가리키는 곳의 크기 출력(x를 선언할 때의 타입이 int이므로, x가 가리키는 곳의 타입은 int. 따라서 4bytes.)

    //vscode가 32비트 컴파일러이므로, 포인터 변수의 크기는 4bytes
}
