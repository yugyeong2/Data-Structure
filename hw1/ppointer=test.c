#include <stdio.h> //표준 입출력 라이브러리 헤더파일 포함

int main() {
	
	int i, *p; //정수형 변수 i와 포인터 변수 p

	i = 10; //i에 정수값 10을 대입

	printf("value of i = %d\n", i); //정수형 변수 i의 값을 10진수로 출력
	printf("adress of i = %p\n", &i); //i의 주소 출력
	printf("value of p = %p\n", p); //포인터 변수 p의 값 출력(p는 현재 아무것도 가리키고 있지 않음.)
	printf("address of p = %p\n", &p); //p의 주소 출력

	p = &i; //포인터 변수 p에 i의 주소 대입(p는 현재 i를 가리킴.)

	printf("\n\n----- after p = &i -----\n\n");

	printf("value of p = %p\n", p); //포인터 변수 p의 값 출력(p가 가리키는 i의 주소 출력)
	printf("address of p = %p\n", &p); //p의 주소 출력(변하지 않음.)
	printf("dereferencing *p = %d\n", *p); //포인터 변수 p의 역참조 값(포인터가 가리키는 값)을 10진수로 출력(p가 가리키는 i의 값 출력)

	return 0;
}