// FunctionSumInTwoHreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <thread> 
#include <Windows.h> 

HANDLE hMutex;

typedef struct MyData {
	int N;
	double result;
} MYDATA, * PMYDATA;

DWORD WINAPI sumParts(LPVOID lpParam) //first part for hThread
{
	for (size_t i = 1; i < floor(((PMYDATA)lpParam)->N / 2); i++)
	{
		WaitForSingleObject(hMutex, INFINITY);
		((PMYDATA)lpParam)->result += pow((-1.0), i) - pow(i, 2 * i); //func 
		ReleaseMutex(hMutex);
	}
	return 0;
}

int main()
{
	PMYDATA pDataArray;
	HANDLE hThread;
	hMutex = CreateMutex(NULL, false, L"");
	int n = 0;
	std::cout << "n?\n";
	std::cin >> n;

	pDataArray = (PMYDATA)malloc(sizeof(MYDATA));

	pDataArray->N = n;
	int nDivTwo = floor(n / 2);
	pDataArray->result = 0;

	hThread = CreateThread(NULL, 0, sumParts, pDataArray, 0, NULL);

	for (int i = nDivTwo; i <= n; i++) //second part for main thread
	{
		WaitForSingleObject(hMutex, INFINITY);
		pDataArray->result += pow((-1.0), i) - pow(i, 2 * i); //func 
		ReleaseMutex(hMutex);
	}

	WaitForSingleObject(hThread, INFINITY);

	std::cout << pDataArray->result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
