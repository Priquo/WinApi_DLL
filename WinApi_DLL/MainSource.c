#include "LibsAndStructs.h"

#define PATH L"UserDataEditor.dll"
#define DATA_PATH L"../WinApi_DLL/Users1.csv"
#define SEARCH L"ова"

typedef u*(_cdecl* ParseStr)(LPWSTR, LPDWORD);
typedef u* (_cdecl* FindAndWriteUsers)(LPWSTR, u*, DWORD);
typedef DWORD(_cdecl* AverageAge)(u*);


int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE MyDLL;
    if (!(MyDLL = LoadLibrary(PATH))) return 1;
    ParseStr Read; 
    FindAndWriteUsers Find;
    AverageAge AvAge;
    Read = (ParseStr)GetProcAddress(MyDLL, "ParseStr");
    Find = (FindAndWriteUsers)GetProcAddress(MyDLL, "FindAndWriteUsers");
    AvAge = (AverageAge)GetProcAddress(MyDLL, "AverageAge");

    DWORD n = 0;
    u* users = Read(DATA_PATH, &n);
    u* finded = Find(SEARCH, users, n);
    AvAge(finded);

    FreeLibrary(MyDLL);
    return 0;
}
