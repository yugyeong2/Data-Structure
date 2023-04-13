#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void allocation_matrix(int*** X, int row, int col); //동적할당
void random_matrix(int** X, int row, int col); //랜덤
void print_matrix(int** X, int row, int col); //출력
void addition_matrix(int** X, int** Y, int** re, int row, int col); //덧셈
void subtraction_matrix(int** X, int** Y, int** re, int row, int col); //뺄셈
void transpose_matrix(int** X, int** re, int row, int col); //전치
void multiply_matrix(int** X, int** Y, int** re, int A_row, int A_col, int B_row, int B_col); //곱셈
void free_matrix(int** X, int row); //메모리 해제

int main() {
    printf(" [----- [Park Yugyeong] [2022041028] -----]\n\n");

    srand((unsigned)time(NULL)); //랜덤

    int A_row, A_col; //A의 행 row, 열 col 값
    int B_row, B_col; //B의 행 row, 열 col 값
    int** A = NULL, ** B = NULL; //행렬 A, B
    int** Add_Matrix = NULL; //A+B
    int** Subtract_Matrix = NULL; //A-B
    int** Transpose_matrix = NULL; //전치행렬 T
    int** Multiply_Matrix = NULL; //AxB

//• 행렬의 행(row)과 열(column)의 값을 입력 받는다. (scanf() 사용)
    printf("A row col: ");
    scanf("%d%d", &A_row, &A_col);
    printf("B row col: ");
    scanf("%d%d", &B_row, &B_col);
    printf("\n");

//• 모든 행렬은 동적 메모리할당(dynamic memory allocation) 방식으로 생성한다.
    allocation_matrix(&A, A_row, A_col);
    random_matrix(A, A_row, A_col); //행렬 랜덤 값 배정

    allocation_matrix(&B, B_row, B_col);
    random_matrix(B, B_row, B_col); //행렬 랜덤 값 배정

//• Print Matrix - A와 B 행렬을 출력한다. (print matrix() 사용)
    printf("A Matrix\n");
    print_matrix(A, A_row, A_col);
    printf("B Matrix\n");
    print_matrix(B, B_row, B_col);

//• Add Matrix - A + B를 구현한다. (함수: addition matrix())

    if(A_row==B_row && A_col==B_col) { //A와 B의 행과 열의 크기가 같을 때,
        pirntf("A+B\n");
        allocation_matrix(&Add_Matrix, A_row, A_col); //동적할당
        addition_matrix(A, B, Add_Matrix, A_row, A_col);
        print_matrix(Add_Matrix, A_row, A_col); //A+B 출력
        //A와 B의 행과 열의 크기가 같기 때문에 어느 행렬의 크기 중 어느 것도 상관없다.
    }
    else {
        printf("Row and column sizes for A and B are not the same.\n\n");
        //A, B의 행과 열의 크기가 같지 않습니다.
    }


//• Subtract Matrix - A − B를 구현한다. (함수: subtraction matrix())
    if(A_row==B_row && A_col==B_col) { //A와 B의 행과 열이 같을 때,
        printf("A-B\n");
        allocation_matrix(&Subtract_Matrix, A_row, A_col); //동적할당
        subtraction_matrix(A, B, Subtract_Matrix, A_row, A_col);
        print_matrix(Subtract_Matrix, A_row, A_col); //A-B 출력
        //A와 B의 행과 열의 크기가 같기 때문에 어느 행렬의 크기 중 어느 것도 상관없다.
    }
    else {
        printf("Row and column sizes for A and B are not the same.\n\n");
        //A, B의 행과 열의 크기가 같지 않습니다.
    }

//• Transpose matrix a - A의 전치행렬 T를 구현한다. (함수: transpose matrix())
    printf("T\n");
    allocation_matrix(&Transpose_matrix, A_col, A_row); //A의 행과 열의 바꿔서 동적할당
    transpose_matrix(A, Transpose_matrix, A_col, A_row);
    print_matrix(Transpose_matrix, A_col, A_row); //A의 전치행렬 출력

//• Multiply Matrix - A × B를 구현한다. (함수: multiply matrix())
    if (A_col == B_row) {
        printf("AxB\n");
        allocation_matrix(&Multiply_Matrix, A_row, B_col); //동적할당
        multiply_matrix(A, B, Multiply_Matrix, A_row, A_col, B_row, B_col);
        print_matrix(Multiply_Matrix, A_row, B_col); //AxB 출력
    }
    else {
        printf("Columns in A and rows in B are not the same size.\n");
        //A의 열과 B의 행의 크기가 같지 않습니다.
    }

//• 연산이 종료되거나 프로그램을 종료할 때 할당했던 메모리를 해제 한다. (함수: free matrix())
    free_matrix(A, A_row);
    free_matrix(B, B_row);
    free_matrix(Add_Matrix, A_row);
    free_matrix(Subtract_Matrix, A_row);
    free_matrix(Transpose_matrix, A_row);
    free_matrix(Multiply_Matrix, B_row);

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

void random_matrix(int** X, int row, int col) { //행렬 랜덤
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            X[i][j] = rand() % 9 + 1;
        }
    }
}

void print_matrix(int** X, int row, int col) { //행렬 출력
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%d ", X[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void addition_matrix(int** X, int** Y, int** re, int row, int col) { //행렬 덧셈
    printf("Addition_matri: \n");
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            re[i][j] = X[i][j] + Y[i][j];
        }
    }
}

void subtraction_matrix(int** X, int** Y, int** re, int row, int col) { //행렬 뺄셈
    printf("Subtraction_matrix: \n");
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            re[i][j] = X[i][j] - Y[i][j];
        }
    }
}

void transpose_matrix(int** X, int** re, int row, int col) { //전치행렬
    printf("Transpose_matrix: \n");
    for(int i = 0; i < row; i++) { //row = A_col
        for(int j = 0; j < col; j++) { //col = A_row
            re[i][j] = X[j][i];
        }
    }
}

void multiply_matrix(int** X, int** Y, int** re, int A_row, int A_col, int B_row, int B_col) { //행렬 곱
    printf("Multiply_Matrix: \n");

    //행렬 곱
    for(int i = 0; i < A_row; i++) {
        for(int j = 0; j < B_col; j++) {
            re[i][j] = 0; //0으로 초기화
            
            for(int k = 0; k < A_col; k++) {
                re[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
}

void free_matrix(int** X, int row) { //메모리 해제
    for (int i = 0; i < row; i++) {
        free(X[i]);
    }
    free(X);
}