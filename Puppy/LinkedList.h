#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1

typedef struct List
{
	char Name[50]; //ǰ����
	int time; //���� ��å �ð�
	char Feature[50]; //Ư¡

	struct List* Next; //��ũ
}List;

List* Setup(List *p);
List* AppendList(List* p);
List* InsertList(List* p);
void listmenu(List* head, List* tail);
void UpdateList(List* p);
List* DeleteList(List* p);
List getData(List* p);
int DisplayList(List* p);
void FreeMallocList(List* p);
char MenuList();
void SaveFile(List* p);

