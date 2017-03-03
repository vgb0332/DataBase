#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

//struct node
typedef struct _node {
	int key;
	struct _node *right;
	struct _node *left;
}node;

//create a node
node *makeBT(node *left, int key, node *right) {
	node *t;
	//Make a new node T
	t = (node*)malloc(sizeof(node));
	//Connect left, right as child nodes for T
	t->left = left;
	t->right = right;
	//Item into T's data field
	t->key = key;

	return t;
}

//insert x into a binary seartch Tree
node* insertBST(node *bsT, int x)
{
	//search insertion position
	node *p = bsT;
	node *r, *q;
	while (p != NULL) {
		if (x == p->key)
			return bsT; //same key exists
		q = p;
		if (x < p->key)
			p = p->left;
		else
			p = p->right;
	}
	//create new node
	r = makeBT(NULL, x, NULL);
	//insert node

	if (bsT == NULL)
		bsT = r;
	else if (x < q->key)
		q->left = r;
	else
		q->right = r;

	return bsT;
}

//print the tree inorder
void inorder(node *t){
	if (t == NULL)
		return;
	//order: left->current->right
	inorder(t->left);
	printf("%d ", t->key);
	inorder(t->right);
}

//print the tree from
void printTree(node *t, int *sortedSet, int size) {
	node *p = t;
	int i;
	//search for the sortedSet data in the tree
	for (i = 0; i < size; i++) {
		while (p != NULL) {
			//create spaces depending on the depth
			printf("   ");
			if (sortedSet[i] == p->key) {
				printf("%d\n", p->key);
				break;
			}
			else if (sortedSet[i] < p->key)
				p = p->left;
			else
				p = p->right;
		}
		p = t;
	}
}

//shell sort
int* shellSort(int *a, int n) {
	int interval;
	int i, pos, val;

	for (interval = n / 2; interval > 0; interval = interval / 2)
	{
		for (i = interval; i < n; i++)
		{
			val = a[i];
			for (pos = i; pos >= interval; pos -= interval)
			{
				if (val < a[pos - interval]) {
					a[pos] = a[pos - interval];
				}
				else
					break;
			}
			a[pos] = val;
		}
	}
	return a;
}

void generateRandomList(int *set, int size)
{
	int i;
	srand(time(NULL));

	for (i = 0; i < size; i++)
		set[i] = rand() % 1000;
}

void printList(int *set, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", set[i]);
}

int main()
{
	int size;
	int i;
	int *randSet;
	int *sortedSet;
	node *bst;

	//Get an input size from the user
	printf("Enter  Size = ");
	scanf("%d", &size);

	//Allocate space for the randSet
	randSet = (int*)malloc(sizeof(int)*size);
	sortedSet = (int*)malloc(sizeof(int)*size);
	generateRandomList(randSet, size);
	printf("Unsorted Data: ");
	printList(randSet, size);

	//insert randSet data into the Tree
	bst = NULL;
	for (i = 0; i < size; i++)
		bst = insertBST(bst, randSet[i]);

	//sorted set
	sortedSet = shellSort(randSet, size);
	printf("\n\n");

	//print the Tree
	printTree(bst, sortedSet, size);
	
	//print sorted data
	printf("\n\nSorted data: \n\n");
	inorder(bst);
	printf("\n\n");

	return 0;
}