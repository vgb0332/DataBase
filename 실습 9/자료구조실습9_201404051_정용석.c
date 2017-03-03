#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	char data;
	struct _node *right;
	struct _node *left;
}node;

node *makeBT(node *left, char item, node *right) {
	node *t;
	//Make a new node T
	t = (node*)malloc(sizeof(node));
	//Connect left, right as child nodes for T
	t->left = left;
	t->right = right;
	//Item into T's data field
	t->data = item;

	return t;
}

// Pre order transverse data 
void preorder(node *t)
{
	if (t == NULL)
		return;
	//order: current->left->right

	printf("%c ", t->data);
	preorder(t->left);
	preorder(t->right);
}
// In order transverse data
void inorder(node *t)
{
	if (t == NULL)
		return;
	//order: left->current->right
	inorder(t->left);
	printf("%c ", t->data);
	inorder(t->right);
}
// Post order transverse data
void postorder(node *t)
{
	if (t == NULL)
		return;
	//order: left->right->current
	postorder(t->left);
	postorder(t->right);
	printf("%c ", t->data);
}

void test1()
{
	node *a, *b, *c, *d, *e, *f, *g, *h;
	node *i, *j, *k, *l, *m, *n, *o, *root;

	a = makeBT(NULL, 'A', NULL);
	b = makeBT(NULL, 'B', NULL);
	c = makeBT(NULL, 'C', NULL);
	d = makeBT(NULL, 'D', NULL);
	e = makeBT(NULL, 'E', NULL);
	f = makeBT(NULL, 'F', NULL);
	g = makeBT(NULL, 'G', NULL);
	h = makeBT(NULL, 'H', NULL);

	i = makeBT(a, '*', b);
	j = makeBT(c, '-', d);
	k = makeBT(e, '+', f);
	l = makeBT(g, '/', h);
	m = makeBT(i, '/', j);
	n = makeBT(k, '*', l);
	root = makeBT(m, '+', n);

	printf("Expression: A * B / (C - D) + ( E + F ) * G / H \n\n");

	printf("  Preorder  "); preorder(root); printf("\n");
	printf("  Inorder  "); inorder(root); printf("\n");
	printf("  Postorder  "); postorder(root); printf("\n");
}
void test2()
{
	node *a, *b, *c, *d, *e, *f, *g, *h;
	node *i, *j, *k, *l, *m, *n, *root;

	a = makeBT(NULL, 'A', NULL);
	b = makeBT(NULL, 'B', NULL);
	c = makeBT(NULL, 'C', NULL);
	d = makeBT(NULL, 'D', NULL);
	e = makeBT(NULL, 'E', NULL);
	f = makeBT(NULL, 'F', NULL);
	g = makeBT(NULL, 'G', NULL);
	h = makeBT(NULL, 'H', NULL);

	i = makeBT(a, '+', b);
	j = makeBT(d, '-', e);
	k = makeBT(g, '/', h);
	l = makeBT(i, '*', c);
	m = makeBT(j, '/', f);
	n = makeBT(m, '-', k);
	root = makeBT(l, '+', n);

	printf("Expression: (A + B) * C + ( D - E ) / F - ( G / H )\n\n");

	printf("  Preorder  "); preorder(root); printf("\n");
	printf("  Inorder  "); inorder(root); printf("\n");
	printf("  Postorder  "); postorder(root); printf("\n");
}
void test3()
{
	node *a, *b, *c, *d, *e, *f, *g, *h;
	node *i, *j, *k, *l, *m, *n, *root;

	a = makeBT(NULL, 'A', NULL);
	b = makeBT(NULL, 'B', NULL);
	c = makeBT(NULL, 'C', NULL);
	d = makeBT(NULL, 'D', NULL);
	e = makeBT(NULL, 'E', NULL);
	f = makeBT(NULL, 'F', NULL);
	g = makeBT(NULL, 'G', NULL);
	h = makeBT(NULL, 'H', NULL);

	i = makeBT(b, '+', c);
	j = makeBT(e, '-', f);
	k = makeBT(i, '-', d);
	l = makeBT(j, '+', g);
	m = makeBT(a, '*', k);
	n = makeBT(l, '/', h);
	root = makeBT(m, '*', n);

	printf("Expression: A * ( ( B + C ) - D ) * ( ( E - F ) + G ) / H\n\n");

	printf("  Preorder  "); preorder(root); printf("\n");
	printf("  Inorder  "); inorder(root); printf("\n");
	printf("  Postorder  "); postorder(root); printf("\n");
}


int main()
{
	test1(); printf("\n");
	test2(); printf("\n");
	test3(); printf("\n");
	/*
	node *a, *b, *c, *d, *e, *f, *g, *h;
	node *i, *j, *k, *l, *m, *n, *root;
	
	a = makeBT(NULL, 'A', NULL);
	b = makeBT(NULL, 'B', NULL);
	c = makeBT(NULL, 'C', NULL);
	d = makeBT(NULL, 'D', NULL);
	e = makeBT(NULL, 'E', NULL);
	f = makeBT(NULL, 'F', NULL);
	g = makeBT(NULL, 'G', NULL);
	h = makeBT(NULL, 'H', NULL);

	i = makeBT(b, '+', c);
	j = makeBT(e, '*', f);
	k = makeBT(g, '*', h);
	l = makeBT(a, '*', i);
	m = makeBT(d, '/', j);
	n = makeBT(l, '-', m);
	root = makeBT(n, '+', k);
	
	printf("Expression ~~~\n\n");

	printf("  Preorder  "); preorder(root); printf("\n");
	printf("  Inorder  "); inorder(root); printf("\n");
	printf("  Postorder  "); postorder(root); printf("\n");
	*/
	return 0;
}