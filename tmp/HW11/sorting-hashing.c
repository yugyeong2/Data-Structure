/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	printf("[----- [Park Yugyeong] [2022041028] -----]\n\n");

	char command;
	int *array = NULL; //배열을 가리킬 array 포인터
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //array의 값을 바꿔야하기 때문에 array의 주소를 넘긴다
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 'i': case 'I':
			insertionSort(array); //삽입 정렬
			break;
		case 's': case 'S':
			selectionSort(array); //선택 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); //버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); //쉘 정렬
			break;

		case 'k': case 'K':
			printf("Quick Sort: \n"); // 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 전 배열 출력
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 후 배열 출력
			break;

		case 'h': case 'H':
			printf("Hashing: \n"); //해싱
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 전 배열 출력
			hashing(array, &hashtable); //hashtable의 값을 바꿔야하기 때문에 hashtable의 주소를 넘긴다
			printArray(hashtable); //정렬 후 배열 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //찾을 key 값 입력
			printArray(hashtable); //서치 전 배열 출력
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) //array의 주소를 이중 포인터로 받는다
{
	int *temp = NULL; //a를 초기화할 임시 공간 temp

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { //a 배열이 비어있는 경우
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //새로운 배열 temp를 동적으로 생성
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else //a가 비어있지 않은 경우(a 배열이 존재)
		temp = *a; //a 배열의 주소를 temp에 복사

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) {
		temp[i] = rand() % MAX_ARRAY_SIZE; //0~12의 랜덤 수를 temp에 차례로 저장
	} //배열의 인덱스 12만큼 반복

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //a가 비어있지 않으면(a 배열이 존재)
		free(a); //a 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { //a가 비어있으면
		printf("nothing to print.\n"); //출력할 배열이 존재하지 않는다
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //a의 인덱스를 0~12까지 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //배열 a의 값 순서대로 출력
	printf("\n");
}

int insertionSort(int *a) //삽입 정렬 -> i번째 원소를 정렬된 부분에서 알맞은 위치에 삽입한다
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //i는 1부터 배열의 크기-1까지 반복(a[0]은 이미 정렬되었다고 본다)
	{
		t = a[i]; //t에 a[i]를 임시 저장(a[i]는 정렬된 부분과 비교하여 삽입할 원소)
		j = i; //j에 i를 저장하여 i번째 원소와 j번째 원소를 비교한다

		//정렬된 부분 i와 정렬되지 않은 부분 j를 비교하여 알맞은 위치에 삽입
		while (a[j-1] > t && j > 0) //j가 0보다 크고(j=0이면 비교할 대상이 없다), a[j-1]이 a[i]보다 크면(정렬된 부분의 원소가 더 크면)
		{
			//자리 교환
			a[j] = a[j-1]; //a[j]에 a[j-1]을 저장
			j--; //j를 하나 감소
		}
		a[j] = t; //a[j]에 t에 임시 저장했던 a[i]를 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int selectionSort(int *a) //선택 정렬 -> 최소값을 선택해 i번째 원소와 바꾼다
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE-1; i++) //0~배열의크기-2까지 반복(마지막 원소는 이미 올바른 곳에 있기 때문에 바꿀 필요가 없다)
	{
		minindex = i; //최소값 인덱스
		min = a[i]; //최소값(a[0]을 최소값으로 놓는다)
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //a[i]까지는 정렬되었다고 보고, a[j]부터 차례로 비교한다
		{
			if (min > a[j]) //j번째 원소가 현재의 최소값보다 작으면
			{
				min = a[j]; //최소값을 j번째 원소로 바꾼다
				minindex = j; //최소값 인덱스를 j로 바꾼다
			}
		}
		//자리 교환
		a[minindex] = a[i]; //탐색한 최소값이 있는 자리에 a[i]를 저장한다
		a[i] = min; //a[i]에 탐색한 최소값을 저장한다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력
	return 0;
}

int bubbleSort(int *a) //버블 정렬 -> 인접한 두 원소를 비교하여 가장 큰 수를 한 칸씩 뒤로 보낸다
{
	int i, j, t; //t는 임시저장할 공간

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE-1; i++) //0~배열의크기-1까지 반복(i=5일때는 첫 번째 원소 하나밖에 남지않으므로 정렬할 필요 없다)
	{
		for (j = 1; j < MAX_ARRAY_SIZE-i; j++) //1~배열의크기-i까지 반복하여 비교한다(회차를 반복할 때마다 마지막 i개의 원소가 정렬된다)
		{
			if (a[j-1] > a[j]) //j번째 원소가 j-1번째 원소보다 작으면
			{
				//자리 교환
				t = a[j-1]; //t에 j-1번째 원소를 임시저장
				a[j-1] = a[j]; //j-1번째에 j번째 원소를 저장
				a[j] = t; //j번째에 t에 임시 저장했던 j-1번째 원소를 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int shellSort(int *a) //쉘 정렬
{
	int i, j, k, h, v; //v=a의 값 임시 저장, k=a의 인덱스 임시 저장

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //배열의 크기를 반으로 나눠 반씩 비교
	{
		for (i = 0; i < h; i++) //i는 0~h-1까지 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //j는 h~배열의 크기-1까지 반복
			{
				v = a[j]; //v에 a[j]를 임시 저장
				k = j; //k에 인덱스 j를 임시 저장
				while (k > h-1 && a[k-h] > v)  //k가 h-1보다 크면서(k가 반으로 나눈 값이 아닐 때), a[k-h]가 v(a[j])보다 크면
				{
					a[k] = a[k-h]; //a[j]에 이전 원소를 저장
					k -= h; //k를 h만큼 감소시킨다
				}
				a[k] = v; //a[k]에 t에 임시 저장했던 a[i]를 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int quickSort(int *a, int n) //퀵 정렬 (n=배열의 크기)
{
	int v, t; //v=피벗, t=임시 저장
	int i, j; //i=왼쪽 인덱스, j=오른쪽 인덱스

	if (n > 1) //배열의 크기가 1보다 클 때
	{
		v = a[n-1];  //피벗으로 배열의 마지막 원소 저장
		i = -1; //왼쪽 인덱스를 -1로 초기화
		j = n - 1; //오른쪽 인덱스를 n-1로 초기화

		while(1)
		{
			while(a[++i] < v); //왼쪽에서부터 피벗보다 큰 값을 찾는다
			while(a[--j] > v); //오른쪽에서부터 피벗보다 작은 값을 찾는다

			if (i >= j) break; //왼쪽 인덱스가 오른쪽 인덱스보다 커지면, 반복문 종료
			//자리 교환
			t = a[i]; //t에 a[i]를 임시 저장
			a[i] = a[j]; //a[i]에 a[j]를 저장
			a[j] = t; //a[j]에 t에 임시 저장했던 a[i]를 저장
		}
		//피벗과 a[i] 교환
		t = a[i]; //t에 a[i]를 임시 저장
		a[i] = a[n-1]; //a[i]에 마지막 원소를 저장
		a[n-1] = t; //마지막 원소에 t에 임시 저장했던 a[i]를 저장

		quickSort(a, i); //재귀로 왼쪽 부분 배열 퀵 정렬
		quickSort(a+i+1, n-i-1); //재귀로 오른쪽 부분 배열을 퀵 정렬
	}

	return 0;
}

int hashCode(int key) {
   //키를 해시 테이블 크기로 나눈 나머지를 반환하여 해시 코드를 계산
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht) //해싱
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //hashtable에 배열 동적 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	//해시 테이블을 -1로 초기화
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);

		if (hashtable[hashcode] == -1) //키의 해시 코드를 계산
		{
			hashtable[hashcode] = key; //해당 해시 코드 위치가 비어있으면 키를 저장
		} else 	{

			index = hashcode; //해시 충돌 발생 시 선형 탐사 방식으로 다음 위치 찾음

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //다음 위치를 계산하여 해시 테이블을 순환하며 빈 공간을 찾음
			}
			hashtable[index] = key; //빈 공간에 키를 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //키의 해시 코드를 계산하여 초기 인덱스 설정

	if(ht[index] == key) //초기 인덱스에 저장된 값이 키와 일치하면 해당 인덱스 반환
		return index;

	while(ht[++index] != key) //다음 위치의 값이 키와 일치할 때까지 순환
	{
		index = index % MAX_HASH_TABLE_SIZE; //해시 테이블 크기를 넘어가면 순환하여 검색
	}
	return index; //일치하는 키를 찾은 인덱스 반환
}
