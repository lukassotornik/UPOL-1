// 2-Zaokrouhlení.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>



int main()
{
	float x, presnost;;
	printf("Zadejte cislo:");
	scanf_s("%f", &x);
	printf("\nZadejte presnost:");
	scanf_s("%f", &presnost);
	x /= presnost / 10;
	int x1 = x;
	(x1 % 10) >= 5 ? (x = x1 / 10 + 1) : (x = x1 / 10);
	x *= presnost;
	int i = 0;
	for (int j = 0; j == 0; i++)
	{
		presnost *= 10;
		j = presnost;
	}
	printf("%.*f \n", i, x);
	system("pause");
	return 0;
}


