/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { //이중 연결리스트의 노드 구조체 listNode
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

	char command; //사용자가 입력할 명령어
	int key; //사용자가 입력할 노드의 key
	listNode* headnode=NULL; //헤더 노드 생성 후 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); //주소를 넘긴다 = 헤드 노드의 값을 바꾼다
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q또는 Q를 입력할 때까지 반복

	return 1;
}

int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //헤더 동적할당
	//더 이상 노드가 없기 때문에, 헤더는 자신을 가리킨다
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999; //헤더 노드임을 알려주기 위해 임의의 수 -9999를 저장한다
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫 번째 노드를 가리킨다
	listNode* trail = NULL; //p를 뒤따라가는 포인터 trail

	while(p != NULL && p != h) { //p가 NULL이 아니고, 헤더가 아니면(헤더를 제외한 모든 노드 해제)
		trail = p; //p를 이동하기 전에, trail을 다음 노드로 이동
		p = p->rlink; //p를 다음 노드로 이동
		free(trail); //trail 메모리 해제
	}
	free(h); //헤더 메모리 해제

	return 0;
}

void printList(listNode* h) {
	int i = 0;

	printf("\n---PRINT\n");

	if(h == NULL) { //노드 0개
		printf("Nothing to print....\n");
		return;
	}

	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫 번째 노드를 가리킨다

	while(p != NULL && p != h) { //p가 NULL이 아니고, 헤더가 아니면(헤더를 제외한 모든 노드 출력)
		printf("[ [%d]=%d ] ", i, p->key); //p가 가리키는 노드의 인덱스와 key 출력
		p = p->rlink; //p를 다음 노드로 이동
		i++; //인덱스 증가
	}
	printf("  items = %d\n", i); //노드의 수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //헤더의 llink, 주소, rlink 출력

	i = 0;
	p = h->rlink; //p는 다시 첫 번째 노드를 가리킨다
	while(p != NULL && p != h) { //p가 NULL이 아니고, 헤더가 아니면(헤더를 제외한 모든 노드 출력)
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //p가 가리키는 노드의 llink, 주소, rlink 출력
		p = p->rlink; //p를 다음 노드로 이동
		i++; //인덱스 증가
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성 후 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다

	if(h->llink == h && h->rlink == h) { //노드 0개
	 	//헤더는 node를 가리킨다
		node->llink = h; //node의 llink는 헤더를 가리킨다 (첫번째 노드는 node)
		node->rlink = h; //node의 rlink는 헤더를 가리킨다 (마지막 노드는 node)		
		h->llink = node;
		h->rlink = node;
		return 1;
	}

	//노드 1개 이상 존재
	while(p->rlink != NULL && p->rlink != h) { //p의 다음 노드가 NULL이 아니고, 헤더가 아니면(마지막 노드까지 p를 이동)
		p = p->rlink; //p를 다음 노드로 이동
	}
	p->rlink = node; //p의 다음 노드는 node
	node->llink = p; //node의 이전 노드는 p
	node->rlink = h; //node의 rlink는 헤더를 가리킨다 (마지막 노드는 node)
	h->llink = node; //헤더의 llink는 node

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다

	if(h->llink == h && h->rlink == h) { //노드 0개
		printf("There are no nodes to delete.\n\n");
	}
	else if(p->llink == h->llink && p->rlink == h->rlink) { //노드 1개
		//더 이상 노드가 없기 때문에, 헤더는 자신을 가리킨다
		h->llink = h;
		h->rlink = h;
		free(p); //p가 가리키는 노드 삭제
	}
	else { //노드 2개 이상
		while(p->rlink != NULL && p->rlink != h) { //p의 다음 노드가 NULL이 아니고, 헤더가 아니면(마지막 노드까지 p를 이동)
			p = p->rlink; //p를 다음 노드로 이동
		}
		h->llink = p->llink; //헤더의 llink는 p의 llink (마지막 노드는 p의 이전 노드)
		p->llink->rlink = h; //p의 이전 노드의 rlink는 헤더를 가리킨다
		free(p); //p가 가리키는 노드 삭제
	}
	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성 후 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if(h->llink == h && h->rlink == h) { //노드 0개
		//헤더는 node를 가리킨다
		node->llink = h; //node의 llink는 헤더 (첫번째 노드는 node)
		node->rlink = h; //node의 rlink는 헤더 (마지막 노드는 node)		
		h->llink = node;
		h->rlink = node;
	}
	else { //노드 1개 이상
		node->llink = h; //node의 llink는 헤더 (첫번째 노드는 node)
		node->rlink = h->rlink; //node의 rlink는 헤더의 rlink (원래의 첫번째 노드)	
		h->rlink = node; //h의 rlink는 node (첫번째 노드는 node)
	}
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다

	if(h->llink == h && h->rlink == h) { //노드 0개
		printf("There are no nodes to delete.\n\n");
	}
	else if (p->rlink == NULL) { //노드 1개
		//더 이상 노드가 없기 때문에, 헤더는 자신을 가리킨다
		h->llink = h;
		h->rlink = h;
		free(p); //p가 가리키는 노드 삭제
	}
	else { //노드 2개 이상
		h->rlink = p->rlink; //헤더의 rlink는 p의 rlink (첫번째 노드는 p의 다음 노드)
		p->rlink->llink = h; //p의 다음 노드의 llink는 헤더
		free(p); //p가 가리키는 노드 삭제
	}
	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다
	listNode* middle = NULL; //p를 뒤따라가는 포인터 middle
	listNode* trail = NULL; //middle을 뒤따라가는 포인터 trail

	if(h->llink == h && h->rlink == h) { //노드 0개
		printf("There are no nodes to invert.\n\n");
		return 0;
	}
	//노드 1개 이상
	while(p != NULL && p != h) { //p가 NULL이 아니고, 헤더가 아니면(마지막 노드까지 p를 이동)
		trail = middle;  //middle을 이동하기 전에, trail을 다음 노드로 이동
		middle = p; //p를 이동하기 전에, middle을 다음 노드로 이동
		p = p->rlink; //p를 다음 노드로 이동

		middle->llink = p; //middle의 왼쪽 노드는 오른쪽 노드를 가리킨다
		middle->rlink = trail; //middle의 오른쪽 노드는 왼쪽 노드를 가리킨다
	}
	h->llink = h->rlink; //헤더의 llink는 처음의 헤더의 rlink를 가리킨다(첫번째노드가 마지막노드로)
	h->rlink = middle; //헤더의 rlink는 middle을 가리킨다(마지막노드는 첫번째노드로)

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성 후 초기화
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다
	listNode* trail = NULL; //p를 뒤따라가는 포인터 trail

	if(h->llink == h && h->rlink == h) { //노드 0개
		node->llink = h; //node의 llink는 헤더를 가리킨다 (첫번째 노드는 node)
		node->rlink = h; //node의 rlink는 헤더를 가리킨다 (마지막 노드는 node)
		//헤더는 node를 가리킨다
		h->llink = node;
		h->rlink = node;
		return 0;
	}

	//노드 1개 이상
	while(1) {
		if(p == h && trail == h->llink) { //삽입 위치가 마지막일 때 (key 탐색 실패)
			insertLast(h, key); //마지막 위치에 노드 삽입
			return 0;
		}

		if(key < p->key) { //key 탐색 성공
			if(p == h->rlink) { //삽입 위치가 첫번째일 때
				insertFirst(h, key); //첫번째 위치에 노드 삽입
				return 0;
			}
			else { //삽입 위치가 중간일 때
				node->llink = trail; //node의 llink는 trail을 가리킨다
				node->rlink = p; //node의 rlink는 p를 가리킨다
				trail->rlink = node; //trail의 rlink는 node를 가리킨다
				p->llink = node; //p의 llink는 node를 가리킨다
				return 0;
			}
		}
		trail = p;; //p를 이동하기 전에, trail을 다음 노드로 이동
		p = p->rlink; //p를 다음 노드로 이동
	}
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* p = h->rlink; //리스트를 탐색할 포인터 p는 첫번째 노드를 가리킨다
	listNode* trail = NULL; //p를 뒤따라가는 포인터 trail

	if(h->rlink == h && h->llink == h) { //노드 0개
		printf("There are no nodes to delete.\n\n");
		return 0;
	}

	while(1) {
		if(p == h && trail == h->llink) { //삭제 위치가 마지막일 때 (key 탐색 실패)
			printf("No node matches key.\n\n"); //key와 일치하는 노드가 없습니다
			return 0;
		}

		if(p->key == key) { //p가 가리키는 노드의 key와 삭제할 노드의 key가 같을 때
			if(p->llink == h->llink && p->rlink == h->rlink) { //노드 1개
				//더 이상 노드가 없기 때문에, 헤더는 자신을 가리킨다
				h->llink = h;
				h->rlink = h;
				free(p); //p가 가리키는 노드 삭제
				return 0;
			}
			
			//노드 2개 이상
			if(p == h->rlink) { //삭제 위치가 첫번째일 때
				deleteFirst(h); //첫번째 노드 삭제
				return 0;
			}
			else if(p == h->llink) { //삭제 위치가 마지막일 때
				deleteLast(h); //마지막 노드 삭제
				return 0;
			}
			else {
				p->llink->rlink = p->rlink; //p의 왼쪽 노드의 rlink는 p의 오른쪽 노드를 가리킨다
				p->rlink->llink = p->llink; //p의 오른쪽 노드의 llink는 p의 왼쪽 노드를 가리킨다
				free(p); //p가 가리키는 노드를 삭제
				return 0;
			}
		}
		trail = p; //p를 이동하기 전에, trail을 다음 노드로 이동
		p = p->rlink; //p를 다음 노드로 이동		
	}
	return 0;
}