#include "LibsAndStructs.h"
#define PATH L"UserDataEditor.dll"
#define DATA_PATH L"../WinApi_DLL/Users.csv"
typedef u*(_cdecl* ParseStr)(LPWSTR, LPDWORD);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATH))) return 1;//подключение DLL
    ParseStr Read; //создали переменную типа указатель на вызываемую функцию
    Read = (ParseStr)GetProcAddress(MyDLL, "ParseStr");//инициализация указателя на функцию
    DWORD n = 0;
    u* users = Read(DATA_PATH, &n);
    FreeLibrary(MyDLL);//отключение DLL
    return 0;
}
