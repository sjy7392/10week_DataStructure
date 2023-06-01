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


typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
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
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("[----------------- [Son Ji Yeon] [2020039104] -----------------]\n");	
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left); //왼쪽 서브트리 중위순회
		printf(" [%d] ", ptr->key); //현재 노드 출력
		recursiveInorder(ptr->right); //오른쪽 서브트리 중위순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node); //스택에 현재 노드 저장
		node = pop(); //스택에서 노드를 팝함

		if(!node) break;
		printf(" [%d] ", node->key); //현재 노드 출력

		node = node->right; //오른쪽 자식 노드로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //큐에 루트 노드를 넣는다.

	for(;;)
	{
		ptr = deQueue(); //
		if(ptr) {
			printf(" [%d] ", ptr->key); //현재 노드 출력

			if(ptr->left)
				enQueue(ptr->left); //왼쪽 자식 노드를 큐에 넣음
			if(ptr->right)
				enQueue(ptr->right); //오른쪽 자식 노드를 큐에 넣음
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	//새로운 노드 생성 및 초기화
	Node* newNode = (Node*)malloc(sizeof(Node)); 
	newNode->key = key; //새 노드에 키 지정
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode; //루트 없는 경우, 새 노드를 루트로 설정
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	/* save the parent */

			if(ptr->key > key)
				ptr = ptr->left; //키가 작은 경우 왼쪽 자식으로 이동
			else
				ptr = ptr->right; //키가 큰 경우 오른쪽 자식으로 이동
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //왼쪽 서브트리 재귀적으로 해제
		freeNode(ptr->right); //오른쪽 서브트리 재귀적으로 해제
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //헤드 노드가 자기 자신을 가리키는 경우
	{
		free(head); //헤드 노드를 해제
		return 1;
	}

	Node* p = head->left; //왼쪽 자식을 p로 지정

	freeNode(p);

	free(head);
	return 1;
}


Node* pop()
{
	if (top < 0) return NULL; //스택이 빈 경우
	return stack[top--]; //스택의 top에서 1 감소한 값 리턴
}

void push(Node* aNode)
{
	stack[++top] = aNode; //스택 포인터 하나 증가시킨 후, 스택에 요소 저장
}


void printStack()
{
	int i = 0;

	if (top == -1) {
        printf("Empty.\n");
        return;
    }

	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); //스택의 모든 요소를 순회하며 각 요소의 키 값 출력
	}
}


Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front 1 증가시켜
	return queue[front]; // 큐의 맨 앞에 있는 요소를 반환

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //리어 포인터 1 증가
	if (front == rear) { //큐가 가득 찬 경우 함수 종료
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //큐에 요소 저장
}





