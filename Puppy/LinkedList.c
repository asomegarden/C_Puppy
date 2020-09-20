#include "LinkedList.h"

List* Setup(List *p)
{
	FILE* fp;
	fopen_s(&fp, "DATA.bin", "rb");

	if (fp == NULL)
	{
		return NULL;
	}
	while (!feof(fp))
	{
		printf("adsfdas\n");
		fread(p, sizeof(List), 1, fp);
		p->Next = (List*)malloc(sizeof(List));
		p = p->Next;
		p->Next = NULL;
	}
	fclose(fp);
	return p;
}

char MenuList()
{
	char number;
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
	number = getchar();
	getc(stdin);
	return number;
}
List* AppendList(List* p)
{
	printf("ǰ������ �Է��ϼ��� : ");
	gets_s(p->Name, sizeof(p->Name));

	printf("����� �Է��ϼ��� : ");
	scanf_s("%d", &p->Coef);
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
	puts("ǰ��\t\t���\tƯ¡");
	while (p->Next != NULL)
	{
		printf("%3d %20s %4d %10s\n", i++, p->Name, p->Coef, p->Feature);
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
	scanf_s("%d", &p->Coef);
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
		scanf_s("%d", &p->Coef);
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
		scanf_s("%d", &p->Coef);
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
	fopen_s(&fp, "DATA.bin", "wb");

	if (fp == NULL)
	{
		printf("����\n");
		return;
	}

	while (p->Next != NULL)
	{
		fwrite(p, sizeof(p), 1, fp);
		p = p->Next;
	}
	fclose(fp);
}