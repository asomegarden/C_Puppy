#include "LinkedList.h"

List* Setup(List *p)
{
	FILE* fp;
	fopen_s(&fp, "DATA.txt", "r");

	if (fp == NULL)
	{
		return NULL;
	}
	while (!feof(fp))
	{
		printf("1");
		fgets(p->Name, 50, fp);
		p->Name[strlen(p->Name) - 1] = '\0';

		fgets(p->Feature, 50, fp);
		p->Feature[strlen(p->Feature) - 1] = '\0';

		fscanf_s(fp, "%d", &p->time);

		p->Next = (List*)malloc(sizeof(List));
		p = p->Next;
		p->Next = NULL;
	}
	fclose(fp);
	return p;
}

char MenuList()
{
	int number;
	system("cls");
	puts("��ũ�� ����Ʈ");
	puts("1. �߰�");
	puts("2. ����");
	puts("3. ����");
	puts("4. ����");
	puts("5. ���");
	puts("0. ����");

	printf("��ȣ ���� : ");
	fflush(stdin);
	scanf_s("%d", &number);
	getc(stdin);
	return number;
}
void listmenu(List* head, List* tail)
{
	while (TRUE)
	{
		switch (MenuList())
		{
		case 1:
			tail = AppendList(tail);
			break;
		case 2:
			head = InsertList(head);
			break;
		case 3:
			UpdateList(head);
			break;
		case 4:
			head = DeleteList(head);
			break;
		case 5:
			DisplayList(head);
			break;
		case 0:
			SaveFile(head);
			FreeMallocList(head);
			return;
		default:
			puts("���� �޴�");
		}
	}
}
List* AppendList(List* p)
{
	printf("ǰ������ �Է��ϼ��� : ");
	gets_s(p->Name, sizeof(p->Name));

	printf("���� ��å �ð��� �Է��ϼ���(���� : ��) : ");
	scanf_s("%d", &p->time);
	getc(stdin);

	printf("Ư¡�� �Է��ϼ��� : ");
	gets_s(p->Feature, sizeof(p->Feature));

	p->Next = (List*)malloc(sizeof(List));
	p = p->Next;
	p->Next = NULL;
	return p;
}

int DisplayList(List* p)
{
	int i = 1;
	puts("  ǰ��\t\t���� ��å �ð�\tƯ¡");
	while (p->Next != NULL)
	{
		printf("%d %10s %4d %10s\n", i++, p->Name, p->time, p->Feature);
		p = p->Next;
	}
	system("pause");
	return i - 1;
}

List* InsertList(List* p)
{
	int pos, number;
	List* item;
	List* start = p;
	item = (List*)malloc(sizeof(List));
	number = DisplayList(p);

	do {
		printf("������ ��ġ : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);

	printf("ǰ������ �Է��ϼ��� : ");
	gets_s(p->Name, sizeof(p->Name));

	printf("����� �Է��ϼ��� : ");
	scanf_s("%d", &p->time);
	getc(stdin);

	printf("Ư¡�� �Է��ϼ��� : ");
	gets_s(p->Feature, sizeof(p->Feature));

	if (pos == 1)
	{
		item->Next = p;
		start = item;
	}
	else
	{
		for (int i = 1; i < pos - 1; i++)
		{
			p = p->Next;
		}
		item->Next = p->Next;
		p->Next = item;
	}
	return start;
}

List getData(List* p)
{
	int pos, number;
	number = DisplayList(p);
	do {
		printf("��ȣ ���� : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);
	if (pos == 1)
	{
		return *p;
	}
	else
	{
		int i;
		for (i = 1; i < pos; i++)
		{
			p = p->Next;
		}
		return *p;
	}
}

void UpdateList(List* p)
{
	int pos, number;
	number = DisplayList(p);
	do {
		printf("������ ��ȣ : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);

	if (pos == 1)
	{
		printf("����� ǰ������ �Է��ϼ��� : ");
		gets_s(p->Name, sizeof(p->Name));

		printf("����� ����� �Է��ϼ��� : ");
		scanf_s("%d", &p->time);
		getc(stdin);

		printf("����� Ư¡�� �Է��ϼ��� : ");
		gets_s(p->Feature, sizeof(p->Feature));
	}
	else
	{
		int i;
		for (i = 1; i < pos; i++)
		{
			p = p->Next;
		}
		printf("����� ǰ������ �Է��ϼ��� : ");
		gets_s(p->Name, sizeof(p->Name));

		printf("����� ����� �Է��ϼ��� : ");
		scanf_s("%d", &p->time);
		getc(stdin);

		printf("����� Ư¡�� �Է��ϼ��� : ");
		gets_s(p->Feature, sizeof(p->Feature));
	}
}

List* DeleteList(List* p)
{
	int pos, number;
	List* start = p;
	number = DisplayList(p);
	do
	{
		printf("������ ��ȣ : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);

	if (pos == 1)
	{
		start = p->Next;
		free(p);
	}
	else
	{
		List* tmp;
		for (int i = 1; i < pos - 1; i++)
		{
			p = p->Next;
		}
		tmp = p->Next;
		p->Next = p->Next->Next;
		free(tmp);
	}
	return start;
}

void FreeMallocList(List* p)
{
	List* tmp = p;
	while (p != NULL)
	{
		tmp = p->Next;
		free(p);
		p = tmp;
	}
	puts("���Ͽ� ������");
}

void SaveFile(List* p)
{
	FILE* fp;
	fopen_s(&fp, "DATA.txt", "w");

	if (fp == NULL)
	{
		printf("����\n");
		return;
	}

	while (p->Next != NULL)
	{
		fprintf(fp, "%s\n%s\n%d", p->Name, p->Feature, p->time);
		p = p->Next;
	}
	fclose(fp);
}