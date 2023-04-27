/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { //연결리스트의 노드 구조체
	int key; //노드의 data 값
	struct Node* link; //다음 노드의 주소
} listNode;

typedef struct Head { //연결리스트의 첫 번째 노드를 가리키는 헤더 구조체
	struct Node* first; //헤더가 가리키는 노드의 주소
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //헤더 노드 초기화
int freeList(headNode* h); //메모리 해제

int insertFirst(headNode* h, int key); //첫 번째에 node 삽입
int insertNode(headNode* h, int key); //key의 오름차순으로 node 삽입
int insertLast(headNode* h, int key); //마지막에 node 삽입

int deleteFirst(headNode* h); //첫 번째 node 삭제
int deleteNode(headNode* h, int key); //입력받은 key와 같은 key를 가진 노드 삭제
int deleteLast(headNode* h); //마지막 node 삭제

int invertList(headNode* h); //연결리스트 link 반전

void printList(headNode* h); //연결리스트 출력

int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");
	
	char command; //사용자가 입력할 명령어
	int key; //사용자가 입력할 노드의 data 값
	headNode* headnode=NULL; //헤더 노드

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); //intialize에서 할당한 temp의 주소를 headNode에 반환
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //key의 오름차순으로 node 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //입력받은 key와 같은 key를 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //마지막에 node 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 node 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //첫 번째에 node 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫 번째 node 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //연결리스트 link 반전
			break;
		case 'q': case 'Q':
			freeList(headnode); //메모리 해제
			break;
		default: //지정된 명령어가 아닌 다른 값이 입력되면 집중 표시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q(Q)가 입력되면 반복문 종료

	return 1;
}

headNode* initialize(headNode* h) { //헤더 노드 초기화
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL) //headNode에 쓰레기값이 남아있다면 메모리 해제
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //temp 노드를 헤더 노드로 동적 할당
	temp->first = NULL; //temp의 링크 first를 NULL로 초기화
	return temp; //temp의 주소 반환
}

int freeList(headNode* h){ //연결리스트 메모리 해제
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p

	listNode* prev = NULL; //p를 따라올 구조체 포인터 prev
	while(p != NULL) { //p가 마지막을 가리켜 더 이상 노드가 없을 때 반복문 종료
		prev = p; //prev 한 칸 뒤로
		p = p->link; //p 한 칸 뒤로
		free(prev); //prev가 가리키는 노드 메모리 해제
	}
	free(h); //헤더 노드 메모리 해제
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //node에 key값을 넣는다
	node->link = NULL; //node link 초기화

	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	listNode* trail = NULL; //p를 따라올 구조체 포인터 trail
	//p는 현재 헤더의 다음 노드를 가리킨다

	if(h->first == NULL) { //연결된 node가 하나도 없는 경우, first에 node 삽입
		h->first = node;
	}
	else { //탐색
		while(1) {
			if(p == NULL) { //p의 탐색이 끝나 마지막을 가리키는 경우, 마지막에 node 삽입
				trail->link = node;
				break;
			}
			if (p->key > node->key) { //p가 탐색한 key > 입력받은 key
				if(p == h->first) { //p가 탐색한 위치가 헤드의 위치인 경우, 제일 앞에 node를 삽입
					h->first = node;
					node->link = p;
					break;
				}			
				else { //탐색한 위치가 node의 중간인 경우, 중간에 node 삽입
					node->link = p;
					trail->link = node;
					break;
				}
			}

		trail = p; //trail 한 칸 뒤로
		p = p->link; // p 한 칸 뒤로
		}			
	}
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //node에 key값을 넣는다

	node->link = h->first; //head가 가리키고 있던 것을 node가 가리킨다.
	h->first = node;  //head가 node를 가리킨다

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //node에 key값을 넣는다
	node->link = NULL; //node link 초기화

	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	
	if(h->first == NULL) { //연결된 node가 하나도 없는 경우, first에 node 삽입
		h->first = node;
	}
	else {//연결된 node가 있을 경우, 가장 마지막에 node 삽입
		while(p->link != NULL) { //마지막이 나올 때까지 탐색 반복
			p = p->link; //p 한 칸씩 앞으로
		}
	p->link = node; //p가 가리키는 곳에 node 삽입
	}
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	listNode* trail = NULL; //p를 따라올 구조체 포인터 trail

	if (h->first == NULL) { //연결된 node가 하나도 없는 경우, 삭제하지 않는다
		printf("nothing to delete\n");
	}
	else { //h->first != NULL
		while(1) {
			if(p == NULL) { //p의 탐색이 끝나 마지막을 가리키는 경우, key 값을 찾지 못함
				printf("cannot find the node for key = %d\n", key);
				break;
			}
			if(p->key == key) {//p가 가리키는 node의 key값이 입력받은 key와 같을 경우
				if(p == h->first) { //p가 탐색한 위치가 헤드의 위치인 경우, 제일 앞에 node를 삭제
					h->first = p->link;
					free(p);
					break;
				}
				else { //p가 탐색한 위치가 중간인 경우, 중간의 node 삭제
					trail->link = p->link;
					free(p);
					break;
				}
			}
			trail = p; //trail 한 칸 뒤로
			p = p->link; //p 한 칸 뒤로			
		}
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p

	if (h->first == NULL) { //연결된 node가 하나도 없는 경우, 삭제하지 않는다
		printf("nothing to delete\n");
	}
	else { //h->first != NULL
		h->first = p->link; //헤더가 두 번째 node를 가리킨다
		free(p); //p가 가리키는 첫 번째 node 메모리 해제
	}
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) { //연결된 node가 하나도 없는 경우, 삭제하지 않는다
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	listNode* trail = NULL; //p를 따라올 구조체 포인터 trail

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(p->link == NULL) { //p가 탐색한 위치가 헤드의 위치인 경우, 제일 앞에 node를 삭제
		h->first = NULL;
		free(p);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(p->link != NULL) { //마지막이 나올 때까지 탐색 반복
		trail = p; //trail 한 칸 증가
		p = p->link; //p 한 칸 증가
	}

	/* p가 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //마지막 노드가 될 노드의 link를 NULL로
	free(p); //메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {//연결된 node가 하나도 없는 경우, 반전할 수 없다
		printf("nothing to invert...\n");
		return 0;
	}
	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	listNode *middle = NULL; //p를 첫 번째로 따라올 구조체 포인터 trail
	listNode *trail = NULL; //p를 두 번째로 따라올 구조체 포인터 trail

	while(p != NULL){ //마지막이 나올 때까지 탐색 반복
		trail = middle; //trail 한 칸 증가
		middle = p; //middle 한 칸 증가
		p = p->link; //p 한 칸 증가
		middle->link = trail; //middle의 link를 반전
	}

	h->first = middle; //헤더가 가리키는 값을 가장 마지막 노드로 변경

	return 0;
}


void printList(headNode* h) {
	int i = 0; //반복문에 사용될 인덱스 i
	listNode* p; //리스트를 탐색할 구조체 포인터 p

	printf("\n---PRINT\n");

	if(h == NULL) { //헤더 노드가 아무것도 가리키고 있지 않는 경우, 연결된 노드가 하나도 없다
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p는 헤더 노드가 가리키고 있는 노드를 가리킨다

	while(p != NULL) { //p가 끝을 가리킬 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //노드의 인덱스와 key값 출력
		p = p->link; //p 한 칸 뒤로
		i++; //인덱스 하나 증가
	}

	printf("  items = %d\n", i); //노드의 개수 출력
}

