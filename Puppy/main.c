#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main()
{
	List* head = (List*)malloc(sizeof(List));
	List* tail = head;
	head->Next = NULL;

	if (Setup(tail) == NULL) printf("�ҷ��� ������ �����ϴ�.\n");
	else tail = Setup(tail);

	while (TRUE)
	{
		switch (MenuList())
		{
		case '1':
			tail = AppendList(tail);
			break;
		case '2':
			head = InsertList(head);
			break;
		case '3':
			UpdateList(head);
			break;
		case '4':
			head = DeleteList(head);
			break;
		case '5':
			DisplayList(head);
			break;
		case '0':
			SaveFile(head);
			FreeMallocList(head);
			return;
		default:
			puts("���� �޴�");
		}
	}
	return 0;
}




