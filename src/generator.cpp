/**
	Created on	: 26 мая 2015 г.
	Генератор файла test.txt
*/
#include "generator.h"

bool generateTest(unsigned int amount)
{
    srand(time(NULL));

	set <unsigned int> mr;
    freopen("test.txt","w",stdout);

	while (mr.size() < amount)
	{
		unsigned int ssr= rand();
		ssr = (ssr%(1<< (rand()%32)))+1;		// Формула для увеличения разброса случайной велечины
		if (mr.find(ssr) ==  mr.end())
		{
			mr.insert(ssr);
			cout << ssr << "\n";
		}
	}
    return true;
}
