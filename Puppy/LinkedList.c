#include "LinkedList.h"

List* Setup(List *p)
{
	FILE* fp;
	fopen_s(&fp, "DATA.txt", "r");

	if (fp == NULL)
	{
		return NULL;
	}
	while (!feof(fp)) //파일에서 읽어오기
	{
		fgets(p->Name, 50, fp);
		p->Name[strlen(p->Name) - 1] = '\0';

		fgets(p->Feature, 50, fp);
		p->Feature[strlen(p->Feature) - 1] = '\0';

		fscanf_s(fp, "%d", &p->time);

		p->Next = (List*)malloc(sizeof(List));
		p = p->Next;
		p->Next = NULL; //하나 가져올 때마다 노드 하나씩 생성
	}
	fclose(fp);
	return p;
}

char MenuList()
{
	int number;
	system("cls");
	puts("링크드 리스트");
	puts("1. 추가");
	puts("2. 삽입");
	puts("3. 수정");
	puts("4. 삭제");
	puts("5. 출력");
	puts("0. 종료");

	printf("번호 선택 : ");
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
			puts("없는 메뉴");
		}
	}
}
List* AppendList(List* p)
{
	printf("품종명을 입력하세요 : ");
	gets_s(p->Name, sizeof(p->Name));

	printf("권장 산책 시간을 입력하세요(단위 : 분) : ");
	scanf_s("%d", &p->time);
	getc(stdin);

	printf("특징을 입력하세요 : ");
	gets_s(p->Feature, sizeof(p->Feature));

	p->Next = (List*)malloc(sizeof(List)); //맨 끝에 노드 생성
	p = p->Next;
	p->Next = NULL; //꼬리 노드의 링크 초기화
	return p;
}

int DisplayList(List* p)
{
	int i = 1;
	puts("\t품종\t\t권장 산책 시간\t\t특징");
	while (p->Next != NULL) //더이상 다음 노드가 없을 때까지
	{
		printf("%d %15s %12d분 %35s\n", i++, p->Name, p->time, p->Feature);
		p = p->Next;
	}
	system("pause");
	return i - 1; // 리스트 길이 반환
}

List* InsertList(List* p)
{
	int pos, number;
	List* item;
	List* start = p;
	item = (List*)malloc(sizeof(List)); //새로 추가할 노드
	number = DisplayList(p); //리스트 길이 얻어옴

	do {
		printf("삽입할 위치 : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number); 

	printf("품종명을 입력하세요 : ");
	gets_s(item->Name, sizeof(item->Name));

	printf("권장 산책 시간를 입력하세요 : ");
	scanf_s("%d", &item->time);
	getc(stdin);

	printf("특징을 입력하세요 : ");
	gets_s(item->Feature, sizeof(item->Feature));

	if (pos == 1)
	{
		item->Next = p; //head는 두 번째 노드가 됨
		start = item; //item은 start가 됨
	}
	else
	{
		for (int i = 1; i < pos - 1; i++)
		{
			p = p->Next; // 선택한 위치 이전까지 이동
		}
		printf("%s", p->Name);
		system("pause");
		item->Next = p->Next; //아이템이 가리키는 노드는 선택한 위치의 노드
		p->Next = item; //선택한 노드 이전 위치의 노드가 item를 가리킴
	}
	return start;
}

List getData(List* p) //선택한 위치의 노드 가져옴
{
	int pos, number;
	number = DisplayList(p);
	do {
		printf("번호 선택 : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);
	if (pos == 1)
	{
		return *p; //1일경우 첫 노드 반환
	}
	else
	{
		int i;
		for (i = 1; i < pos; i++)
		{
			p = p->Next; //선택한 위치까지 이동
		}
		return *p; //반환
	}
}

void UpdateList(List* p)
{
	int pos, number;
	number = DisplayList(p);
	do {
		printf("수정할 번호 : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);

	if (pos == 1) //1일경우 바로 작성
	{
		printf("변경된 품종명을 입력하세요 : ");
		gets_s(p->Name, sizeof(p->Name));

		printf("변경된 권장 산책 시간을 입력하세요 : ");
		scanf_s("%d", &p->time);
		getc(stdin);

		printf("변경된 특징을 입력하세요 : ");
		gets_s(p->Feature, sizeof(p->Feature));
	}
	else //아닐경우 해당 위치까지 이동 후 작성
	{
		int i;
		for (i = 1; i < pos; i++)
		{
			p = p->Next;
		}
		printf("변경된 품종명을 입력하세요 : ");
		gets_s(p->Name, sizeof(p->Name));

		printf("변경된 권장 산책 시간을 입력하세요 : ");
		scanf_s("%d", &p->time);
		getc(stdin);

		printf("변경된 특징을 입력하세요 : ");
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
		printf("삭제할 번호 : ");
		scanf_s("%d", &pos);
		getc(stdin);
	} while (pos<1 || pos>number);

	if (pos == 1) //1일경우 start는 그 다음 노드가 됨 (head가 바뀜)
	{
		start = p->Next;
		free(p);
	}
	else
	{
		List* temp;
		for (int i = 1; i < pos - 1; i++)
		{
			p = p->Next; //해당 위치 이전까지 이동
		}
		temp = p->Next; //temp에 해당 위치 저장
		p->Next = p->Next->Next;//선택한 위치 건너뛰고 연결
		free(temp);
	}
	return start;
}

void FreeMallocList(List* p) //모두 메모리 할당 해제
{
	List* tmp = p;
	while (p != NULL)
	{
		tmp = p->Next;
		free(p);
		p = tmp;
	}
	puts("파일에 저장중");
}

void SaveFile(List* p)
{
	FILE* fp;
	fopen_s(&fp, "DATA.txt", "w");

	if (fp == NULL)
	{
		printf("오류\n");
		return;
	}

	while (p->Next != NULL)
	{
		fprintf(fp, "%s\n%s\n%d", p->Name, p->Feature, p->time); //파일에 저장
		p = p->Next;
	}
	fclose(fp);
}