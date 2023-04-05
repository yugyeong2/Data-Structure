#include <stdio.h>

struct student { //구조체 student 선언
    char lastName[13]; /* 13 bytes */
    //문자형 구조체 멤버변수로 배열 lastName 선언(char형이 배열로 13개 있으므로 13bytes)
    int studentId; /* 4 bytes */
    //정수형 구조체 멤버변수 studentId 선언(int는 4bytes)
    short grade; /* 2 bytes */
    //정수형 구조체 멤버변수 grade 선언(shrot는 2bytes)
};

int main()
{
    printf("----- [Park_Yugyeong] [2022041028] -----\n\n");

    struct student pst; //구조체 student의 구조체 변수 pst 선언

    printf("size of student = %ld\n", sizeof(struct student)); //구조체 student의 전체의 크기 출력
    // 13+4+2 = 19bytes이지만, 32bit 컴파일러에서 4bytes씩 데이터를 처리하기 때문에, 메모리를 효율적으로 사용하기 위해 4bytes 단위로 할당한다.
    // 따라서 padding으로 인해 lastName(13+3(padding)) + studentId(4) + grade(2 + 2(padding)) = 24bytes로 할당된다.
    
    printf("size of int = %ld\n", sizeof(int)); //int의 크기 출력(4bytes)
    printf("size of short = %ld\n", sizeof(short)); //short의 크기 출력(2bytes)

    return 0;
}