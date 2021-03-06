// cv-5.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
using namespace std;

CRITICAL_SECTION CSs;
CRITICAL_SECTION CSc;

struct Args {
	int *number;
	FILE *file;
};

DWORD WINAPI hledat(CONST LPVOID lpParam) {
	Args arg = *((Args*)lpParam);

	while (true)
	{
		EnterCriticalSection(&CSs);
		int my_record;
		fread(&my_record, sizeof(int), 1, arg.file);
		LeaveCriticalSection(&CSs);
		if (feof(arg.file)) break;

		EnterCriticalSection(&CSc);
		int *num = arg.number;
		if (*num == 1) {
			LeaveCriticalSection(&CSc); 
			break; 
		}
		while (*num % my_record == 0) {
			cout << my_record << ",";
			*num /= my_record;
		}
		LeaveCriticalSection(&CSc);
	}

	ExitThread(0);
}

int main() {
	HANDLE hThreads[2];

	char Filtr[30];
	cout << "Enter number" << endl;
	int *C = new int;
	cin >> *C;
	if (*C < 2) return 0;

	FILE *ptr_myfile;
	ptr_myfile = fopen("..\\Prvocisla", "rb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}

	Args args = { C,ptr_myfile };

	hThreads[0] = CreateThread(NULL, 0, &hledat, &args, CREATE_SUSPENDED, NULL);
	if (NULL == hThreads[0]) {
		cout << "Error in Thread creation" << endl;
	}
	hThreads[1] = CreateThread(NULL, 0, &hledat, &args, CREATE_SUSPENDED, NULL);
	if (NULL == hThreads[1]) {
		cout << "Error in Thread creation" << endl;
	}


	assert(hThreads[0] && hThreads[1]);
	InitializeCriticalSection(&CSs);
	InitializeCriticalSection(&CSc);


	ResumeThread(hThreads[0]);
	ResumeThread(hThreads[1]);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	fclose(ptr_myfile);

	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);


	DeleteCriticalSection(&CSs);
	DeleteCriticalSection(&CSc);

	cout << "***" << *C << endl;
	char x;
	cin >> x;
	ExitProcess(0);
}

