/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */


#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node { //노드 구조체 listNode
	int key; //data값
	struct Node* llink; //이전 노드를 가리키는 left link
	struct Node* rlink; //다음 노드를 가리키는 right link
} listNode;

typedef struct Head { //헤더 노드 구조체 headNode
	struct Node* first; //첫 번째 노드를 가리키는 헤더의 first
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);
// headNode* initialize(headNode* h)
// -> 구조체 자체를 동적할당하여, 메인의 포인터에 대입한다
// -> 싱글 포인터로 받는다. 값을 복사하기 때문에, 호출하는 곳의 값이 바뀌지 않는다
// -> 원본의 헤더 노드가 바뀌지 않는다

// int initialize(headNode** h)
// -> 이중 포인터 h가 가리키는 구조체로 동적할당하여, h의 주소로 접근한다
// -> 이중 포인터로 받는다. 호출하는 곳의 h를 바꾼다
// -> 원본의 헤더 노드를 바꾼다

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
		//int freeList(headNode** h);

int freeList(headNode* h);
// -> 마찬가지로 싱글포인터로 받기 때문에, 값을 복사하여 호출하는 곳의 값이 바뀌지 않는다
// -> 헤더 노드가 바뀌지 않는다

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

	char command; //사용자 명령어
	int key; //노드에 추가할 값
	headNode* headnode=NULL; //헤더 노드 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자 명령어 입력

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); //헤더 노드 초기화
			//싱글 포인터의 주소를 매개변수로 넘기기 때문에, initialize에서 더블 포인터로 받아야 한다
			break;
		case 'p': case 'P':
			printList(headnode); //연결리스트의 index와 key, node의 수 출력
			break;
		case 'f': case 'F':
			printf("Your Key = "); 
			scanf("%d", &key); //첫 번째에 삽입할 노드의 key 값 입력
			insertFirst(headnode, key); //첫 번째에 노드 삽입
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //마지막에 삽입할 노드의 key 값 입력
			insertLast(headnode, key); //마지막에 노드 삽입
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //오름차순으로 삽입할 노드의 key 값 입력
			insertNode(headnode, key); //노드의 key 값을 비교하여, 오름차순으로 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //첫 번째 노드 삭제
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드 삭제
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //삭제할 노드의 key 값 입력
			deleteNode(headnode, key); //입력받은 key 값과 같은 key를 가진 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //리스트를 역순으로 변경
			break;
		case 'q': case 'Q':
			freeList(headnode); //동적할당 메모리 해제

			// - 이중포인터를 매개변수로 받아도 해제할 수 있을 것
			//freeList(&headnode);
			break;					
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q'); //프로그램 종료

	return 1;
}

int initialize(headNode** h) { //헤더 노드 초기화
	if(*h != NULL) { //h가 가리키는 headnode가 비어있지 않다면(기존 리스트가 존재한다면)
		freeList(*h); //동적할당 메모리 해제
	}
	//headnode가 비어있다면
	*h = (headNode*)malloc(sizeof(headNode)); //h가 가리키는 headnode 동적할당
	(*h)->first = NULL; //헤더노드 link 초기화

	return 1;
}

int freeList(headNode* h) { //동적할당 메모리 해제
	listNode* p = h->first; //리스트를 탐색할 포인터 p
	listNode* trail = NULL; //p의 이전 노드를 가리킬 포인터 trail
	
	while(p != NULL) { //p가 마지막을 넘어갈 때까지
		trail = p; //trail이 p를 가리킨다
		p = p->rlink;//p는 다음 노드를 가리킨다
		free(trail); //trail이 가리키는 노드 메모리 해제
	}
	free(h); //헤더 노드 메모리 해제

	return 0;
}

// - 이중포인터를 매개변수로 받아도 해제할 수 있을 것
// int freeList(headNode** h) {
// 	listNode* p = (*h)->first;
// 	listNode* trail = NULL;
	
// 	while(p != NULL) {
// 		trail = p;
// 		p = p->rlink;
// 		free(trail);
// 	}
// 	free(*h);
	
// 	return 0;
// }

void printList(headNode* h) { //연결리스트의 index와 key, node의 수 출력
	int i = 0; //반복문에 사용되는 변수 i
	listNode* p; //리스트를 탐색할 포인터 p

	printf("\n---PRINT\n");

	if(h == NULL) { //리스트가 비어있다면
		printf("Nothing to print....\n"); //출력하지 않는다
		return;
	}

	p = h->first; //p는 첫 번째 노드를 가리킨다

	while(p != NULL) { //p가 마지막을 넘어갈 때까지
		printf("[ [%d]=%d ] ", i, p->key); //p가 가리키는 노드의 index와 key 값 출력
		p = p->rlink; //p는 다음 노드를 가리킨다
		i++; //index 증가
	}

	printf("  items = %d\n", i); //node의 수(item) 출력
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { //첫 번째에 노드 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key; //node의 key 값 대입
	node->rlink = node->llink = NULL; //node의 link 초기화

	if(h->first == NULL) { //리스트가 비어있다면
		h->first = node; //첫 번째에 노드 삽입
		return 0;
	}

	//node의 link 설정
	node->rlink = h->first; //node의 rlink는 head가 가리키는 첫 번째 노드를 가리킨다
	node->llink = NULL; //node가 첫 번째 노드가 되기 때문에, llink는 NULL

	//첫 번째 노드 link 설정
	listNode *p = h->first; //p는 첫 번째 노드를 가리킨다
	p->llink = node; //p가 가리키는 첫 번째 노드의 llink는 node를 가리킨다

	//헤더노드의 first 설정
	h->first = node; //헤더는 첫 번째 노드인 node를 가리킨다

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { //마지막에 노드 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //node에 key 값 대입
	node->llink = NULL; //node의 llink 초기화
	node->rlink = NULL; //node의 rlink 초기화

	if(h->first == NULL) { //리스트가 비어있다면
		h->first = node; //첫 번째에 노드 삽입
		return 0;
	}

	listNode* p = h->first; //리스트를 탐색할 포인터 p

	while(p->rlink != NULL) { //p가 가리키는 노드가 마지막 노드가 아닐 때
		p = p->rlink; //p를 다음 노드로 이동
	}
	p->rlink = node; //원래의 마지막 노드의 rlink는 node를 가리킨다
	node->llink = p; //node의 link는 원래의 마지막 노드를 가리킨다

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //노드의 key 값을 비교하여, 오름차순으로 노드 삽입
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 node 생성
	node->key = key; //node의 key 값 대입
	node->llink = NULL; //node의 llink 초기화
	node->rlink = NULL; //node의 rlink 초기화

	if(h->first == NULL) { //리스트가 비어있다면
		h->first = node; //첫 번째에 노드 삽입
		return 0;
	}

	listNode* p = h->first; //리스트를 탐색할 포인터 p

	while(1) {
		if(p == NULL) { //p가 마지막 노드를 넘어간 경우(탐색 실패)
			insertLast(h, key); //마지막에 node 삽입
			return 0;
		}
		if(p->key > key) { //p가 가리키는 노드의 key와 입력받은 key가 같을 때(탐색 성공)
			if(p == h->first) { //첫 번째에 삽입하는 경우
				insertFirst(h, key);
			}
			else { //중간에 삽입하는 경우
				node->llink = p->llink; //node의 llink는 p가 가리키는 노드의 이전 노드를 가리킨다
				node->rlink = p; //node의 rlink는 p가 가리키는 노드를 가리킨다
				p->llink->rlink = node; //p가 가리키는 노드의 이전노드의 rlink는 node를 가리킨다
				//p->llink = node; //p가 가리키는 노드의 llink는 node를 가리킨다.
			}
			return 0;
		}
		p = p->rlink; //p 한 칸 증가
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { //첫 번째 노드 삭제
	if(h->first == NULL) {//리스트가 비어있다면
		printf("nothing to delete.\n"); //삭제할 노드가 없다
		return 1;
	}
	listNode* p = h->first; //리스트를 탐색할 구조체 포인터 p
	h->first = p->rlink; //헤더는 p가 가리키는 노드(삭제할 노드)의 다음 노드를 가리킨다
	
	free(p); //p가 가리키는 노드 삭제

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { //마지막 노드 삭제
	if(h->first == NULL) { //리스트가 비어있다면
		printf("nothing to delete.\n"); //삭제할 노드가 없다
		return 1;
	}

	listNode* p = h->first; //리스트를 탐색할 포인터 p
	listNode* trail = NULL; //p의 이전 노드을 가리킬 포인터 trail

	//노드가 하나만 있으면
	if(p->rlink == NULL) {
		h->first == NULL; //헤더는 아무것도 가리키지 않는다(더 이상 노드가 없다)
		free(p); //p가 가리키는 노드 삭제
		return 0;
	}

	//노드가 여러 개 있는 경우
	while(p->rlink != NULL) { //p가 마지막 노드까지 이동
		trail = p; //trail 한 칸 증가
		p = p->rlink; //p 한 칸 증가
	}
	trail->rlink = NULL; //p의 이전 노드는 NULL을 가리킨다(마지막 노드가 된다)
	free(p); //p가 가리키는 노드 삭제

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { //입력받은 key 값과 같은 key를 가진 노드 삭제
	if(h->first == NULL) { //리스트가 비어있다면
		printf("nothing to delete.\n"); //삭제할 노드가 없다
		return 1;
	}

	listNode* p = h->first; //리스트를 탐색할 포인터 p
	
	while(1) {
		if(p == NULL) { //p가 마지막 노드를 넘어간 경우(탐색 실패)
			printf("cannot find the node for key = %d\n", key); //key 값을 찾지 못했다
			return 1;
		}
		if(p->key == key) { //p가 가리키는 노드의 key와 입력받은 key가 같을 때(탐색 성공)
			if(p == h->first) { //첫 번째 노드를 삭제하는 경우
				deleteFirst(h);
				break;
			}
			else if(p->rlink == NULL) { //마지막 노드를 삭제하는 경우
				deleteLast(h);
				break;
			}
			else { //중간 위치의 노드를 삭제하는 경우
				p->llink->rlink = p->rlink; //p가 가리키는 노드의 왼쪽 노드는 p의 오른쪽 노드를 가리킨다
				p->rlink->llink = p->llink; //p가 가리키는 노드의 오른쪽 노드는 p의 왼쪽 노드를 가리킨다
				free(p);
				break;
			}
		}
		p = p->rlink; //p 한 칸 증가
	}
	return 0;
}

/**
 * 리스트의 링크를 역순으로 재배치
 */
int invertList(headNode* h) { //리스트를 역순으로 변경
	if(h->first == NULL) { //리스트가 비어있다면
		printf("nothing to invert.\n"); //역순으로 변경할 노드가 없다
		return 1;
	}

	listNode* p = h->first; //리스트를 탐색할 포인터 p
	listNode* middle = NULL; //p의 이전 노드을 가리킬 포인터 middle
	listNode* trail = NULL; //middel의 이전 노드를 가리킬 포인터 trail

	while(p != NULL) { //p가 마지막 노드를 넘어갈 때까지
		trail = middle; //trail은 middle로 이동
		middle = p; //middle은 p로 이동
		p = p->rlink; //p는 다음 노드로 이동
		middle->llink = p; //middle의 llink는 p를 가리킨다(링크를 반전)
		middle->rlink = trail; //middle의 rlink는 trail을 가리킨다(링크를 반전)
	}
	h->first = middle; //헤더는 middle을 가리킨다(마지막 노드를 가리킨다)

	return 0;
}