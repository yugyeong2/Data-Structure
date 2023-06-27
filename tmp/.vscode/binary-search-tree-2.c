/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node 구조체
	int key; //node의 key 값
	struct node *left; //node의 left 포인터
	struct node *right; //node의 right 포인터
} Node;

/* for stack */
#define MAX_STACK_SIZE	20 //스택의 최댓값 20
Node* stack[MAX_STACK_SIZE]; //스택 포인터 배열의 크기는 20
int top = -1; //스택의 top은 -1을 가리킨다(스택에 아무것도 없다)

/* for circular queue */
#define MAX_QUEUE_SIZE	20 //큐의 최댓값 20
Node* queue[MAX_QUEUE_SIZE]; //큐 포인터 배열의 크기는 20
//큐의 front와 rear는 -1을 가리킨다(큐에 아무것도 없다)
int front = -1;
int rear = -1;

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */

void printStack();

int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");
	
	char command; //입력받을 명령어
	int key; //입력받을 node의 key 값
	Node* head = NULL; //헤드 NULL로 초기화

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      PrintStack                   = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //헤드의 값을 바꿔야하기 때문에 헤드의 주소를 넘긴다
			break;
		case 'q': case 'Q':
			freeBST(head); //헤드 노드를 전달
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 노드의 key 값 입력
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //삭제할 노드의 key 값 입력
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left); //root 노드를 전달
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //root 노드를 전달
			break;
		case 'l': case 'L':
			levelOrder(head->left); //root 노드의 주소를 전달
			break;
		case 'p': case 'P':
			printStack();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q 또는 Q이면 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //헤드가 비어있지 않으면(헤드에 노드가 연결되어 있다면)
		freeBST(*h); //헤드에 연결된 메모리를 해제한다

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //헤드 노드를 생성한다
	/* root */
	(*h)->left = NULL; //헤드의 left 링크는 NULL로 초기화한다(헤드의 left는 root를 가리킨다)
	(*h)->right = *h; //헤드의 right 링크는 헤드 자신을 가리킨다
	(*h)->key = -9999; //헤드 노드는 key를 임의로 -9999로 지정(헤드 노드임을 명시)

	return 1;
}

void recursiveInorder(Node* ptr) //main에서 ptr에 root 노드를 전달
{
	if(ptr) {  //ptr이 참일 때(ptr이 NULL을 가리키지 않을 때)
		recursiveInorder(ptr->left); //left node가 있으면 재귀호출로 왼쪽으로 이동
		printf(" [%d] ", ptr->key); //왼쪽 끝부터 차례로 이동하며 출력
		recursiveInorder(ptr->right); //right node가 있으면 재귀호출로 오른쪽으로 이동
	}
}

/* textbook: p 224 */
void iterativeInorder(Node* node) //main에서 node에 root 노드를 전달
{
	if(!node) return; /* empty tree */

	while(1) {
		//node가 NULL을 만날 때까지 왼쪽으로 이동
		while(node != NULL) { //node의 왼쪽 노드가 NULL이 아니면(left leaf node까지)
			push(node); //node를 push
			node = node->left; //node를 왼쪽으로 이동
		}

		node = pop(); //pop의 반환값을 node에 대입

		if(node == NULL) //pop의 반환값이 NULL일 때(더 이상 pop할 노드가 없음 -> 스택 공백)
			break;
		else { //pop의 반환값이 NULL이 아닐 때
			printf(" [%d] ", node->key); //pop한 node의 key 값을 출력
		}

		node = node->right; //node를 오른쪽으로 이동
		//오른쪽으로 이동한 뒤, 다시 NULL을 만날 때까지 왼쪽으로 이동(반복)
	}
}

void push(Node* aNode)
{
	stack[++top] = aNode; //증가시킨 top이 가리키는 스택의 위치에 aNode 삽입
}

Node* pop()
{
	if(top < 0) { //top이 -1이면(노드가 없으면)
		return NULL; //NULL을 반환
	}
	else { //top이 0이상이면
		return stack[top--]; //top이 가리키는 스택의 노드를 반환하고, top을 감소시킨다
	} //나중에 push할 때 스택의 값이 바뀌므로 스택 안의 값을 굳이 삭제하지 않고 top만 바꾼다
}

/* textbook: p 225 */
void levelOrder(Node* ptr) //main에서 ptr에 root 노드를 전달
{
	if(!ptr) return; /* empty tree */

	enQueue(ptr); //root 노드 삽입

	while(1) {
		ptr = deQueue(); //deQueue의 반환값을 ptr에 대입

		if(ptr != NULL) { //deQueue의 반환값이 NULL이 아닐 때
			printf(" [%d] ", ptr->key); //deQueue한 ptr의 key 값 출력

			//같은 Level의 노드를 모두 enQueue
			//ptr이 NULL이 아니면서 ptr의 left, right 링크가 NULL일 때, deQueue만 실행한다
			if(ptr->left) { //ptr의 left 링크가 NULL이 아닐 때(ptr의 left 노드가 존재하면)
				enQueue(ptr->left); //ptr의 왼쪽 노드부터 삽입
			}
			if(ptr->right) { //ptr의 right 링크가 NULL이 아닐 때(ptr의 right 노드가 존재하면)
				enQueue(ptr->right); //ptr의 오른쪽 노드를 삽입
			}
		}
		else { //deQueue의 반환값이 NULL일 때
			break;
		}
	}
}

void enQueue(Node* aNode) //Circular Queue enQueue
{
	//rear를 증가시키고, 모듈러 연산으로 rear가 MAX_QUEUE_SIZE를 넘어가면 다시 0으로 돌아간다
	//rear[MAX_QUEUE_SIZE] -> rear[0]
	rear = (rear + 1) % MAX_QUEUE_SIZE;

	//is full
	if(front == rear) { //큐의 첫 번째 노드와 마지막 노드의 위치가 같다면
		//printf("Queue is full.\n\n"); //큐는 가득 차서 삽입할 수 없다
		return ;
	}
	queue[rear] = aNode; //rear가 가리키는 큐의 마지막 노드 위치에 aNode 삽입
}

Node* deQueue() //Circular Queue deQueue
{
	//is empty
	if(front == rear) { //큐의 첫 번째 노드와 마지막 노드의 위치가 같다면
		//printf("Queue is empty.\n\n"); //큐가 비어있어 삭제할 수 없다
		return NULL; //NULL 반환
	}
	
	//front를 증가시키고, 모듈러 연산으로 front가 MAX_QUEUE_SIZE를 넘어가면 다시 0으로 돌아간다
	//front[MAX_QUEUE_SIZE] -> front[0]
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front]; //front 위치의 큐 값을 반환		
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 node 생성
	newNode->key = key; //node에 key 대입
	newNode->left = NULL; //node의 left 링크를 NULL로 초기화
	newNode->right = NULL; //node의 right 링크를 NULL로 초기화

	if (head == NULL) { //헤드 노드가 없는 경우
		printf("There's no head.\n");
		return -1;
	}
	if (head->left == NULL) { //헤드에 연결된 노드가 0개인 경우
		head->left = newNode; //헤드의 left 링크에 새로운 노드 삽입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //포인터 ptr은 헤드의 왼쪽 노드를 가리킨다(root 노드)
	Node* parentNode = NULL; //ptr을 뒤따라가는 포인터 parentNode(부모노드)는 ptr의 이전 노드를 가리킨다
	
	while(ptr != NULL) { //ptr이 NULL이 아닐 때(ptr을 트리의 끝(NULL을 만날 때)까지 탐색)

		/* if there is a node for the key, then just return */
		if(ptr->key == key) { //트리에 이미 동일한 key 값을 가진 노드가 있다면
			return 1;
		}
		
		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr을 이동하기 전, parentNode를 ptr의 위치로 이동시킨다

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr이 가리키는 노드의 key < 입력받은 key
			ptr = ptr->right; //ptr을 오른쪽으로 이동
		else //입력받은 key < ptr이 가리키는 노드의 key
			ptr = ptr->left; //ptr을 왼쪽으로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //입력받은 key < ptr의 부모노드
		parentNode->left = newNode; //ptr의 부모노드의 왼쪽에 새로운 노드 삽입
	else //ptr의 부모노드 < 입력받은 key
		parentNode->right = newNode; //ptr의 부모노드의 오른쪽에 새로운 노드 삽입
	return 1;
}

//왼쪽에서 가장 큰 원소 or 오른쪽에서 가장 작은 원소를 삭제
int deleteNode(Node* head, int key)
{
	if(head == NULL) { //헤드 노드가 없는 경우
		printf("There's no head.\n");
		return -1;
	}
	if(head->left == NULL) { //헤드에 연결된 노드가 0개인 경우
		printf("Queue is empty.\n"); //큐가 비어있어 삭제할 노드가 없다
		return -1;
	}
	
	Node* ptr = head->left; //포인터 ptr은 root 노드를 가리킨다
	Node* parent = NULL; //ptr을 뒤따라갈 부모노드 parent는 ptr의 이전 노드를 가리킨다

	//key 값을 가진 노드 탐색
	while((ptr != NULL) && (ptr->key != key)) { //ptr이 NULL이 아니고, ptr의 key가 입력받은 key 다르다
		parent = ptr; //ptr을 이동하기 전, parent를 ptr의 위치로 이동

		if(ptr->key > key) { //입력받은 key < ptr이 가리키는 노드의 key
			ptr = ptr->left; //ptr을 왼쪽으로 이동
		}
		else { //ptr이 가리키는 노드의 key > 입력받은 key
			ptr = ptr->right; //ptr을 오른쪽으로 이동
		}
	}
	if(ptr == NULL) { //ptr이 key 값을 가진 노드를 탐색하지 못하고, NULL을 가리킬 때(트리의 끝까지 도달)
		printf("There's no node for key [ %d ]\n", key);
		return -1;
	}

	//Case 1. leaf node 삭제
	if((ptr->left == NULL) && (ptr->right == NULL)) { //ptr이 가리키는 node가 leaf node
		
		if(parent != NULL) { //ptr의 부모노드가 NULL이 아닌 경우(ptr은 root 노드가 아니다)
			if(ptr == parent->left) { //부모노드의 왼쪽 노드가 ptr인 경우
				parent->left = NULL; //부모노드의 left 링크를 NULL로 한다
			}
			else if(ptr == parent->right) { //부모노드의 오른쪽 노드가 ptr인 경우
				parent->right = NULL; //부모노드의 right 링크를 NULL로 한다
			}		
		}
		else { //ptr의 부모노드가 NULL인 경우(ptr은 root 노드)
			head->left = NULL; //헤드 노드가 자기자신을 가리키도록 다시 초기화
		}

		free(ptr);
		return 1;
	}

	//Case 2. 하나의 자식을 가진 non-leaf node 삭제
	if((ptr->left == NULL) || (ptr->right == NULL)) { //ptr의 left, right 링크 둘 중 하나가 NULL인 경우
		
		Node* child = NULL; //ptr의 자식 노드를 가리킬 포인터 child

		if(ptr->left == NULL) { //ptr의 왼쪽 노드가 NULL인 경우(자식노드는 오른쪽에 있다)
			child = ptr->right; //ptr의 자식노드는 오른쪽 노드
		}
		else if(ptr->right == NULL) { //ptr의 오른쪽 노드가 NULL인 경우(자식노드는 왼쪽에 있다)
			child = ptr->left; //ptr의 자식노드는 왼쪽 노드
		}

		if(parent != NULL) { //ptr의 부모노드가 NULL이 아닌 경우(ptr은 root 노드가 아니다)
			if(ptr == parent->left) { //부모노드의 왼쪽 노드가 ptr인 경우
				parent->left = child;
			}
			else if(ptr == parent->right) { //부모노드의 오른쪽 노드가 ptr인 경우
				parent->right = child;
			}
		}
		else { //ptr의 부모노드가 NULL인 경우(ptr은 root 노드)
			head->left = child;
		}

		free(ptr);
		return 1;
	}

	//Case 3. 두 개의 자식을 가진 non-leaf node 삭제
	//삭제된 자리를 오른쪽 서브트리에서 가장 작은 노드로 대체한다
 	//ptr이 삭제된 자리에 ptr의 오른쪽 노드 중 가장 작은 노드를 올린다

	if((ptr->left != NULL) && (ptr->right != NULL)) { //ptr의 left, right 링크 모두 NULL이 아닌 경우
		
		Node* candidate = ptr->right; //ptr을 대체할 노드를 찾기 위한 포인터 candidate는 ptr의 오른쪽 노드를 가리킨다
		parent = ptr; //parent는 candidate의 부모노드

		while(candidate->left != NULL) { //candidate를 왼쪽 leaf 노드까지 이동
			parent = candidate; //candidate를 이동하기 전, parent를 먼저 이동시킨다
			candidate = candidate->left; //가장 작은 노드를 찾기 위해, candidate를 왼쪽으로 이동시킨다
		}

		//candidate는 오른쪽 서브트리에서 가장 작은 노드이다		
		if(parent->left == candidate) { //candidate가 부모노드의 왼쪽에 존재하는 경우
			parent->left = candidate->right; //parent의 left 자리(원래의 candidate의 자리)는 candidate의 오른쪽 노드가 된다
			//candidate의 왼쪽 노드는 존재할 수 없다(candidate의 왼쪽 노드가 다시 가장 작은 노드가 되기 때문)
		}
		else if(parent->right == candidate) { //candidate가 부모노드의 왼쪽에 존재하지 않는 경우(부모노드의 왼쪽 노드는 없다)
			parent->right = candidate->right; //parent의 right 자리(원래의 candidate의 자리)는 candidate의 오른쪽 노드가 된다
			//candidate의 왼쪽 노드는 존재할 수 없다(candidate의 왼쪽 노드가 다시 가장 작은 노드가 되기 때문)
		}
		
		ptr->key = candidate->key; //ptr을 메모리 해제하는 대신, key 값만 변경한다
		
		free(candidate); //원래의 candidate를 메모리 해제한다
		return 1;
	}
}

void freeNode(Node* ptr) //ptr에 head를 전달
{
	if(ptr) { //ptr이 참일 때(ptr이 NULL을 가리키지 않을 때)
		freeNode(ptr->left); //left node가 있으면 재귀호출로 ptr을 왼쪽으로 이동
		freeNode(ptr->right); //right node가 있으면 재귀호출로 ptr을 오른쪽으로 이동
		free(ptr); //ptr이 가리키는 노드를 메모리 해제
	}
}

int freeBST(Node* head)
{
	if(head->left == head) { //헤드 노드의 left 링크가 헤드 자신을 가리킬 때(트리에 노드가 없다)
		free(head); //헤드 메모리 해제
		return 1;
	}

	Node* p = head->left; //포인터 p는 헤드의 왼쪽 노드를 가리킨다

	freeNode(p); //재귀함수 freeNode를 호출하여 p가 가리키는 모든 노드를 메모리 해제한다

	free(head); //헤드 메모리 해제
	return 1;
}

void printStack() //스택은 비어있어야 정상(iterativeInorder를 실행시키면, pop해서 출력하기 때문에 스택은 비어있게 된다)
{
	printf("--- stack ---\n");
	for(int i = 0; i <= top; i++) { //인덱스 0 ~ top까지 반복
		printf("stack[%d] = %d\n", i, stack[i]->key); //스택의 인덱스와 key 값 출력
	}
}