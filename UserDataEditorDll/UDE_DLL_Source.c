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

__declspec(dllexport) u* ReadCSVFile(LPWSTR path);
u* ReadCSVFile(LPWSTR path)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD d = 0;//сколько фактически байт было прочитано
	DWORD sizeBuffer = 4096;//объем буфера
	LPSTR str = malloc(sizeBuffer+1);//куда считывать
	if (ReadFile(hFile, str, sizeBuffer, &d, NULL)) 
	{
		str[d] = '\0';
		if (strlen(str) == 0)
		{
			MessageBox(NULL, L"Ошибка", L"Ваш файл пустой или отсутствовал", MB_ICONERROR);
			return NULL;
		}
	}
	else
	{
		MessageBox(NULL, L"Ошибка", L"Ошибка при чтении данных", MB_ICONERROR);
		return NULL;
	}

}

u* ParseStr(LPSTR str)
{
	TCHAR* del = L"\n";
	TCHAR* del1 = L";";
	char* p = str;
	int n = 0;
	while (p = strchr(p, "\n"))
		p++, n++;
	free(p);
	LPSTR *arrstr = malloc(n*sizeof(LPSTR));

	LPSTR istr = strtok(str, del);
	for (int i=0;i<n;i++)
	{
		*arrstr[i] = istr;
		istr = strtok(NULL, del);
		i++;
	}
	u* data = malloc(n * sizeof(u));
	for (int i = 1; i < n; i++)
	{
		LPSTR idata, *jdata = malloc(4*sizeof(LPSTR));
		for (int k = 0; k < 4; k++)
		{
			idata = strtok(*arrstr[0], del1);
			jdata[k] = idata;
		}
		data[i].lastname = jdata[0];
		data[i].name = jdata[1];
		data[i].patronymic = jdata[0];
		data[i].old = atoi(jdata[0]);
	}

}

