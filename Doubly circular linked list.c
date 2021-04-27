#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */



typedef struct Node { //원형 리스트 생성을 위한 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); // listNode h에 메모리 할당 함수
int freeList(listNode* h); // listNode h에 메모리 헤제 함수
int insertLast(listNode* h, int key); // key 값에 대한 마지막에 노드 추가 함수
int deleteLast(listNode* h); // 리스트의 마지막 노드 삭제 함수
int insertFirst(listNode* h, int key); // key 값에 대한 리스트의 처음 노드 추가 함수
int deleteFirst(listNode* h); // 리스트의 처음 노드 삭제 함수
int invertList(listNode* h); // 역순 함수

int insertNode(listNode* h, int key); // key보다 큰 값 앞에 리스트의 key 값 노드 삽입하는 함수
int deleteNode(listNode* h, int key); // key 값에 대한 리스트에 있는 노드 삭제 함수

void printList(listNode* h); // 리스트에 있는 모든 노드들을 출력하는 함수



int main()
{
	char command; // 정수형 변수 command 생성
	int key; // 정수형 변수 key 생성
	listNode* headnode=NULL; // 구조체에서 포인터형 변수 headnode를 생성한 뒤 NULL 삽입
	printf("----- [민선홍] [2018038028] -----");

	do{ // command의 값에 따라 실행하는 반복문 실행
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
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
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

	}while(command != 'q' && command != 'Q'); // q나 Q가 입력될 때 까지 위에 상황들 반복

	return 1;
}


int initialize(listNode** h) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){ // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.

	free(h); // listNode 포인터 h 메모리 해제

	return 0;
}



void printList(listNode* h) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤더노드에 들어있는 값이 없으면, 출력할 게 없다고 프린트문 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // h->rlink 값 대입 (h가 rlink를 가리키는 값이라고 생각하면 된다)

	while(p != NULL && p != h) { // 원형 리스트에 들어가있는 p -> key 값 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode 포인터 node 메모리 할당
	node -> key = key; // node -> key에 key의 값 대입(node가 가리키는 key의 값이라고 생각하면 된다)
	node -> rlink = NULL; // node -> rlink 값에 NULL 대입
	node -> llink = NULL; // node -> llink 값에 NULL 대입

	node -> rlink = h; // node -> rlink 값에 헤더노드 대입
	node -> llink = h -> llink; // node -> llink 값에 헤더노드 -> llink 값 대입
	h -> llink -> rlink = node; // 헤더노드 -> llink -> rlink 값에 node 대입
	h -> llink = node; // 헤더노드 -> llink 값에 node 대입

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.
	listNode *del = (listNode*)malloc(sizeof(listNode)); // listNode 포인터 변수 del 메모리 할당
	listNode *p; // listNode 포인터 변수 p 생성
	p = h; // p에 헤더노드 대입

	if( h -> llink == h) // 만약 헤더노드 -> llink의 값이 헤더노드이면 지울 노드가 없다는 문장 출력
	{
		printf("지울 노드가 없습니다.\n");
		return 1;
	}

	del = p -> llink; // del에 p -> llink의 값 대입
	p = p -> llink; // p에 p -> llink 값 대입
	p->llink->rlink = h; // p -> llink -> rllink값에 헤더노드 대입
	h -> llink = p -> llink; // 헤더노드 -> llink 값에 p -> llink 값 대입

	free(del); // p -> llink 값이 들어가 있는 del 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.
	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode 포인터 node 메모리 할당
	node -> key = key; // node -> key에 key의 값 대입
	node -> rlink = NULL; // node -> rlink 값에 NULL 대입
	node -> llink = NULL; // node -> llink 값에 NULL 대입

	node -> rlink = h -> rlink; // node -> rlink 값에 헤더노드 -> rlink 값 대입
	node -> llink = h; // node -> llink 값에 헤더노드 대입
	h -> rlink -> llink = node; // h -> rlink -> llink 값에 node 대입
	h -> rlink = node; // 헤더노드 -> rlink 값에 node 대입


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.
	listNode *del = (listNode*)malloc(sizeof(listNode)); // listNode 포인터 변수 del 메모리 할당
	listNode *p; // listNode 포인터형 변수 p 생성
	p = h; // p에 헤더노드 대입

	if( h -> rlink == h) // 헤더노드 -> rlink 값이 헤더노드면 지울 노드가 없다는 문장 출력
	{
		printf("지울 노드가 없습니다.\n");
		return 1;
	}

	del = p -> rlink; // del에 p -> rlink 값 대입
	p = p -> rlink; // p에 p -> rlink 값 대입
	p -> rlink -> llink = h; // p -> rlink -> llink 값에 헤더노드 대입
	h -> rlink = p -> rlink; // 헤더노드 -> rlink 값에 p -> rlink 값 대입
	free(del); // p -> rlink 값이 들어가 있는 del 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.
	listNode *p, *q, *r; // listNode 포인터형 변수 p q r 생성;
	p = h; // p에 헤더노드 대입
	q = NULL; // q가 가리키는 값은 NULL로 초기화
	r = NULL; // r이 가리키는 값은 NULL로 초기화

	if (h -> rlink == h) // 헤더노드 -> rlink 값이 h와 같다면 종료
	{
		return 0;
	}

	while (1) // 반복문을 실행하여, 역순으로 만들기
	{
		r = q ; // r에 q 값 대입
		q = p; // q에 p 값 대입
		p = p -> rlink; // p에 p -> rlink 값 대입
	    q -> llink = p; // q -> llink 값에 q 대입
	    q -> rlink = r; // q -> rlink 값에 r 대입

	    if(p == h) // p가 헤더노드이면
	    {
	    	p -> rlink = q; //p -> rlink 값에 q 대입
	    	break;
	    }
	}

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) { // 주석에 ?? -> ?? 값 이렇게 되어있으면 ??가 ??를 가리키는 값이라고 생각하면 됩니다.

	return 0;
}

