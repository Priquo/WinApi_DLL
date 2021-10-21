#include "LibsAndStructs.h"
#define PATH L"UserDataEditor.dll"
typedef u*(_cdecl* ReadCSVFile)(LPWSTR);
//typedef int(_cdecl* MyFunction)(LPWSTR);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATH))) return 1;//����������� DLL
    ReadCSVFile Read; //������� ���������� ���� ��������� �� ���������� �������
    Read = (ReadCSVFile)GetProcAddress(MyDLL, "ReadCSVFile");//������������� ��������� �� �������
    Read(L"�������");
    FreeLibrary(MyDLL);//���������� DLL
    return 0;
}
