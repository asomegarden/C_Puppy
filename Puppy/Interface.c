#include "Interface.h"
#include <Windows.h>
void initscreen()
{
	system("mode con cols=100 lines=40"); //콘솔창 크기 설정
	setTitle("애견 관리 시스템");
	textcolor(10);
	setCur(40, 15);
	printf("애견 관리 시스템\n");
	setCur(32, 25);
	textcolor(15);
	system("pause");
}
void textcolor(int color_number) //텍스트 색 변경
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void setCur(int x, int y) //커서 위치 설정
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setTitle(const char* name) //제목 설정
{
	SetConsoleTitle(name);
}

