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
		dogstate_screen(&refresh); //refresh가 0이 되면 프로그램 종료
	}
	return 0;
}




