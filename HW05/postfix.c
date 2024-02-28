/* postfix.c
 *
 * Data Structures, Homework #5
 * School of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //스택의 크기 10
#define MAX_EXPRESSION_SIZE 20 //수식의 크기 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7, /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5, /* + 덧셈 */
    minus = 4, /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence; //enum의 새로운 이름을 precedence로 치환

char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE]; /* postfix로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE]; /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1; /* evalStack용 top */

int evalResult = 0; /* 계산 결과를 저장 */

void postfixpush(char x); //postfixStack에 값을 push하는 함수
char postfixPop();//postfixStack에서 값을 pop하는 함수
void evalPush(int x); //evalStack에 값을 push하는 함수
int evalPop(); //evalStack에서 값을 pop하는 함수
void getInfix(); //infixExp에 수식을 입력하는 함수
precedence getToken(char symbol); //infix에서 읽어온 symbol을 판별하는 함수
precedence getPriority(char x); //getToken 함수로 enum타입의 우선순위를 반환하는 함수
void charCat(char* c); //postfixExp에 문자를 저장하는 함수
void toPostfix(); //Infix를 Postfix로 변환하는 함수
void debug(); //디버그: Infix, Postfix, Evaluation, 스택 상태를 보여주는 함수
void reset(); //프로그램을 리셋하는 함수
void evaluation(); //Postfix 값을 스택을 이용해 계산하여, 실제 값이 얼마인지 보여주는 함수

int main()
{
    printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

    char command; //사용자가 입력하는 문자를 저장할 변수 command

    do{
        printf("----------------------------------------------------------------\n");
        printf(" Infix to Postfix, then Evaluation\n"); //Infix를 Postfix로 바꾸고, 계산
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");
        printf("----------------------------------------------------------------\n");
        
        printf("Command = ");
        scanf(" %c", &command); //command 입력

        switch(command) {
        case 'i': case 'I': //대소문자 I를 입력할 경우,
            getInfix(); //infix 수식 입력
            break; //switch 탈출
        case 'p': case 'P': //대소문자 P를 입력할 경우,
            toPostfix(); //Infix를 Postfix로 변환
            break; //switch 탈출
        case 'e': case 'E': //대소문자 E를 입력할 경우,
            evaluation(); //Postfix 값을 스택을 이용해 계산하여, 실제 값이 얼마인지 보여준다.
            break; //switch 탈출
        case 'd': case 'D': //대소문자 D를 입력할 경우,
            debug(); //디버그: Infix, Postfix, Evaluation, 스택 상태를 보여준다.
            break; //switch 탈출
        case 'r': case 'R': //대소문자 R을 입력할 경우,
            reset(); //프로그램 리셋
            break; //switch 탈출
        case 'q': case 'Q': //대소문자 Q를 입력할 경우,
            break; //switch 탈출
        default: //지정된 command가 아닌 다른 값을 입력할 경우,
            printf("\n >>>>> Concentration!! <<<<<\n"); //집중!!
            break; //switch 탈출
        }
    }while(command != 'q' && command != 'Q'); //대소문자 Q를 입력하면 반복문 종료

    return 1; //프로그램 종료
}

void postfixPush(char x) //postfixStack에 값을 push하는 함수
{
    postfixStack[++postfixStackTop] = x; //postfix 스택의 top을 증가시키고 그곳에 x를 push한다.
}

char postfixPop()//postfixStack에서 값을 pop하는 함수
{
    char x; //pop할 값 x
    if(postfixStackTop == -1) //stack의 top이 -1이면(stack이 비어있다)
        return '\0'; //null문자 반환
    else { //stack의 top이 -1이 아니면(stack이 비어있지 않다)
        x = postfixStack[postfixStackTop--]; //postfixStack의 top이 가리키는 값을 x에 저장 후 top 하나 감소
    }
    return x; //pop한 값 반환
}

void evalPush(int x) //evalStack에 값을 push하는 함수
{
   evalStack[++evalStackTop] = x; //evalfix 스택의 top을 증가시키고 그곳에 x를 push한다.
}

int evalPop() //evalStack에서 값을 pop하는 함수
{
    if(evalStackTop == -1) //evalStack의 top이 -1이면(stack이 비어있다)
    return -1; //함수 종료
    else //evalStack의 top이 -1이 아니면(stack이 비어있지 않다)
    return evalStack[evalStackTop--]; //evalStack의 top이 가리키는 값을 반환하고 top 하나 감소
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix() //infixExp에 수식을 입력하는 함수
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //infix 수식 입력
}

precedence getToken(char symbol) //infixExp에서 읽어온 symbol을 판별하는 함수
{
    switch(symbol) {
    case '(' : return lparen; //왼쪽 괄호 => lparen(0) 반환
    case ')' : return rparen; //오른쪽 괄호 =>  rparen(9) 반환
    case '+' : return plus; //덧셈 기호 =>  plus(5) 반환
    case '-' : return minus; //뺄셈 기호 => minus(4) 반환
    case '/' : return divide; //나눗셈 기호 => divide(6) 반환
    case '*' : return times; //곱셈 기호 => times(7) 반환
    default : return operand; // 지정된 기호가 아니라면 피연산자 operand(1) 반환
    }
}

precedence getPriority(char x) //getToken 함수로 enum타입의 우선순위를 반환하는 함수
{
    return getToken(x); //우선순위 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) //postfixExp에 문자를 저장하는 함수
{
    if (postfixExp == '\0') //postfixExp가 비어있다면
    strncpy(postfixExp, c, 1); //c를 postfixExp에 복사한다.
    else //postfixExp가 비어있지 않다면
    strncat(postfixExp, c, 1); //c를 postfixExp의 뒤에 이어붙인다.
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() //Infix를 Postfix로 변환하는 함수
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp; //입력받은 infix 수식의 주소를 exp 포인터에 저장
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */

    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
        while(*exp != '\0') //exp가 infix 수식이 끝날 때까지 반복
        {
        if(getPriority(*exp) == operand) { //읽어온 문자 exp가 피연산자이면
            x = *exp; //x에 피연산자 저장
            charCat(&x); //postfixExp에 피연산자 저장
        }
        else if(getPriority(*exp) == lparen) { //읽어온 문자 exp가 왼쪽 괄호이면
            postfixPush(*exp); //postfixStack에 exp를 push
        }
        else if(getPriority(*exp) == rparen) { //읽어온 문자 exp가 오른쪽 괄호이면
            while((x = postfixPop()) != '(') { //postfixStack에서 pop한 값이 왼쪽 괄호가 나올 때까지
                charCat(&x); //postfixExp에 피연산자 저장
            }
        }
        else { //읽어온 문자 exp가 괄호가 아닌 연산자이면
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) {
            //읽어온 문자 exp보다 postfixStack에 저장한 값이 더 크면 반복
                x = postfixPop(); //x에 postfixStack에서 pop한 값 저장
                charCat(&x); //postfixExp에 연산자 저장
            }
            postfixPush(*exp); //읽어온 문자 exp를 postfixStack에 push한다.
        }
        exp++; //exp 증가(다음 문자로)
    }
    while(postfixStackTop != -1) { //postfixStack의 top이 -1이 아니면 반복(stack이 비어있지 않으면)
        x = postfixPop(); //x에 postfixStack에서 pop한 값 저장
        charCat(&x); // //postfixExp에 pop한 값 저장
    }
}

void debug() //디버그: Infix, Postfix, Evaluation, 스택 상태를 보여주는 함수
{
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp); //Infix 수식 출력
    printf("postExp = %s\n", postfixExp); //Postfix 수식 출력
    printf("eval result = %d\n", evalResult); //Evaluation 결과 출력

    printf("postfixStack : ");
    for(int i = 0; i < MAX_STACK_SIZE; i++) //스택의 크기만큼 반복
        printf("%c ", postfixStack[i]); //스택 값 출력
    
    printf("\n"); //줄바꿈
}

void reset() //프로그램을 리셋하는 함수
{
    infixExp[0] = '\0'; //infixExp 초기화
    postfixExp[0] = '\0'; //postfixExp 초기화

    for(int i = 0; i < MAX_STACK_SIZE; i++) //스택의 크기만큼 반복
        postfixStack[i] = '\0'; //postfixStack 초기화

    postfixStackTop = -1; //postfixStack의 top 초기화
    evalStackTop = -1; //evalStack의 top 초기화
    evalResult = 0; //evalResult 값 초기화
}

void evaluation() //Postfix 값을 스택을 이용해 계산하여, 실제 값이 얼마인지 보여주는 함수
{
    int opr1, opr2, i;

    int length = strlen(postfixExp); //postfixExp의 길이
    char symbol;
    evalStackTop = -1; //evalStack의 top 초기화

    for(i = 0; i < length; i++) //postfixExp의 길이만큼 반복
    {
        symbol = postfixExp[i]; //postfixExp에 저장된 값을 symbol에 저장
        if(getToken(symbol) == operand) { //postfixExp에서 읽어온 symbol이 피연산자이면
            evalPush(symbol - '0'); //symbol에서 0의 아스키코드 값만큼 뺀 값을 evalStack에 push한다.
        }
        else {//postfixExp에서 읽어온 symbol이 연산자이면
            opr2 = evalPop(); //evalStack에서 pop한 값을 opr2에 저장
            opr1 = evalPop(); //evalStack에서 pop한 값을 opr1에 저장
            switch(getToken(symbol)) {
            case plus: evalPush(opr1 + opr2); break; //symbol이 plus(5)이면 opr1과 opr2를 덧셈 연산한다.
            case minus: evalPush(opr1 - opr2); break; //symbol이 minus(4)이면 opr1과 opr2를 뺄셈 연산한다.
            case times: evalPush(opr1 * opr2); break; //symbol이 times(7)이면 opr1과 opr2를 곱셈 연산한다.
            case divide: evalPush(opr1 / opr2); break; //symbol이 divide(6)이면 opr1과 opr2를 나눗셈 연산한다.
            default: break; //symbol이 지정된 연산자가 아니면 반복문 멈춘다
            }
        }
    }
    evalResult = evalPop(); //evalStack에서 pop한 값을 계산 결과에 저장한다.
}