#include <stdio.h>

void print_one(int *ptr, int rows); //배열의 주소와 값을 출력하는 함수

int main()
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    int one[] = {0, 1, 2, 3, 4}; //정수형 배열 one선언 후 0~4로 초기화(배열의 크기는 5)
    printf("one = %p\n", one); //배열 one의 주소 출력(배열의 이름은 주소)
    printf("&one = %p\n", &one); //배열 one의 주소 출력
    printf("&one[0] = %p\n", &one[0]); //배열 one[0]의 주소 출력 
    printf("\n"); //줄바꿈

    printf("------------------------------------\n");
    printf(" print_one(&one[0], 5) \n");
    printf("------------------------------------\n");
    print_one(&one[0], 5); //print_one함수 호출(매개변수 배열 one의 0번째 인덱스의 주소, 5(배열의 크기))

    printf("------------------------------------\n");
    printf(" print_one(one, 5) \n");
    printf("------------------------------------\n");
    print_one(one, 5); //print_one함수 호출(매개변수 배열 one의 주소(배열의 이름은 주소), 5(배열의 크기))

    //&one[0] = one

    return 0;
}

void print_one(int *ptr, int rows) //배열의 주소와 값을 출력하는 함수
{/* print out a one-dimensional array using a pointer */
//포인터를 사용하여 1차원 배열 출력

    int i; //정수형 변수 i 선언(반복문의 변수)
    printf ("Address \t Contents\n"); //주소, 값
    for (i = 0; i < rows; i++) //rows(5)번 반복
        printf("%p \t %5d\n", ptr + i, *(ptr + i)); //ptr의 주소에서 int의 크기만큼 i번(4bytes*i) 이동한 주소, 값 출력 
    printf("\n"); //줄바꿈
}
