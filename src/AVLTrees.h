/**
	Created on	: 26 мая 2015 г.
	АВЛ дерево
*/

#ifndef AVLTREES_H_
#define AVLTREES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct CNode {
    int Key;				// Ключ узла
	int Height;				// Хранит высоту узла
    CNode* Left;			// Указатель на узел в левой ветке
	CNode* Right;			// Указатель на узел в правой ветке

	CNode(int key) : Key(key), Height(1), Left(0), Right(0) {}			// Инициализация полей структуры
};

int Height(CNode* p);
int BalanceFactor(CNode* p);
CNode* RotateRight(CNode* p);
CNode* RotateLeft(CNode* p);
CNode* Balance(CNode* p);
CNode* Insert(CNode* p, int key);
int Count( CNode*);
void free(CNode*);
CNode *find(CNode *, int);

#endif
