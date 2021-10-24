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

DWORD LpwstrToDword(LPWSTR str)//������� �� ������ � �����
{
	DWORD dw = 0;
	for (size_t i = 0; i < wcslen(str); i++)//�� ���� �������� ������
	{
		dw += (str[i] - '0');//�������� �����
		dw *= 10;//����������� ������ ����� �� 1
	}
	return dw / 10;//����� �� 10, �.�. ������ ��� ��������� ������
}

LPWSTR ReadCSVFile(LPWSTR path)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD d = 0;//������� ���������� ���� ���� ���������
	DWORD sizeBuffer = 100500;//����� ������
	LPWSTR str = calloc(sizeBuffer, sizeof(WCHAR));//���� ���������
	if (ReadFile(hFile, str, sizeBuffer * sizeof(WCHAR), &d, NULL))
	{
		str[d / 2] = '\0';
		if (d == 0)
		{
			MessageBox(NULL, L"������", L"��� ���� ������ ��� ������������", MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(NULL, L"������", L"������ ��� ������ ������", MB_ICONERROR);
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


