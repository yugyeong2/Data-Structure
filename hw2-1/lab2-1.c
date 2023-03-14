#include <stdio.h>

void Yugyeong() {
    printf("----- [Park Yugyeong]  2022041028 -----]\n\n\n");
}

int main() {

    Yugyeong();

    char charType; //문자형 변수 charType
    int integerType; //정수형 변수 integerType
    float floatType; //실수형 변수 floatType
    double doubleType; //실수형 변수 doubleType

    printf("Size of char: %ld byte\n", sizeof(charType)); //charType는 char형이므로 char형의 크기는 1byte이다.
    printf("Size of int: %ld bytes\n", sizeof(integerType)); //integerType는 int형이므로 int형의 크기는 4byte이다.
    printf("Size of float: %ld bytes\n", sizeof(floatType)); //floatType는 float형이므로 float형의 크기는 4byte이다.
    printf("Size of double: %ld bytes\n", sizeof(doubleType)); //doubleType는 double형이므로 double형의 크기는 8byte이다.

    printf("-----------------------------------------\n");

    printf("Size of char: %ld byte\n", sizeof(char)); //char형의 크기는 1byte이다.
    printf("Size of int: %ld bytes\n", sizeof(int)); //int형의 크기는 4byte이다.
    printf("Size of float: %ld bytes\n", sizeof(float)); //float형의 크기는 4byte이다.
    printf("Size of double: %ld bytes\n", sizeof(double)); //double형의 크기는 8byte이다.

    printf("-----------------------------------------\n");

    printf("Size of char*: %ld byte\n", sizeof(char*)); //Visual Studio Code의 컴파일러가 32bit체계이므로 포인터의 자료형의 크기는 4byte이다. 따라서 char*도 4byte이다.
    printf("Size of int*: %ld bytes\n", sizeof(int*)); //포인터의 자료형의 크기는 4byte이므로 int*도 4byte이다.
    printf("Size of float*: %ld bytes\n", sizeof(float*)); //포인터의 자료형의 크기는 4byte이므로 float*도 4byte이다.
    printf("Size of double*: %ld bytes\n", sizeof(double*)); //포인터의 자료형의 크기는 4byte이므로 double*도 4byte이다.

    return 0;
}
