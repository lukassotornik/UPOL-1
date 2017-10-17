// Prednaska funkce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


char *preved(unsigned int z1, unsigned int z2, char *cislo)
{
	int k = 0;
	for (int j = 0, i = strlen(cislo) - 1; j < strlen(cislo); j++, i--)
	{
		if (cislo[j] >= '0' && cislo[j] <= '9' && (cislo[j] - 48) < z1)     
			k += (cislo[j] - 48) * pow(z1, i);
		else if (cislo[j] >= 'A' && cislo[j] <= 'Z' && (cislo[j] - 55) < z1)
			k += (cislo[j] - 55) * pow(z1, i);
		else
		{
			printf("Je spatne uvedene cislo. Uved'te prosim spravne... \n");
			return NULL;
		}
	}
	char *tmp=(char*)malloc(sizeof(char));
	itoa(k, tmp, z2);
	for (int  j = 0; j < strlen(tmp); j++)
	{
		
		 if ((tmp[j] >= 97) && (tmp[j] <= 122))
		{

			tmp[j] = tmp[j] - 32; 
		}
	}
	return tmp;
}

int main()
{
	printf("Cislo:");
	char *cislo=(char*)malloc(sizeof(char));
	scanf("%s", cislo);
	int z1;
	printf("Zaklad soustavy:");
	scanf("%d", &z1);
	printf("\nPrevest do:");
	int z2;
	scanf("%d", &z2);
	printf("%s v soustave o zakladu %d odpovida %s v soustave o zakladu %d\n", cislo, z1, preved(z1, z2, cislo), z2);
	system("pause");
	return 0;
}

