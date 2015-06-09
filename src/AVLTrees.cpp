/**
	Created on	: 26 мая 2015 г.
*/
#include "AVLTrees.h"

using std::max;
using std::cout;


/**
	Получить параметр высоты дерева[поле Height в структуре CNode]
*/
int Height(CNode* p)
{
	return p == 0 ? 0 : p->Height;
}

/**
	Функция которая оценивает, нужно ли балансировать дерево
*/
int BalanceFactor(CNode* p)
{
	return Height(p->Left) - Height(p->Right);
}

/**
	Правое вращение дерева
*/
CNode* RotateRight(CNode* p)
{
    CNode* q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    p->Height = max(Height(p->Left), Height(p->Right)) + 1;
	q->Height = max(Height(q->Left), Height(q->Right)) + 1;
	return q;
}

/**
	Левое вращение дерева
*/
CNode* RotateLeft(CNode* p)
{
	CNode* q = p->Right;
	p->Right = q->Left;
	q->Left = p;
	p->Height = max(Height(p->Left), Height(p->Right)) + 1;
	q->Height = max(Height(q->Left), Height(q->Right)) + 1;
	return q;
}

/**
	Балансировка дерева
*/
CNode* Balance(CNode* p)
{
	int balanceFactor = BalanceFactor(p);
	if( balanceFactor == -2 )
	{
		if( BalanceFactor(p->Right) > 0 )
		{
			p->Right = RotateRight(p->Right);
		}
		return RotateLeft(p);
	}
	if( balanceFactor == 2 )
	{
		if( BalanceFactor(p->Left) < 0 )
		{
			p->Left = RotateLeft(p->Left);
		}
		return RotateRight(p);
	}
	p->Height = max(Height(p->Left), Height(p->Right)) + 1;
	return p;
}

/**
	Вставка элемента в дерево
*/
CNode* Insert(CNode* p, int key)
{
	if( p == 0 ) {
		return new CNode(key);
	}
	if( key < p->Key ) {
		p->Left = Insert(p->Left, key);
	} else {
		p->Right = Insert(p->Right, key);
	}
	return Balance(p);
}


/**
	Рекурсивная функция подсчёта высоты дерева.
*/
int Count( CNode* AVLTree )
{
    if( AVLTree == NULL )
        return 0;
    return max(Count( AVLTree->Left ), Count( AVLTree->Right )) + 1;
}

/**
	Освобождение памяти от узла [рекурсивное удаление узла и под узлов]
*/
void free(CNode* node)
{
    if (node == NULL)
        return;
    CNode *bufLeft = node->Left;
    CNode *bufRight = node->Right;
    delete node;

    free(bufLeft);
    free(bufRight);
}

/**
	Поиск ключа в дереве
*/
CNode *find(CNode *tree, int val)
{
    if (tree == NULL) {
        return NULL;
    }
    if (tree->Key == val) {
        return tree;
    }
    if( val < tree->Key ) {
		tree->Left = Insert(tree->Left, val);
	} else {
		tree->Right = Insert(tree->Right, val);
	}
    return NULL;
}

