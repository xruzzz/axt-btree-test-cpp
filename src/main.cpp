/*
	Аргументы
	-g - генерация файла test.txt
	RBTree:
	-tRBs-оценка поиска в дереве в зависимости от количества элементов
	-tRBh-оценка высоты дерева в зависимости от количества элементов
	AVLTree:
	-tAVLs-оценка поиска в дереве в зависимости от количества элементов
	-tAVLh-оценка высоты дерева в зависимости от количества элементов
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include "generator.h"
#include "timer.h"
#include "RBTrees.h"
#include "AVLTrees.h"

// Код ниже, чтоб не писать постоянно "std::"
using std::map;
using std::cout;
using std::endl;
using std::string;

extern struct node NIL;			//  Без extern не сможем использовать struct node NIL, которая создаётся в RBTrees.cpp
extern NODEPTR NILPTR;

/**
 	 Поиск параметра командной строки в списке параметров
*/
bool findArg(map <string, string> mm, string vv)
{
	if (mm.find(vv) !=  mm.end()) return true;
	return false;
}

/**
	Функция тестирования времени поиска в зависимости от количества элементов в АВЛ дереве
 */
bool testSearchAVL(unsigned int nn)
{
    CNode *tree = NULL;
    freopen("test.txt","r",stdin);//переключаем поток на ввод из файла
    freopen("dataSearchAVL.cvs","w",stdout);		// переключаем поток на вывод в файл
    int buf;
    int count = 1;
    long long int start;
    for (unsigned int i = 0; i < nn; i++)
    {
        scanf("%i", &buf);
        tree = Insert(tree, buf);			// Добавляем новый элемент в дерево

        if (!(i % count)) {					// if чтобы не считать поиск для каждого элемента
            if (count < 25000) {
                count *= 10;
            }
            Timer tt;						// Создаём объект таймера, иначе не сможем вызвать getTicks
            start = tt.getTicks();			// Фиксируем время начала измерений
            tree = find(tree, i);
            cout << i << "," << (unsigned long)((tt.getTicks() - start)*1000000000UL) << "\n";
        }
    }

    free(tree);								// Освобождаем память
	return true;
}

/**
	Функция тестирования высоты в зависимости от количества элементов в АВЛ дереве
*/
bool testCountAVL(unsigned int nn)
{
    CNode *tree = NULL;
    freopen("test.txt","r",stdin);				//переключаем поток на ввод из файла
    freopen("dataCountAVL.cvs","w",stdout);		// переключаем поток на вывод в файл
    int buf;
    for (unsigned int i = 0; i < nn; i++) {
        scanf("%i", &buf);
        tree = Insert(tree, buf);
        if (!(i % 10)) {
            cout << i << ","<< tree->Height << "\n";
        }
    }

    free(tree);
	return true;
}

/**
	Функция тестирования времени поиска в зависимости от количества элементов в Красно-чёрном дереве
*/
bool testSearchRB(unsigned int nn)
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;

    freopen("test.txt","r",stdin);				//переключаем поток на ввод из файла
    freopen("dataSearchRB.cvs","w",stdout);		// переключаем поток на вывод в файл
    int buf;

	int count = 1;
	long long int start;

    // Цикл для подсчёта зависимости времени поиска от количества элементов
 	for (unsigned int i = 0; i < nn; i++)
	{
        scanf("%i", &buf);							// Читаем из потока ввода
        rbinsert(&tree, buf);						// Добавляем новый элемент в дерево
        if (!(i % count)) {							// Если остаток от деления i на count равен 0 то выполнить :
            if (count < 25000) {
                count *= 10;
            }
            Timer tt;
            start = tt.getTicks();
            search(tree, buf);
            cout << i << "," << (unsigned int)((tt.getTicks() - start)*1000000000UL) << "\n";
        }
    }
	return true;
}

/**
	Функция тестирования высоты в зависимости от количества элементов в Красно-чёрном дереве
*/
bool testCountRB(unsigned int nn)
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;

    freopen("test.txt","r",stdin);				// переключаем поток на ввод из файла
    freopen("dataHeightRB.cvs","w",stdout);		// переключаем поток на вывод в файл
    int buf;
    for (unsigned int i = 0; i < nn; i++)
    {
        scanf("%i", &buf);
        rbinsert(&tree, buf);
        if (!(i % 1000)) {
            cout << i << "," << Count(tree) << endl;
        }
    }

	return true;
}

int main(int argc, const char * argv[])
{
	const unsigned int NUM_ELEMENTS = 25000000;
    map <string, string> listArg;
//    listArg["-g"] = "";				//	Для указания аргументов запуска в коде
    for (int i = 1; i < argc; i++)		// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
    	listArg[argv[i]] = "";
    }

	if (listArg.size())					// если в котейнере listArg есть аргументы, которые передал пользователь
	{
		if (findArg(listArg, "-g"))
		{
			cout << "Generation of test file. Please wait ...  "<<endl;
			generateTest(NUM_ELEMENTS);
		}
		else
			if (findArg(listArg, "-tRBs"))			// Выбрано красно-чёрное дерево, будет выполнена оценка скорости выполнения поиска
			{
				cout << "RB Tree Search rate. Please wait ..."<<endl;
				testSearchRB(NUM_ELEMENTS);
			}
			else
			{
				if (findArg(listArg, "-tRBh"))			// Выбрано красно-чёрное дерево, будет выполнена оценка высоты дерева
				{
					cout << "RB Tree height rate. Please wait ..."<<endl;
					testCountRB(NUM_ELEMENTS);
				}
				else
					if (findArg(listArg, "-tAVLs")) // Выбрано АВЛ дерево, будет выполнена оценка скорости выполнения поиска
					{
						cout << "AVL Tree Search rate. Please wait ..."<<endl;
						testSearchAVL(NUM_ELEMENTS);
					}
					else
						if (findArg(listArg, "-tAVLh"))//  Выбрано АВЛ дерево, будет выполнена оценка высоты дерева
						{
							cout << "AVL Tree height rate. Please wait ..."<<endl;
							testCountAVL(NUM_ELEMENTS);
						}
						else
						{
							cout << "Unknown arguments" << endl;
						}
			}
	} else
	{
		cout << "Not arguments" << endl;
	}


    return 0;
}
