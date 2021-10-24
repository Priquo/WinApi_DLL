#include "LibsAndStructs.h"
#define PATH L"UserDataEditor.dll"
#define DATA_PATH L"../WinApi_DLL/Users.csv"
typedef u*(_cdecl* ParseStr)(LPWSTR, LPDWORD);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATH))) return 1;//����������� DLL
    ParseStr Read; //������� ���������� ���� ��������� �� ���������� �������
    Read = (ParseStr)GetProcAddress(MyDLL, "ParseStr");//������������� ��������� �� �������
    DWORD n = 0;
    u* users = Read(DATA_PATH, &n);
    FreeLibrary(MyDLL);//���������� DLL
    return 0;
}
