/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 크기 4

typedef char element; //char 자료형에 새로운 이름 element 선언
//큐의 값(queue/data)과 함수 명령키(command)를 각각 char형과 element형으로 구별하여 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //크기가 4인 element(char)형의 큐 선언
	int front, rear; //큐의 첫번재 원소의 하나 앞 fornt, 큐의 끝 rear
}QueueType; //구조체의 새로운 이름 QueueType 선언

QueueType *createQueue(); //구조체 포인터형 함수 createQueue, 큐를 생성하는 함수
int freeQueue(QueueType *cQ); //큐의 메모리를 해제하는 함수
int isEmpty(QueueType *cQ); //큐가 비어있는지 검사하는 함수
int isFull(QueueType *cQ); //큐가 모두 차있는지 검사하는 함수
void enQueue(QueueType *cQ, element item); //큐에 삽입할 data를 입력받는 함수
void deQueue(QueueType *cQ, element* item); //큐에 삽입되어있는 data를 삭제하는 함수(실제 값 삭제x, front의 위치 이동)
void printQ(QueueType *cQ); //큐의 data를 출력하는 함수
void debugQ(QueueType *cQ);  //큐의 front와 rear의 위치 출력하고 큐의 상태를 확인하는 함수(디버그)
element getElement(); //큐에 삽입될 data를 입력받는 함수

int main(void)
{
    printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

	QueueType *cQ = createQueue(); //구조체 포인터 cQ
    //creatQueue에서 생성한 cQ의 주소를 main의 cQ에 전달한다.(createQueue의 cQ는 지역이기 때문에 소멸)
	element data; //element(char)형 변수 data 선언
	char command; //char형 변수 command 선언
    //data: 큐의 데이터 값, command: 함수를 실행하는 명령키

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command 입력

		switch(command) { //command 값에 따라 조건 제어
		case 'i': case 'I': /* i/I 입력할 경우, */
			data = getElement(); //큐에 입력할 data를 입력받아 data에 저장
			enQueue(cQ, data); //큐에 data 삽입
			break; //switch 탈출

		case 'd': case 'D': /* d/D 입력할 경우 */
			deQueue(cQ, &data); //큐에서 data 삭제
			break; //switch 탈출

		case 'p': case 'P': /* p/P 입력할 경우 */
			printQ(cQ); //큐 출력
			break; //switch 탈출

		case 'b': case 'B': /* b/B 입력할 경우 */
			debugQ(cQ); //큐 디버깅
			break; //switch 탈출

		case 'q': case 'Q': /* q/Q 입력할 경우 */
   	        freeQueue(cQ); //큐 해제
			break; //switch 탈출

		default: //정해진 command가 아닐 경우, 집중!!
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; //switch 탈출
		}

	}while(command != 'q' && command != 'Q'); /* q/Q를 입력할 경우 반복문 탈출 */

	return 1; //프로그램 종료
}

QueueType *createQueue() //큐 생성
{
	QueueType *cQ; //구조체 포인터 cQ
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ가 가리키는 곳에 구조체 QueueType만큼 동적할당
	cQ->front = 0; //cQ의 front를 0으로 초기화
	cQ->rear = 0; //cQ의 rear를 0으로 초기화
	return cQ; //cQ의 값(주소) 리턴
}

int freeQueue(QueueType *cQ) //큐 메모리 해제
{
    if(cQ == NULL) return 1; //cQ가 NULL(cQ가 가리키는 값x, cQ 생성x)이면, 함수 종료
    free(cQ); //cQ에 할당된 값이 있으면, 메모리 해제를 한다.
    return 1; //함수 종료
}

element getElement() //큐의 data를 입력
{
	element item; //element(char)형 변수 item
	printf("Input element = ");
	scanf(" %c", &item); //큐에 삽입될 item 입력
	return item; //item값 리턴
}

/* complete the function */
int isEmpty(QueueType *cQ) //큐 empty 검사
{
    if(cQ->front == cQ->rear) { //queue가 비어있다면,
	//front의 위치와 rear의 위치가 같다면
		printf("Circular Queue is empty\n");
        return 1; //1(true) 리턴
    }
    else { //queue가 비어있지 않다면,
        return 0; //0(false) 리턴
    }
}

/* complete the function */
int isFull(QueueType *cQ) //큐 full 검사
{
    if(cQ->front == ((cQ->rear+1) % MAX_QUEUE_SIZE)) { //queue가 모두 차있다면,
	//front의 위치와 rear의 위치(모듈러 연산)가 같다면
	//원형큐이기 때문에 rear가 큐의 크기를 넘어서면, 다시 0부터 시작한다(rear[MAX_QUEUE_SIZE] -> rear[0])
		printf("Circular Queue is full\n");
        return 1; //1(true) 리턴
    }
    else { //queue가 모두 차있지 않다면,
        return 0; //0(false) 리턴
    }
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //큐 data 삽입
{
	if(isFull(cQ)) { //큐가 full이면,
		return; //함수 종료
	}
	else { //큐가 full이 아니라면,
		cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE; //rear 위치 하나 증가(모듈러 연산)
		//원형큐이기 때문에 rear가 큐의 크기를 넘어서면, 다시 0부터 시작한다(rear[MAX_QUEUE_SIZE] -> rear[0])
		cQ->queue[cQ->rear] = item;// 큐의 끝(rear의 위치)에 item 삽입		
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) //큐 data 삭제
//enQueue 과정에서 새로운 data가 삽입되면 이전 data가 삭제되기 때문에,
//deQueue 과정에서 실제 큐의 data를 삭제하지 않고, 삭제된 data에 접근하지 못하도록 front의 위치를 증가한다.
{
    if(isEmpty(cQ)) { //큐가 empty라면,
		return ; //함수 종료
    }
	else { //큐가 empty가 아니라면,
		cQ->front = (cQ->front+1) % MAX_QUEUE_SIZE; //front의 위치 하나 증가(모듈러 연산)
		//원형큐이기 때문에 front가 큐의 크기를 넘어서면, 다시 0부터 시작한다(front[MAX_QUEUE_SIZE] -> rear[0])
	}
}

void printQ(QueueType *cQ) //큐 출력
{
	int i, first, last; //반복문의 변수 i, front의 위치를 저장할 변수 first, rear의 위치를 저장할 변수 last 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //모듈러 연산으로 front가 가리키는 원소의 위치 계산하여 first에 저장
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //모듈러 연산으로 rear가 가리키는 원소의 위치 계산하여 last에 저장

	printf("Circular Queue : [");

	i = first; //반복문에 사용될 i에 first 값 대입
	while(i != last){ //first(front)부터 last(rear)까지 반복
		printf("%3c", cQ->queue[i]); //큐의 i번째 원소 출력
		i = (i+1)%MAX_QUEUE_SIZE; // //i값 증가(모듈러 연산으로 배열의 크기를 넘어서면 0부터 다시 시작)

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //디버그(front, rear 위치 확인)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //큐의 크기만큼 반복
	{
		if(i == cQ->front) { //만약 i가 front와 같다면,
			printf("  [%d] = front\n", i); //front에 해당하는 i값 출력
			continue; //아래 코드를 실행하지 않고 반복문 계속
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //front가 아닌 큐의 i와 data 출력
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 값 출력
}