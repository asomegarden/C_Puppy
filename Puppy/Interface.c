#include "Interface.h"
#include <Windows.h>
void initscreen()
{
	system("mode con cols=100 lines=40");
	textcolor(10);
	setCur(30, 10);
	printf("애견 관리 시스템\n");
	setCur(20, 20);
	textcolor(15);
	system("pause");
}
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void setCur(int x, int y)
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setTitle(const char* name)
{
	SetConsoleTitle(name);
}

