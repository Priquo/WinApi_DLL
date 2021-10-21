#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

struct UsersData;
typedef struct UsersData u;

struct UsersData
{
	LPSTR lastname, name, patronymic;
	int old;
};
