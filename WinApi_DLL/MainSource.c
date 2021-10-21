#include "LibsAndStructs.h"
#define PATH L"UserDataEditor.dll"
#define DATA_PATH L"../Debug/Users.csv"
typedef u*(_cdecl* ReadCSVFile)(LPWSTR);
//typedef int(_cdecl* MyFunction)(LPWSTR);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATH))) return 1;//����������� DLL
    ReadCSVFile Read; //������� ���������� ���� ��������� �� ���������� �������
    Read = (ReadCSVFile)GetProcAddress(MyDLL, "ReadCSVFile");//������������� ��������� �� �������
    u* users = Read(DATA_PATH);
    FreeLibrary(MyDLL);//���������� DLL
    return 0;
}
