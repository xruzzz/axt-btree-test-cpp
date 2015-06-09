/**
	Created on	: 26 мая 2015 г.
	Красно-черное дерево
*/

#ifndef RBTREES_H_
#define RBTREES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define RED		1
#define BLACK	2

struct node {
	int key;
	struct node *left, *right, *p;
	int color;

};

typedef struct node *NODEPTR;

NODEPTR search(NODEPTR, int);
void leftrotate(NODEPTR *, NODEPTR);
void rightrotate(NODEPTR *, NODEPTR);
void rbinsertfixup(NODEPTR *, NODEPTR);

void rbinsert(NODEPTR *, int);
int Count( NODEPTR );


#endif
