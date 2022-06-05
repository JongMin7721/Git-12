/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
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
	char command;
	int *array = NULL;
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
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
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

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)		//배열의 메모리 반환
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)			//배열 순서대로 출력
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//원래 배열에 저장 되었던 것들을 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)			//정렬을 위한 반복
	{
		minindex = i;								//최소값의 위치
		min = a[i];									//최소값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)		//비교하기 위한 반복
		{
			if (min > a[j])							//현재최소값이 현재의 키보다 크다면
			{
				min = a[j];							//현재의 키를 최소값으로 지정 후 현재 키의 위치를 저장
				minindex = j;
			}
		}
		a[minindex] = a[i];							//최소값으로 지정된 위치에 정렬되기 전 맨 처음 값을 입력
		a[i] = min;									//정렬되기 전 맨 처음 위치에 최소값을 입력
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);		//정렬된 후의 배열을 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//원래 배열에 저장 되었던 것들을 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)		//정렬을 위한 반복
	{
		t = a[i];							//t에 i번째 키를 저장
		j = i;								//i번 반복을 위한 j
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];					//좌측값보다 우측값이 크다면 좌측값을 우측에 입력
			j--;
		}
		a[j] = t;							//더이상 크지 않을때까지 비교 후 좌측값이 더 커진다면 현 위치에 i번째에서 가져왔던 값 입력
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);		//정렬된 후의 배열을 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//원래 배열에 저장 되었던 것들을 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])					//좌측값보다 우측값이 크다면
			{
				t = a[j-1];						//서로 교환
				a[j-1] = a[j];
				a[j] = t;
			}									//n^2 만큼 반복
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);		//정렬된 후의 배열을 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)				//반복될때마다 h의 값이 1이 될때까지 절반으로 감소
	{
		for (i = 0; i < h; i++)								//반복될때마다 h-1까지 1씩 증가
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)		//반복될때마다 0부터 h만큼 증가
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)				//insertionSort와 동일 방법
				{
					a[k] = a[k-h];							
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)					
	{
		v = a[n-1];		//피봇으로 지정
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);			//피봇보다 큰 값을 찾을때까지 반복해서 증가
			while(a[--j] > v);			//피봇보다 작은 값을 찾을때까지 반복해서 감소

			if (i >= j) break;			//서로의 위치가 역전되었다면 반복문 종료
			t = a[i];					//서로 위치의 값을 교환
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];						//피봇과 피봇보다 큰 값의 위치를 교환
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);				//교환된 피봇위치의 좌측 퀵정렬
		quickSort(a+i+1, n-i-1);		//교환된 피봇위치의 우측 퀵정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)					//해시테이블 초기화						
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];								//배열에 저장된 순서대로 key에 입력
		hashcode = hashCode(key);				//최대 크기로 나눈 나머지를 해시코드로 저장
		/*
		printf("key = %d, hashcode = %d, hashtable[ 해당 해시테이블에 키 입력%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)			//해시테이블이 -1 이라면
		{
			hashtable[hashcode] = key;			//해당 해시테이블에 키 입력
		} else 	{								//아니라면

			index = hashcode;					//index라는 변수에 해시코드를 넣고

			while(hashtable[index] != -1)		//해시테이블이 비어 있을 때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;		//index값을 늘려가며 찾는다.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;								//비어있는 해시테이블을 발견하면 그 위치에 키를 입력
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);				//index에 키를 저장

	if(ht[index] == key)					//해당 위치에 키가 있다면 
		return index;						//위치 반환

	while(ht[++index] != key)				//해시테이블에 키가 있을떄까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;	//최대크기를 넘지 않도록 설정 후
	}
	return index;							//키를 발견하면 위치 반환
}



