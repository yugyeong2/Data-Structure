/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어를 입력한다

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //insert할 노드의 key를 입력한다
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //delete할 노드의 key를 입력한다
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //search할 노드의 key를 입력한다
			ptr = searchIterative(head, key); //search한 결과를 ptr에 저장한다
			if(ptr != NULL) //ptr이 NULL이 아니라면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //탐색한 노드의 key 값과 주소를 출력한다
			else //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); //key 값을 가진 노드가 존재하지 않는다
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); //search할 노드의 key를 입력한다
			ptr = searchRecursive(head->left, key); //search한 결과를 ptr에 저장한다
			if(ptr != NULL) //ptr이 NULL이 아니라면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //탐색한 노드의 key 값과 주소를 출력한다
			else //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); //key 값을 가진 노드가 존재하지 않는다
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //헤더의 왼쪽 노드의 주소를 넘겨준다
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); //헤더의 왼쪽 노드의 주소를 넘겨준다
			break;
		case 't': case 'T':
			postorderTraversal(head->left); //헤더의 왼쪽 노드의 주소를 넘겨준다
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q'); //q 또는 Q를 입력하면 종료한다

	return 1;
}

int initializeBST(Node** h) {
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //만약 트리에 노드가 존재한다면
		freeBST(*h); //트리를 해제한다

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //헤드 노드를 생성한다
	(*h)->left = NULL; //헤드의 left 링크는 root 노드를 가리킨다
	(*h)->right = *h; //헤드의 right 링크는 자신을 가리킨다
	(*h)->key = -9999; //헤드 노드라는 것을 명시하기 위해 헤드의 key를 임의의 수 -9999로 설정한다
	return 1;
}

void inorderTraversal(Node* ptr) { //ptr에 head->left를 받는다(함수가 main에서 호출될 때 ptr 초기화)
	if (ptr) { //ptr이 NULL을 가리키지 않을 때
		inorderTraversal(ptr->left); //재귀함수로 ptr을 왼쪽 끝 노드로 이동한다
		printf("%d ", ptr->key); //ptr이 가리키는 노드의 key를 출력한다
		inorderTraversal(ptr->right); //재귀함수로 왼쪽 노드가 없으면, ptr을 오른쪽 노드로 이동한다
		//재귀를 탈출
	}
}

void preorderTraversal(Node* ptr) { //ptr에 head->left를 받는다(함수가 main에서 호출될 때 ptr 초기화)
	if(ptr) { //ptr이 NULL을 가리키지 않을 때
		printf("%d ", ptr->key); //부모 노드부터 왼쪽으로 순서대로 key를 출력한다
		preorderTraversal(ptr->left); //재귀함수로 ptr을 왼쪽 노드로 이동한다
		preorderTraversal(ptr->right); //재귀함수로 왼쪽 노드가 없으면, ptr을 오른쪽 노드로 이동한다
		//재귀를 탈출
	}
}

void postorderTraversal(Node* ptr) { //ptr에 head->left를 받는다(함수가 main에서 호출될 때 ptr 초기화)
	if(ptr) { //ptr이 NULL을 가리키지 않을 때
		postorderTraversal(ptr->left); //재귀함수로 ptr을 왼쪽 끝 노드로 이동한다
		postorderTraversal(ptr->right); //재귀함수로 왼쪽 노드가 없으면, ptr을 오른쪽 노드로 이동한다
		printf("%d ", ptr->key); //부모 노드를 가장 나중에 출력한다
		//재귀를 탈출
	}
}


int insert(Node* head, int key) {
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 node 생성
	newNode->key = key; //node에 key 대입
	newNode->left = NULL; //node의 left 링크를 NULL로 초기화
	newNode->right = NULL; //node의 right 링크를 NULL로 초기화

	if (head->left == NULL) { //트리의 노드가 0개
		head->left = newNode; //헤드의 왼쪽에 새로운 노드를 추가
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //트리를 탐색할 포인터 ptr은 헤드의 왼쪽 노드(루트 노드를 가리킨다)

	Node* parentNode = NULL; //ptr의 부모 노드를 가리킬 포인터 parentNode는 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아닐 때

		/* if there is a node for the key, then just return */
		if(ptr->key == key) //이미 key가 동일한 노드가 있을 경우 노드를 삽입하지 않는다
			return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr을 이동하기 전에 parentNode를 ptr로 이동한다

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //node의 key가 ptr이 가리키는 key보다 클 경우
			ptr = ptr->right; //ptr을 오른쪽으로 이동한다
		else //node의 key가 ptr이 가리키는 key보다 작은 경우
			ptr = ptr->left; //ptr을 왼쪽으로 이동한다
	}
	
	/* linking the new node to the parent */
	//ptr이 NULL을 만나 leaf node에 도달한 경우
	if(parentNode->key > key) //node의 key가 ptr의 부모 노드의 key보다 작은 경우
		parentNode->left = newNode; //ptr의 부모 노드의 왼쪽에 node를 삽입한다
	else //node의 key가 ptr의 부모 노드의 key보다 큰 경우
		parentNode->right = newNode; //ptr의 부모 노드의 오른쪽에 node를 삽입한다
	return 1;
}

int deleteLeafNode(Node* head, int key) {
	if (head == NULL) { //트리의 노드가 0개(헤드 노드도 없다)
		printf("\n Nothing to delete!!\n"); //삭제할 노드가 없기 때문에 함수를 종료한다
		return -1;
	}

	if (head->left == NULL) { //트리의 노드가 0개
		printf("\n Nothing to delete!!\n"); //삭제할 노드가 없기 때문에 함수를 종료한다
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //트리를 탐색할 포인터 ptr은 헤드의 왼쪽 노드(루트 노드를 가리킨다)


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //ptr의 부모 노드를 가리킬 포인터 parentNode는 head를 가리킨다

	while(ptr != NULL) { //ptr이 NULL이 아닐 때

		if(ptr->key == key) { //ptr이 가리키는 노드가 입력받은 key와 같을 경우
			if(ptr->left == NULL && ptr->right == NULL) { //ptr이 가리키는 노드가 leaf node인 경우

				/* root node case */
				if(parentNode == head) //ptr의 부모 노드가 헤드일 경우(노드가 하나밖에 없는 경우)
					head->left = NULL; //head와 ptr이 가리키는 노드의 연결을 끊는다(트리의 노드가 0개)

				/* left node case or right case*/
				if(parentNode->left == ptr) //ptr이 부모 노드의 왼쪽 노드인 경우
					parentNode->left = NULL; //부모노드와 ptr이 가리키는 노드의 연결을 끊는다
				else //ptr이 부모 노드의 오른쪽 노드인 경우
					parentNode->right = NULL; //부모노드와 ptr이 가리키는 노드의 연결을 끊는다

				free(ptr); //ptr이 가리키는 노드를 메모리 해제한다
			}
			else { //key 값을 가진 노드가 leaf 노드가 아닌 경우
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //ptr을 이동하기 전에 parentNode를 ptr로 이동한다

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //node의 key가 ptr의 부모 노드의 key보다 작은 경우
			ptr = ptr->right; //ptr의 부모 노드의 왼쪽에 node를 삽입한다
		else //node의 key가 ptr의 부모 노드의 key보다 큰 경우
			ptr = ptr->left; //ptr의 부모 노드의 오른쪽에 node를 삽입한다
	}

	printf("Cannot find the node for key [%d]\n ", key); //key 값을 가진 노드가 존재하지 않은 경우

	return 1;
}

Node* searchRecursive(Node* ptr, int key) { //recursive 방식으로 search
	if(ptr == NULL) //ptr이 NULL을 가리키면 NULL을 리턴한다(노드가 존재하지 않는다)
		return NULL;

	if(ptr->key < key) //search할 key가 ptr이 가리키는 노드의 key보다 큰 경우
		ptr = searchRecursive(ptr->right, key); //ptr을 오른쪽으로 이동하고 재귀로 다시 함수를 호출한다
	else if(ptr->key > key) //search할 key가 ptr이 가리키는 노드의 key보다 작은 경우
		ptr = searchRecursive(ptr->left, key); //ptr을 왼쪽으로 이동하고 재귀로 다시 함수를 호출한다

	/* if ptr->key == key */
	//search할 key를 찾은 경우
	return ptr; //ptr이 가리키는 주소를 리턴한다
}

Node* searchIterative(Node* head, int key) { //iterative 방식을 search
	/* root node */
	Node* ptr = head->left; //트리를 탐색할 포인터 ptr은 헤드의 왼쪽 노드(루트 노드를 가리킨다)

	while(ptr != NULL) //ptr이 NULL이 아닐 때
	{
		if(ptr->key == key)	//search할 key를 찾은 경우
			return ptr; //ptr이 가리키는 주소를 리턴한다

		if(ptr->key < key) //search할 key가 ptr이 가리키는 노드의 key보다 큰 경우
			ptr = ptr->right; //ptr을 오른쪽으로 이동
		else //search할 key가 ptr이 가리키는 노드의 key보다 작은 경우
			ptr = ptr->left; //ptr을 왼쪽으로 이동
	}
	//search할 key를 못 찾은 경우
	return NULL; //NULL을 리턴한다
}

void freeNode(Node* ptr) { //ptr에 head의 주소를 받는다
	if(ptr) { //ptr이 NULL이 아닌 경우(헤드가 비어있지 않은 경우)
		freeNode(ptr->left); //ptr의 왼쪽 노드를 재귀 호출한다
		freeNode(ptr->right); //ptr의 오른쪽 노드를 재귀 호출한다
		free(ptr); //ptr을 메모리 해제한다
		//재귀를 탈출
	}
}

int freeBST(Node* head) {
	if(head->left == head) //헤드가 가리키는 노드가 없는 경우
	{
		free(head); //헤드를 메모리 해제한다
		return 1;
	}

	Node* p = head->left; //포인터 p는 첫 번째 노드를 가리킨다

	freeNode(p); //p가 가리키는 노드를 메모리 해제한다

	free(head); //헤드를 메모리 해제한다
	return 1;
}