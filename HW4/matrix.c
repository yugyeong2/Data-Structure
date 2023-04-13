#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void allocation_matrix(int*** X, int row, int col); //행렬을 행과 열로 동적할당
void random_matrix(int** X, int row, int col); //행렬에 랜덤 값 저장
void print_matrix(int** X, int row, int col); //출력
void addition_matrix(int** X, int** Y, int** re, int row, int col); //행렬의 덧셈
void subtraction_matrix(int** X, int** Y, int** re, int row, int col); //행렬의 뺄셈
void transpose_matrix(int** X, int** re, int row, int col); //전치행렬
void multiply_matrix(int** X, int** Y, int** re, int m, int n, int p); //행렬의 곱
void free_matrix(int** X, int row); //메모리 해제

int main() {
    printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

    srand((unsigned)time(NULL)); //난수 생성

    int A_row, A_col; //A의 행(row), 열(col)의 크기 변수
    int B_row, B_col; //B의 행(row), 열(col)의 크기 변수
    int** A = NULL, ** B = NULL; //행렬 A, B를 저장할 포인터 변수
    int** Add_Matrix = NULL; //행렬의 덧셈(A+B)을 저장할 포인터 변수
    int** Subtract_Matrix = NULL; //행렬의 뺄셈(A-B)을 저장할 포인터 변수
    int** Transpose_Matrix = NULL; //A의 전치행렬 T를 저장할 포인터 변수
    int** Multiply_Matrix = NULL; //행렬의 곱(AxB)을 저장할 포인터 변수

//• 행렬의 행(row)과 열(column)의 값을 입력 받는다. (scanf() 사용)
    printf("A row col: ");
    scanf("%d%d", &A_row, &A_col); //A의 행과 열 입력
    printf("B row col: ");
    scanf("%d%d", &B_row, &B_col); //B의 행과 열 입력
    printf("\n");

//• 모든 행렬은 동적 메모리할당(dynamic memory allocation) 방식으로 생성한다.
    allocation_matrix(&A, A_row, A_col); //A를 행과 열로 동적할당
    random_matrix(A, A_row, A_col); //A 행렬에 랜덤 값 배정

    allocation_matrix(&B, B_row, B_col); //B를 행과 열로 동적할당
    random_matrix(B, B_row, B_col); //A 행렬에 랜덤 값 배정

//• Print Matrix - A와 B 행렬을 출력한다. (print matrix() 사용)
    printf("A\n");
    print_matrix(A, A_row, A_col); //A 출력
    printf("B\n");
    print_matrix(B, B_row, B_col); //B 출력

//• Add Matrix - A + B를 구현한다. (함수: addition matrix())
    printf("A+B\n");
    if(A_row==B_row && A_col==B_col) { //A와 B의 행과 열의 크기가 같을 때,
        //A와 B의 행과 열의 크기가 같기 때문에, A와 B 중 어느 행렬의 크기를 넘겨줘도 상관없다.
        allocation_matrix(&Add_Matrix, A_row, A_col); //A+B를 받을 행렬 Add_Matrix 동적할당
        addition_matrix(A, B, Add_Matrix, A_row, A_col); //addition_matrix 함수 호출
        print_matrix(Add_Matrix, A_row, A_col); //A+B 출력
    }
    else { //A와 B의 행과 열의 크기가 같지 않을 때,
        printf("Row and column sizes for A and B are not the same.\n\n");
        //A, B의 행과 열의 크기가 같지 않습니다.
    }


//• Subtract Matrix - A − B를 구현한다. (함수: subtraction matrix())
    printf("A-B\n");
    if(A_row==B_row && A_col==B_col) { //A와 B의 행과 열이 같을 때,
        //A와 B의 행과 열의 크기가 같기 때문에, A와 B 중 어느 행렬의 크기를 넘겨줘도 상관없다.
        allocation_matrix(&Subtract_Matrix, A_row, A_col); //A-B를 받을 행렬 Subtract_Matrix 동적할당
        subtraction_matrix(A, B, Subtract_Matrix, A_row, A_col); //subtraction_matrix 함수 호출
        print_matrix(Subtract_Matrix, A_row, A_col); //A-B 출력
    }
    else { //A와 B의 행과 열이 같지 않을 때,
        printf("Row and column sizes for A and B are not the same.\n\n");
        //A, B의 행과 열의 크기가 같지 않습니다.
    }

//• Transpose matrix a - A의 전치행렬 T를 구현한다. (함수: transpose matrix())
    printf("T of A\n");
    allocation_matrix(&Transpose_Matrix, A_col, A_row); //A의 전지행렬을 받을 행렬 Transpose_Matrix 동적할당
    //A의 행과 열의 크기를 바꿔서 매개변수 전달
    transpose_matrix(A, Transpose_Matrix, A_col, A_row); //transpose_Matrix 함수 호출
    print_matrix(Transpose_Matrix, A_col, A_row); //A의 전치행렬 출력

//• Multiply Matrix - A × B를 구현한다. (함수: multiply matrix())
    printf("AxB\n");
    if (A_col == B_row) { //A의 열과 B의 행의 크기가 같을 때,
        allocation_matrix(&Multiply_Matrix, A_row, B_col); //AxB를 받을 행렬 동적할당 Multiply_Matrix 동적할당
        //A(mxn) B(nxp) = Multiply_Matrix(mxp)
        //A의 열과 B의 행의 크기가 같기 때문에, 둘 중 어느 것을 넘겨줘도 상관없다.
        multiply_matrix(A, B, Multiply_Matrix, A_row, A_col, B_col); //multiply_matrix 함수 호출
        print_matrix(Multiply_Matrix, A_row, B_col); //AxB 출력
    }
    else { //A의 열과 B의 행의 크기가 같지 않을 때,
        printf("Columns in A and rows in B are not the same size.\n");
        //A의 열과 B의 행의 크기가 같지 않습니다.
    }

//• 연산이 종료되거나 프로그램을 종료할 때 할당했던 메모리를 해제 한다. (함수: free matrix())
    free_matrix(A, A_row); //A 동적 메모리 해제
    free_matrix(B, B_row); //B 동적 메모리 해제
    free_matrix(Add_Matrix, A_row); //Add_Matrix 동적 메모리 해제
    free_matrix(Subtract_Matrix, A_row); //Subtract_Matrix 동적 메모리 해제
    free_matrix(Transpose_Matrix, A_row); //Transpose_Matrix 동적 메모리 해제
    free_matrix(Multiply_Matrix, B_row); //Multiply_Matrix 동적 메모리 해제

    return 0;
}

void allocation_matrix(int*** X, int row, int col) { //행렬 동적할당
    //row만큼 동적할당
    *X = (int**)malloc(sizeof(int*) * row);

    //col만큼 동적할당
    for(int i = 0; i < row; i++) {
        (*X)[i] = (int*)malloc(sizeof(int) * col);
    }
}

void random_matrix(int** X, int row, int col) { //행렬 랜덤 값 저장
    for(int i = 0; i < row; i++) { //행
        for(int j = 0; j < col; j++) { //열
            X[i][j] = rand() % 9 + 1; //1~9까지의 값 랜덤 저장
        }
    }
}

void print_matrix(int** X, int row, int col) { //행렬 출력
    for(int i = 0; i < row; i++) { //행
        for(int j = 0; j < col; j++) { //열
            printf("%d ", X[i][j]); //출력
        }
        printf("\n");
    }
    printf("\n");
}

void addition_matrix(int** X, int** Y, int** re, int row, int col) { //행렬 덧셈
    for(int i = 0; i < row; i++) { //행
        for(int j = 0; j < col; j++) { //열
            re[i][j] = X[i][j] + Y[i][j]; //re(Add_Matrix) = X(A) +Y(B)
        }
    }
}

void subtraction_matrix(int** X, int** Y, int** re, int row, int col) { //행렬 뺄셈
    for(int i = 0; i < row; i++) { //행
        for(int j = 0; j < col; j++) { //열
            re[i][j] = X[i][j] - Y[i][j]; //re(Subtract_Matrix) = X(A) +Y(B)
        }
    }
}

void transpose_matrix(int** X, int** re, int row, int col) { //전치행렬
    //저장할 Transpose_Matrix에 저장할 것을 기준으로 반복문 설정
    for(int i = 0; i < row; i++) { //행 (row = A_col)
        for(int j = 0; j < col; j++) { //열 (col = A_row)
            re[i][j] = X[j][i]; //re(Transpose_Matrix)의 행 열 값 = X(A)의 열 행 값
        }
    }
}

void multiply_matrix(int** X, int** Y, int** re, int m, int n, int p) { //행렬 곱
    //A(mxn) B(nxp) = Multiply_Matrix(mxp)
    for(int i = 0; i < m; i++) { //m(A_row)
        for(int j = 0; j < p; j++) { //p(B_col)
            re[i][j] = 0; //0으로 초기화
            
            for(int k = 0; k < n; k++) { //n(A_col)
                re[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
}

void free_matrix(int** X, int row) { //메모리 해제
    //행만큼 동적 메모리 해제
    for (int i = 0; i < row; i++) {
        free(X[i]);
    }

    //나머지(열만큼) 동적 메모리 해제
    free(X);
}