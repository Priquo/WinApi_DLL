#include "../WinApi_DLL/LibsAndStructs.h"

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}

DWORD LpwstrToDword(LPWSTR str)//перевод из строки в число
{
	DWORD dw = 0;
	for (size_t i = 0; i < wcslen(str); i++)//по всем символам строки
	{
		dw += (str[i] - '0');//получаем цифру
		dw *= 10;//увеличиваем разряд числа на 1
	}
	return dw / 10;//делим на 10, т.к. лишний раз увеличили разряд
}

LPWSTR ReadCSVFile(LPWSTR path)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD d = 0;//сколько фактически байт было прочитано
	DWORD sizeBuffer = 100500;//объем буфера
	LPWSTR str = calloc(sizeBuffer, sizeof(WCHAR));//куда считывать
	if (ReadFile(hFile, str, sizeBuffer * sizeof(WCHAR), &d, NULL))
	{
		str[d / 2] = '\0';
		if (d == 0)
		{
			MessageBox(NULL, L"Ошибка", L"Ваш файл пустой или отсутствовал", MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(NULL, L"Ошибка", L"Ошибка при чтении данных", MB_ICONERROR);
	}
	if (str != NULL)
	{
		CloseHandle(hFile);
		return str;
	}
	CloseHandle(hFile);
	return NULL;
}

__declspec(dllexport) u* ParseStr(LPWSTR path, LPDWORD count)
{
	LPWSTR str = ReadCSVFile(path);
	TCHAR* del = L"\n";
	TCHAR* del1 = L";";
	int n = 0, k = 0;
	for (int i = 0; i < wcslen(str); i++)
	{
		if (str[i] == del[0])
			n++;
	}
	*count = n;
	u* data = calloc(n, sizeof(u));
	if (n != 0)
	{
		LPWSTR istr = calloc(n+1, sizeof(WCHAR));
		LPWSTR token = wcstok(str, del, istr);
		while (token != NULL && k<n)
		{
			LPWSTR strT = calloc(wcslen(token)+1, sizeof(WCHAR));
			wcscpy(strT, token);
			LPWSTR jstr = calloc(wcslen(token)+1, sizeof(WCHAR));
			LPWSTR tokenJ = wcstok(strT, del1, jstr);
			data[k].lastname = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].lastname, tokenJ);
			tokenJ = wcstok(NULL, del1, jstr);
			data[k].name = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].name, tokenJ);
			tokenJ = wcstok(NULL, del1, jstr);
			data[k].patronymic = calloc(wcslen(tokenJ) + 1, sizeof(WCHAR));
			wcscpy(data[k].patronymic, tokenJ);
			tokenJ = wcstok(NULL, L"\r", jstr);
			data[k].old = tokenJ != NULL ? LpwstrToDword(tokenJ) : 0;
			token = (LPWSTR)wcstok(NULL, del, istr);
			free(strT);
			free(jstr);
			k++;
		}
		free(token);
		free(istr);
		return data;
	}
	return NULL;
}

__declspec(dllexport) void FindUsers(LPWSTR path, u* datausers)
{
	int n = 0;

}


