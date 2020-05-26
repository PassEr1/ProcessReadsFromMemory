#include <iostream>
#include <string>
#include <windows.h>
#define MEM_MAX_SIZE 1000
#define NAME_OF_SHARED_OBJEECT L"SharedMem1"
using namespace std;

void lockMemory() {};


HANDLE createSharedMemory()
{
	return CreateFileMappingW(INVALID_HANDLE_VALUE,
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,
		MEM_MAX_SIZE,
		NAME_OF_SHARED_OBJEECT
	);
}

LPVOID getView(HANDLE hSharedObject)
{
	return MapViewOfFile(
		hSharedObject,
		FILE_MAP_READ,
		0,
		0,
		MEM_MAX_SIZE);
}

wstring ReadFromView(HANDLE hSharedObject, LPVOID offsetOfView) {
	PWCHAR szBuffer = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MEM_MAX_SIZE);
	CopyMemory(szBuffer, offsetOfView, MEM_MAX_SIZE);
	return wstring(szBuffer);
}

int main()
{
	wstring sDataToHandle;
	HANDLE hSharedObject = createSharedMemory();
	LPVOID offsetOfView = getView(hSharedObject);
	while (true)
	{
		lockMemory(); //TODO: implement
		wcout << ReadFromView(hSharedObject, offsetOfView) << endl;
		Sleep(1000);
	}
	CloseHandle(hSharedObject);
}
