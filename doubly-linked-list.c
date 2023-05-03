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

typedef struct Node {	//리스트 노드 구조체 정의
	int key;	//노드에 입력할 값 변수
	struct Node* llink;	//왼쪽으로 이동할 링크 포인터
	struct Node* rlink;	//오른쪽으로 이동할 링크 포인터
} listNode;

typedef struct Head {	//헤드 노드 구조체 정의
	struct Node* first;	//헤드 노드 다음 노드를 가리킬 포인터
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);


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
	printf("[----- [Jeong Hanul] [2020039076] -----]\n\n");

	
	char command;	//명령어를 입력 받을 변수
	int key;	//값을 입력 받을 변수
	headNode* headnode=NULL;	//헤드 노드를 선언하고 NULL 값으로 초기화

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
		scanf(" %c", &command);	//명령어를 입력받아 command에 저장

		switch(command) {
		case 'z': case 'Z':	//z or Z 입력 시
			initialize(&headnode);
			break;
		case 'p': case 'P':	//p or P 입력 시
			printList(headnode);
			break;
		case 'i': case 'I':	//i or I 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//노드에 넣을 key 값 입력
			insertNode(headnode, key);
			break;
		case 'd': case 'D':	//d or D 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//노드에서 삭제할 key 값 입력
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':	//n or N 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//마지막 노드에 넣을 key 값 입력
			insertLast(headnode, key);
			break;
		case 'e': case 'E':	//e or E 입력 시
			deleteLast(headnode);
			break;
		case 'f': case 'F':	//f or F 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//처음 노드에 넣을 key 값 입력
			insertFirst(headnode, key);
			break;
		case 't': case 'T':	//t or T 입력 시
			deleteFirst(headnode);
			break;
		case 'r': case 'R':	//r or R 입력 시
			invertList(headnode);
			break;
		case 'q': case 'Q':	//q or Q 입력 시
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//q or Q 입력시 while문 탈출

	return 1;
}


int initialize(headNode** h) {	//헤드 노드를 초기화하는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));	//매개변수로 받은 헤드 노드 h에 headNode 사이즈만큼 동적 할당
	(*h)->first = NULL;	//헤드 노드가 가리키는 포인터를 NULL로 초기화
	return 1;
}

int freeList(headNode* h){	//모든 노드 메모리 해제하는 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;	//리스트 노드 포인터 p를 선언하고 h의 first로 초기화

	listNode* prev = NULL;	//리스트 노드 포인터 prev를 선언하고 NULL로 초기화
	while(p != NULL) {	//p가 NULL이 아닌 동안 반복
		prev = p;	//prev에 p를 대입
		p = p->rlink;	//p에 rlink가 가리키는 오른쪽 노드를 대입
		free(prev);	//prev 메모리 해제
	}
	free(h);	//h 메모리 해제
	return 0;
}


void printList(headNode* h) {	//리스트 노드의 순서와 값을 차례대로 출력하는 함수
	int i = 0;	//변수 i를 선언하고 0으로 초기화
	listNode* p;	//리스트 노드 포인터 p를 선언

	printf("\n---PRINT\n");

	if(h == NULL) {	//헤드 노드 h에 값이 없다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;	//p에 헤드 노드가 가리키는 다음 노드 대입

	while(p != NULL) {	//p가 NULL이 아닌 동안
		printf("[ [%d]=%d ] ", i, p->key);	//i번째의 key 값 출력
		p = p->rlink;	//p에 다음 노드를 대입
		i++;
	}

	printf("  items = %d\n", i);	//노드의 총 개수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {	//노드에 값을 입력하고 가장 마지막 순서로 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//리스트 노드 node를 선언하고 동적 할당
	node->key = key;	//node의 key 값에 입력 받은 key 대입
	node->rlink = NULL;	//node의 오른쪽을 가리키는 포인터를 NULL로 초기화
	node->llink = NULL;	//node의 왼쪽을 가리키는 포인터를 NULL로 초기화

	if (h->first == NULL)	//헤드 노드의 포인터가 NULL 값인 경우
	{
		h->first = node;	//헤드 노드의 포인터에 node를 대입
		return 0;
	}

	listNode* n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화
	while(n->rlink != NULL) {	//n의 오른쪽 노드가 NULL이 아닌 동안
		n = n->rlink;	//n에 오른쪽 노드를 대입
	}
	n->rlink = node;	//n의 오른쪽을 가리키는 포인터에 node를 대입
	node->llink = n;	//node의 왼쪽을 가리키는 포인터에 node를 대입
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {	//마지막 노드를 삭제하는 함수

	if (h->first == NULL)	//헤드 노드의 포인터가 NULL이면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화
	listNode* trail = NULL;	//리스트 노드 포인터 trail을 선언하고 NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {	//n의 오른쪽을 가리키는 포인터가 NULL이면
		h->first = NULL;	//헤드 노드의 포인터에 NULL 대입
		free(n);	//n 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {	//n의 오른쪽을 가리키는 포인터가 NULL이 아닌 동안
		trail = n;	//trail에 n 대입
		n = n->rlink;	//n에 오른쪽 노드 대입
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail의 오른쪽을 가리키는 포인터에 NULL 대입
	free(n);	//n 메모리 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {	//노드에 값을 입력하고 가장 처음 순서로 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//리스트 노드 node를 선언하고 동적 할당
	node->key = key;	//node의 key 값에 입력 받은 key 대입
	node->rlink = node->llink = NULL;	//node의 양쪽 포인터를 NULL로 초기화

	if(h->first == NULL)	//헤드 노드의 포인터가 NULL이면
	{
		h->first = node;	//헤드 노드의 포인터에 node 대입
		return 1;
	}

	node->rlink = h->first;	//node의 오른쪽을 가리키는 포인터에 헤드 노드의 포인터를 대입
	node->llink = NULL;	//node의 왼쪽을 가리키는 포인터에 NULL 대입

	listNode *p = h->first;	//리스트 노드 포인터 p를 선언하고 헤드 노드의 포인터로 초기화
	p->llink = node;	//p의 왼쪽을 가리키는 포인터에 node를 대입
	h->first = node;	//헤드 노드의 포인터에 node 대입

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {	//첫번째 노드를 삭제하는 함수

	if (h->first == NULL)	//헤드 노드의 포인터가 NULL이면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화
	h->first = n->rlink;	//헤드 노드의 포인터에 n의 오른쪽을 가리키는 포인터를 대입

	free(n);	// n 메모리 해제 

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {	//노드의 순서를 역순으로 재배치하는 함수


	if(h->first == NULL) {	//헤드 노드의 포인터가 NULL이면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화
	listNode *trail = NULL;	//리스트 노드 포인터 trail을 선언하고 NULL로 초기화
	listNode *middle = NULL;	//리스트 노드 포인터 middle을 선언하고 NULL로 초기화

	while(n != NULL){	//n이 NULL이 아닌 동안
		trail = middle;	//trail에 middle 대입
		middle = n;	//middle에 n 대입
		n = n->rlink;	//n에 n의 오른쪽을 가리키는 포인터 대입
		middle->rlink = trail; //middle의 오른쪽을 가리키는 포인터에 trail 대입
		middle->llink = n;	//middle의 왼쪽을 가리키는 포인터에 n 대입
	}

	h->first = middle;	//헤드 노드의 포인터에 middle 대입

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {	//노드에 값을 대입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//리스트 노드 node를 선언하고 동적 할당
	node->key = key;	//node의 key 값에 입력 받은 key 대입
	node->llink = node->rlink = NULL;	//node의 양쪽 포인터를 NULL로 초기화

	if (h->first == NULL)	//헤드 노드의 포인터가 NULL이면
	{
		h->first = node;	//헤드 노드의 포인터에 node 대입
		return 0;
	}

	listNode* n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {	//n이 NULL이 아닌 동안
		if(n->key >= key) {	//리스트 노드 n의 key 값이 입력 받은 key 값보다 크거나 같으면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//리스트 노드 n이 헤드 노드의 포인터와 같다면
				insertFirst(h, key);	//가장 처음 순서로 삽입하는 함수 호출
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;	//node의 오른쪽을 가리키는 포인터에 n을 대입
				node->llink = n->llink;	//node의 왼쪽을 가리키는 포인터에 n의 왼쪽을 가리키는 포인터를 대입
				n->llink->rlink = node;	//n의 왼쪽 노드의 오른쪽을 가리키는 포인터에 node 대입
			}
			return 0;
		}

		n = n->rlink;	//n에 n의 오른쪽 노드를 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);	//가장 마지막 순서로 삽입하는 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {	//해당하는 key 값인 노드 제거하는 함수

	if (h->first == NULL)	//헤드 노드의 포인터가 NULL인 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;	//리스트 노드 포인터 n을 선언하고 헤드 노드의 포인터로 초기화

	while(n != NULL) {	//n이 NULL 값이 아닌 동안
		if(n->key == key) {	//n의 key 값과 입력 받은 key 값이 같다면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);	//첫번째 노드를 삭제하는 함수 호출
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);	//마지막 노드를 삭제하는 함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;	//n의 왼쪽 노드의 오른쪽을 가리키는 포인터에 n의 오른쪽을 가리키는 포인터를 대입
				n->rlink->llink = n->llink;	//n의 오른쪽 노드의 왼쪽을 가리키는 포인터에 n의 왼쪽을 가리키는 포인터를 대입
				free(n);	//n 메모리 해제
			}
			return 1;
		}

		n = n->rlink;	//n에 n의 오른쪽 노드 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key  =  %d\n", key);
	return 1;
}