#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1

typedef struct List
{
	char Name[50];
	int Coef; //coefficient(계수)
	char Feature[50]; //단두종, 장모종 등등

	struct List* Next;
}List;

List* Setup(List *p);
List* AppendList(List* p);
List* InsertList(List* p);
void UpdateList(List* p);
List* DeleteList(List* p);
int DisplayList(List* p);
void FreeMallocList(List* p);
char MenuList();
void SaveFile(List* p);

