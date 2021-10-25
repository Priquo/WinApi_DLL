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

__declspec(dllexport) u* FindAndWriteUsers(LPWSTR search, u* datausers, DWORD k)
{	
	int n = 0;
	u* searchedUsers = calloc(k, sizeof(u));
	for (int i = 0; i < k; i++)
	{
		if (wcsstr(datausers[i].lastname, search))
		{
			searchedUsers[n].lastname = calloc(wcslen(datausers[i].lastname) + 1, sizeof(WCHAR));
			wcscpy(searchedUsers[n].lastname, datausers[i].lastname);
			searchedUsers[n].name = calloc(wcslen(datausers[i].name) + 1, sizeof(WCHAR));
			wcscpy(searchedUsers[n].name, datausers[i].name);
			searchedUsers[n].patronymic = calloc(wcslen(datausers[i].patronymic) + 1, sizeof(WCHAR));
			wcscpy(searchedUsers[n].patronymic, datausers[i].patronymic);
			searchedUsers[n].old = datausers[i].old;
			n++;
		}
	}
	HANDLE hFile = CreateFile(RESULT_FILE, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD d = 0;
	TCHAR bugg[SIZE_BUFFER];
	LPWSTR MyString = calloc(100500, sizeof(WCHAR));
	swprintf(bugg, SIZE_BUFFER, TEXT("%s;%s;%s;%d\r\n"), searchedUsers[0].lastname, searchedUsers[0].name, searchedUsers[0].patronymic, searchedUsers[0].old);
	wcscpy(MyString, bugg);
	for (int i = 1; i < n; i++)
	{
		swprintf(bugg, SIZE_BUFFER, TEXT("%s;%s;%s;%d\r\n"), searchedUsers[i].lastname, searchedUsers[i].name, searchedUsers[i].patronymic, searchedUsers[i].old);
		wcscat(MyString, bugg);
		//free(bugg);
	}
	if (MyString != NULL)
		WriteFile(hFile, MyString, wcslen(MyString) * sizeof(TCHAR), d, NULL);
	CloseHandle(hFile);
	return searchedUsers;
}

__declspec(dllexport) DWORD AverageAge(u* users)
{
	DWORD summ = 0, avAge = 0;
	int n = 0;
	while (users[n].old != NULL)
	{
		summ += users[n].old;
		n++;
	}
	avAge = summ / n;
	HANDLE hFile = CreateFile(RESULT_FILE, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD d = 0;
	TCHAR bugg[100];
	swprintf(bugg, 100, TEXT("Средний возраст пользователей равен %d\n"), avAge);
	SetFilePointer(hFile, 0, NULL, FILE_END);
	WriteFile(hFile, bugg, wcslen(bugg) * sizeof(TCHAR), d, NULL);
	CloseHandle(hFile);
	return avAge;
}


