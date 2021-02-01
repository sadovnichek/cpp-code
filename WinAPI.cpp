#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE hInputHandle = CreateFile(
		"myFavoriteFile.encrypted",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hInputHandle == INVALID_HANDLE_VALUE)
	{
		cout << "Error on CreateFile, error code: " << GetLastError() << endl;
		return 1;
	}
	cout << "File is OK" << endl;

	LARGE_INTEGER fileSize;
	memset(&fileSize, 0, sizeof(fileSize));

	if (!GetFileSizeEx(hInputHandle, &fileSize))
	{
		cout << "Error on GetFileSizeEx, error code: " << GetLastError() << endl;
		CloseHandle(hInputHandle);
		return 2;
	}

	DWORD fileSizeLowPart = fileSize.LowPart;
	cout << "File size: " << fileSize.LowPart << endl;

	char* buffer = new char[fileSizeLowPart];
	memset(buffer, 0, sizeof(char) * fileSizeLowPart);

	DWORD readed;
	if (!ReadFile(hInputHandle, buffer, fileSizeLowPart, &readed, NULL))
	{
		cout << "Error on ReadFile, error code: " << GetLastError() << endl;
		CloseHandle(hInputHandle);
		delete[] buffer;
		return 3;
	}

	CloseHandle(hInputHandle);
	cout << buffer << endl;

	int magicKey = 3;
	for (int i = 0; i < (int)readed; i++)
	{
		buffer[i] ^= magicKey;
	}

	cout << buffer << endl;

	HANDLE hOutputHandle = CreateFile(
		"myFavoriteFile.decrypted",
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	WriteFile(
		hOutputHandle,
		buffer,
		fileSizeLowPart,
		NULL,
		NULL
	);
	CloseHandle(hOutputHandle);
	return 0;
}
