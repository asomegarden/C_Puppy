#include <stdio.h>
#include <stdlib.h>
#include "Dogmanagefunc.h"
#include "Interface.h"

int main()
{
	int refresh = 1;
	initscreen();
	while (refresh)
	{
		dogstate_screen(&refresh); //refresh�� 0�� �Ǹ� ���α׷� ����
	}
	return 0;
}




