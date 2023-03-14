#include <stdio.h>

void Yugyeong() {
    printf("----- [Park Yugyeong]  2022041028 -----]\n\n\n");
}

int main()
{   
    Yugyeong();

    int i; //정수형 변수 i 선언
    int *ptr; //정수형 포인터 변수 ptr 선언
    int **dptr; //정수형 이중 포인터 변수 dptr 선언

    i = 1234; //i에 1234 대입

    printf("[checking values before ptr = &i] \n"); //[ptr에 i의 주소를 대입하기 전 값 확인]
    printf("value of i == %d\n", i); //정수형 변수 i의 값 1234 출력
    printf("address of i == %p\n", &i); //정수형 변수 i의 주소 출력
    printf("value of ptr == %p\n", ptr); //포인터 변수 ptr의 값 출력 (ptr은 현재 아무것도 가리키고 있지 않다.)
    printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소 출력

    ptr = &i; //ptr is now holding the address of i -> 포인터 변수 prt에 i의 주소 대입 (ptr은 현재 i를 가리킨다.)

    printf("\n[checking values after ptr = &i] \n"); //[ptr에 i의 주소를 대입한 후 값 확인]
    printf("value of i == %d\n", i); //정수형 변수 i의 값 1234 출력
    printf("address of i == %p\n", &i); //정수형 변수 i의 주소 출력
    printf("value of ptr == %p\n", ptr); //포인터 변수 ptr의 값 출력 (ptr이 가리키는 i의 주소 출력)
    printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소 출력
    printf("value of *ptr == %d\n", *ptr); //포인터 변수 ptr이 가리키는 i의 값 1234 출력
 
    dptr = &ptr; // dptr is now holding the address of ptr -> 이중 포인터 dptr에 prt의 주소 대입 (dptr은 현재 ptr을 가리킨다.)

    printf("\n[checking values after dptr = &ptr] \n"); //[dptr에 ptr의 주소를 대입한 후 값 확인]
    printf("value of i == %d\n", i); //정수형 변수 i의 값 1234 출력
    printf("address of i == %p\n", &i); //정수형 변수 i의 주소 출력
    printf("value of ptr == %p\n", ptr); //포인터 변수 ptr의 값 출력 (ptr이 가리키는 i의 주소 출력)
    printf("address of ptr == %p\n", &ptr); //포인터 변수 ptr의 주소 출력
    printf("value of *ptr == %d\n", *ptr); //포인터 변수 ptr이 가리키는 i의 값 1234 출력
    printf("value of dptr == %p\n", dptr); //포인터 변수 dptr의 값 출력 (dptr이 가리키는 ptr의 주소 출력)
    printf("address of dptr == %p\n", &dptr); //포인터 변수 dptr의 주소 출력
    printf("value of *dptr == %p\n", *dptr); //포인터 변수 dptr이 가리키는, ptr의 값 출력 (즉 i의 주소 출력)
    printf("value of **dptr == %d\n", **dptr); //포인터 변수 dptr이 가리키는, ptr이 가리키는, i의 값 1234 출력

    *ptr = 7777; //changing the value of *ptr -> 포인터 ptr이 가리키는 i의 값에 7777로 변경

    printf("\n[after *ptr = 7777] \n"); //[포인터 ptr의 값을 7777변경한 후]
    printf("value of i == %d\n", i); //정수형 변수 i의 값 7777 출력
    printf("value of *ptr == %d\n", *ptr); //포인터 변수 ptr이 가리키는 i의 값 7777 출력
    printf("value of **dptr == %d\n", **dptr); //포인터 변수 dptr이 가리키는, ptr이 가리키는, i의 값 7777출력

    **dptr = 8888; // changing the value of **dptr -> 포인터 변수 dptr이 가리키는, ptr이 가리키는, i의 값에 8888을 대입

    printf("\n[after **dptr = 8888] \n"); //[이중포인터 dptr의 값을 8888로 변경한 후]
    printf("value of i == %d\n", i); //정수형 변수 i의 값 8888 출력
    printf("value of *ptr == %d\n", *ptr); //포인터 변수 ptr이 가리키는 i의 값 8888 출력
    printf("value of **dptr == %d\n", **dptr); //포인터 변수 dptr이 가리키는, ptr이 가리키는, i의 값 8888 출력

    return 0;
}