#include <stdio.h>

struct student1 { //구조체 student1 선언
    char lastName; //문자형 구조체 멤버변수 lastName 선언
    int studentId; //정수형 구조체 멤버변수 studentId 선언
    char grade; //문자형 구조체 멤버변수 grade 선언
};

typedef struct { //구조체 선언(구조체 이름 생략) 
    char lastName; //문자형 구조체 멤버변수 lastName 선언
    int studentId; //정수형 구조체 멤버변수 studentId 선언
    char grade; //문자형 구조체 멤버변수 grade 선언
} student2; //구조체의 이름을 student2로 지정

int main() {

    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    struct student1 st1 = {'A', 100, 'A'}; //구조체 struct student1의 구조체 변수 st1 선언 후 초기화

    printf("st1.lastName = %c\n", st1.lastName); //구조체 st1의 lastname 'A' 출력
    printf("st1.studentId = %d\n", st1.studentId); //구조체 st1의 studentId '100' 출력
    printf("st1.grade = %c\n", st1.grade); //구조체 st1의 grade 'A' 출력

    student2 st2 = {'B', 200, 'B'}; //구조체 student2의 구조체 변수 st2 선언 후 초기화
    //구조체를 선언할 때 typedef로 구조체의 이름을 student2라고 정했기 때문에 struct를 쓰지 않아도 된다.

    printf("\nst2.lastName = %c\n", st2.lastName); //구조체 st2의 lastname 'B' 출력
    printf("st2.studentId = %d\n", st2.studentId); //구조체 st2의 studentId '200' 출력
    printf("st2.grade = %c\n", st2.grade); //구조체 st2의 grade 'B' 출력

    student2 st3; //구조체 student2의 구조체 변수 st3 선언
    
    st3 = st2; //구조체 st3에 st2를 복사

    printf("\nst3.lastName = %c\n", st3.lastName); //구조체 st3의 lastname 'B' 출력
    printf("st3.studentId = %d\n", st3.studentId); //구조체 st3의 studentId '200' 출력
    printf("st3.grade = %c\n", st3.grade); //구조체 st3의 grade 'B' 출력

    /* equality test */
    if((st3.lastName == st2.lastName) && (st3.studentId == st2.studentId) && (st3.grade == st2.grade)) //구조체 st3와 st2 비교
    //구조체를 비교할 때는 각각의 멤버 변수를 비교해야 한다.

        printf("equal\n"); //멤버 변수가 모두 같으면 같다고 출력(st3에 st2를 복사했기 때문에 둘은 같다.)
    else
        printf("not equal\n"); //멤버 변수가 하나라도 다르다면 같지 않다고 출력

    return 0;
}