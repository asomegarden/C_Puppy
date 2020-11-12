#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1

typedef struct List
{
	char Name[50];
	int time; //권장 산책 시간
	char Feature[50]; //단두종, 장모종 등등

	struct List* Next;
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

