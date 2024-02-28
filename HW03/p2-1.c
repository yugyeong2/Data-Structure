#include <stdio.h>

#define MAX_SIZE 100 //기호상수 최대값 100

float sum1(float list[], int);
float sum2(float *list, int);
float sum3(int n, float *list);

float input[MAX_SIZE], answer; //실수형 배열 input 전역으로 선언, 실수형 전역변수 answer 선언
int i; //정수형 전역변수 i 선언(반복문의 변수)
void main(void)
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    for(i=0; i < MAX_SIZE; i++) //100번 반복
        input[i] = i; //배열 input의 각각의 인덱스에 0~99 값 순서대로 대입
    
    /* for checking call by reference */
    //참조에 의한 호출 체크
    printf("--------------------------------------\n");
    printf(" sum1(input, MAX_SIZE) \n"); //함수 sum1
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input); //배열 input의 주소 출력(배열의 이름은 주소)

    answer = sum1(input, MAX_SIZE); //answer에 함수 sum1의 리턴값(배열 input 값의 합) 대입
    printf("The sum is: %f\n\n", answer); //answer 값 출력

    printf("--------------------------------------\n");
    printf(" sum2(input, MAX_SIZE) \n"); //함수 sum2
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input); //배열 input의 주소 출력(배열의 이름은 주소)

    answer = sum2(input, MAX_SIZE); //answer에 함수 sum2의 리턴값(배열 input 값의 합) 대입
    printf("The sum is: %f\n\n", answer); //answer 값 출력

    printf("--------------------------------------\n");
    printf(" sum3(MAX_SIZE, input) \n"); //함수 sum3
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input); //배열 input의 주소 출력(배열의 이름은 주소)

    answer = sum3(MAX_SIZE, input); //answer에 함수 sum3의 리턴값(배열 input 값의 합) 대입
    printf("The sum is: %f\n\n", answer); //answer 값 출력
}

float sum1(float list[], int n) //배열을 매개변수로 전달하여, 참조에 의한 호출을 한다.
{
    printf("list \t= %p\n", list); //list의 주소 출력(배열의 이름은 주소)
    printf("&list \t= %p\n\n", &list); //list의 주소 출력
    //list = &list

    int i; //정수형 변수 i 선언(반복문의 변수)
    float tempsum = 0; //실수형 변수 tempsum 선언 후 0으로 초기화
    for(i = 0; i < n; i++) //n(100)번 반복
        tempsum += list[i]; //tempsum = tempsum + list[i](배열 list값의 합)
    return tempsum; //list값의 합 tempsum을 리턴한다.
}

float sum2(float *list, int n) //배열의 이름은 주소이기 때문에, 포인터로 참조에 의한 호출을 한다.
{
    //printf("n\t= %p\n", &n); //n의 주소 출력
    printf("list \t= %p\n", list); //list의 주소 출력(배열의 이름은 주소)
    printf("&list \t= %p\n\n", &list); //list의 주소 출력
    //list = &list

    int i; //정수형 변수 i 선언(반복문의 변수)
    float tempsum = 0; //실수형 변수 tempsum 선언 후 0으로 초기화
    for(i = 0; i < n; i++) //n(100)번 반복
        tempsum += *(list + i); //tempsum = tempsum + *(list+i) (list의 주소에서 int의 크기만큼 i번(4byte*i) 이동한 주소의 값)
    return tempsum; //list값의 합 tempsum을 리턴한다.
}

/* stack variable reuse test */
//스택 변수 재사용 테스트
float sum3(int n, float *list) //배열의 이름은 주소이기 때문에, 포인터로 참조에 의한 호출을 한다.
{
    //printf("n\t= %p\n", &n); //n의 주소 출력
    printf("list \t= %p\n", list); //list의 주소 출력(배열의 이름은 주소)
    printf("&list \t= %p\n\n", &list); //list의 주소 출력

    int i; //정수형 변수 i 선언(반복문의 변수)
    float tempsum = 0; //실수형 변수 tempsum 선언 후 0으로 초기화
    for(i = 0; i < n; i++) //n(100)번 반복
        tempsum += *(list + i); //tempsum = tempsum + *(list+i) (list의 주소에서 int의 크기만큼 i번 (4byte*i)만큼 이동한 주소의 값)
    return tempsum; //list값의 합 tempsum을 리턴한다.
}

// sum1과 sum2의 &list의 값이 다른 이유는 매개변수 list와 n의 순서가 다르기 때문이다.
// sum2에서는 스택에 list가 먼저 쌓이고, n이 쌓인다. sum2 함수가 끝나면서 list와 n에 할당되었던 공간이 해제된다.
// sum3에서는 스택에 n이 먼저 쌓이고, list가 쌓인다. 그 과정에서 sum2에 사용되었던 스택의 메모리 공간이 재사용되고 n과 list의 순서가 교체되게 된다.
// 따라서 메모리에 올라가는 순서가 다르기 때문에, &list의 주소가 4bytes만큼 차이가 난다.
// <sum2> n = 0061FF04, &list = 0061FF00
// <sum3> n = 0061FF00, &list = 0061FF04