#include "Interface.h"
#include <Windows.h>
void initscreen()
{
	system("mode con cols=100 lines=40"); //�ܼ�â ũ�� ����
	setTitle("�ְ� ���� �ý���");
	textcolor(10);
	setCur(40, 15);
	printf("�ְ� ���� �ý���\n");
	setCur(32, 25);
	textcolor(15);
	system("pause");
}
void textcolor(int color_number) //�ؽ�Ʈ �� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void setCur(int x, int y) //Ŀ�� ��ġ ����
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setTitle(const char* name) //���� ����
{
	SetConsoleTitle(name);
}

