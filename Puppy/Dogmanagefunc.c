#include <time.h>
#include "LinkedList.h"
#include "Interface.h"
#include "Dogmanagefunc.h"

void dogstate_screen(int *refresh)
{
	List* head = (List*)malloc(sizeof(List));
	List* tail = head;
	head->Next = NULL;

	if (Setup(tail) == NULL);
	else tail = Setup(tail);

	int loop = 1;
	List mydogdata;
	while (loop)
	{
		myDog dog;
		if (!(loadinfo(&dog)))
		{
			system("cls");
			printf("기존 설정을 찾을 수 없습니다. 초기 설정을 시작합니다.\n");
			printf("이름 : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("무게 : ");
			scanf_s("%lf", &dog.weight);
			mydogdata = getData(head);
			strcopy(dog.kind, mydogdata.Name);
			dog.goodtime = mydogdata.time;
			strcopy(dog.feature, mydogdata.Feature);
			for (int i = 0; i < 7; i++)
			{
				dog.walk[i] = 0;
			}
			dog.stress = 0;
			dog.fat = 0;
			dog.goodweight = 0;
			saveinfo(&dog);
		}
		int sel;

		time_t t = time(NULL);
		struct tm tm;
		localtime_s(&tm, &t);

		system("cls");
		setCur(0, 0);
		printf("%2d월 %2d일", tm.tm_mon + 1, tm.tm_mday);
		printf("  %s", dog.name);
		printf("(%s)", dog.kind);
		setCur(0, 1);
		printf("특징 : %s", dog.feature);
		setCur(0, 35);

		if (dog.fat == 0)
		{
			printf("애견의 BCS를 입력해주세요.");
		}
		else
		{
			printf("체지방률 : 약%d%%", dog.fat);
			if (dog.fat == 5) printf("너무 말랐어요");
			else if (dog.fat == 10) printf(" 말랐어요");
			else if (dog.fat == 20) printf(" 적당해요");
			else if (dog.fat == 30) printf(" 통통해요");
			else if (dog.fat == 40) printf(" 비만이에요");
		}
		printf("\t현재체중 : %.2lfkg || 적정체중 : %.2lfkg", dog.weight, dog.goodweight);
		setCur(0, 37);
		printf("하루에 %d분씩 산책이 적당해요", dog.goodtime);
		setCur(0, 38);
		printf("스트레스 지수 : %lf  ", dog.stress);
		if (dog.stress > 14)
		{
			printf("산책 욕구가 많이 쌓였어요!");
		}
		else if (dog.stress <= 14)
		{
			printf("아직 괜찮지만 더 자주 나가주세요");
		}
		else
		{
			printf("%s가 만족하고 있어요", dog.name);
		}

		setCur(65, 5);
		printf("1. 체중 입력");
		setCur(65, 6);
		printf("2. BCS 입력");
		setCur(65, 7);
		printf("3. 오늘의 산책 시간 기록");
		setCur(65, 8);
		printf("4. 애견 정보 수정");
		setCur(65, 9);
		printf("5. 애견 데이터베이스 관리\n");
		setCur(65, 10);
		printf("6. 초기화\n");
		setCur(65, 11);
		printf("0. 종료");

		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			printf("애견의 무게를 입력하세요 : ");
			scanf_s("%lf", &dog.weight);
			dog.goodweight = (double)(dog.weight * (100-dog.fat) / 100) / 0.8;
			loop = 0;
			saveinfo(&dog);
			break;
		case 2:
			system("cls");
			dog.goodweight = getfat(&dog);
			loop = 0;
			saveinfo(&dog);
			break;
		case 3:
			printf("오늘 산책한 시간을 기록하세요(단위 : 분) : ");
			scanf_s("%d", &dog.walk[6]);
			loop = 0;
			saveinfo(&dog);
			break;
		case 4:
			printf("애견 정보를 수정하세요");
			printf("\n이름 : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("무게 : ");
			scanf_s("%lf", &dog.weight);
			mydogdata = getData(head);
			strcopy(dog.kind, mydogdata.Name);
			dog.goodtime = mydogdata.time;
			strcopy(dog.feature, mydogdata.Feature);

			loop = 0;
			saveinfo(&dog);
			break;
		case 5:
			listmenu(head, tail);
			break;

		case 6:
			remove("./myinfo.txt");
			break;
		case 0:
			system("cls");
			loop = 0;
			*refresh = 0;
			break;
		}
	}
}

double getfat(myDog* dog)
{
	int sel;

	printf("본 서비스는 애견의 적정체중을 신체충실지수(BCS)를 기반으로 측정합니다.\n");
	printf("신체충실지수는 눈에 보이고 만져지는 것을 총 5가지 기준으로 나타내며 이는 다음과 같습니다.\n\n");
	printf("1. 늑골, 척추, 골반,뼈 등 모든 뼈의 돌기부가 멀리서 보아도 두드러져 보인다. (체지방률 약5%)\n");
	printf("2. 늑골이 손쉽게 만져진다. 요추의 앞쪽 끝부분, 골반 뼈도 튀어나와 보인다.\n   허리는 매우 잘록하며 골반이 두드러져 보이는 것을 알 수 있다. (체지방률 약10%)\n");
	printf("3. 늑골을 만지면 확인할 수 있는 정도 피하지방이 적당하게 붙어 있다.\n   위에서 보면 허리가 들어간 것을 쉽게 알 수 있다. (체지방률 약20%)\n");
	printf("4. 피하지방이 두껍고 늑골을 만지기 어렵다. 허리와 엉덩이의 시작 부위에 많은 지방이 쌓여있다.\n   허리의 잘록함이 보이지 않는다. (체지방률 약30%)\n");
	printf("5. 가슴, 등, 꼬리 시작 부위에 지방이 매우 많다. 목이나 네 다리에도 지방이 있고, \n   복부가 뚜렷하게 불룩하다. (체지방률 약40%)\n\n");
	printf("해당하는 항목의 번호를 입력해주세요.(0을 누르면 종료)\n : ");

	while (1)
	{
		scanf_s("%d", &sel);
		switch (sel)
		{
		case 1:
			dog->goodweight = (double)(dog->weight * (95) / 100) / 0.8;
			dog->fat = 5;
			return dog->goodweight;
			break;

		case 2:
			dog->goodweight = (double)(dog->weight * (90) / 100) / 0.8;
			dog->fat = 10;
			return dog->goodweight;
			break;

		case 3:
			dog->goodweight = (double)(dog->weight * (80) / 100) / 0.8;
			dog->fat = 20;
			return dog->goodweight;
			break;

		case 4:
			dog->goodweight = (double)(dog->weight * (70) / 100) / 0.8;
			dog->fat = 30;
			return dog->goodweight;
			break;

		case 5:
			dog->goodweight = (double)(dog->weight * (60) / 100) / 0.8;
			dog->fat = 40;
			return dog->goodweight;
			break;

		case 0:
			return 0;
		default:
			printf("범위 내의 숫자를 입력해주세요 : ");
			break;
		}
	}
}
int loadinfo(myDog* p)
{
	FILE* fp;
	fopen_s(&fp, "myinfo.txt", "r");

	if (fp == NULL)
	{
		return 0;
	}

	while (!feof(fp))
	{
		fgets(p->name, 50, fp);
		p->name[strlen(p->name) - 1] = '\0';

		fgets(p->walk, 8, fp);
		p->walk[strlen(p->walk) - 1] = '\0';

		fgets(p->kind, 50, fp);
		p->kind[strlen(p->kind) - 1] = '\0';

		fgets(p->feature, 7, fp);
		p->walk[strlen(p->feature) - 1] = '\0';

		fscanf_s(fp, "%lf", &p->weight);
		fscanf_s(fp, "%lf", &p->goodweight);
		fscanf_s(fp, "%lf", &p->stress);
		fscanf_s(fp, "%d", &p->fat);
		fscanf_s(fp, "%d", &p->goodtime);
	}
	fclose(fp);
	return 1;
}
int saveinfo(myDog* p)
{
	FILE* fp;
	fopen_s(&fp, "myinfo.txt", "w");

	if (fp == NULL)
	{
		printf("오류\n");
		return 0;
	}

	fprintf(fp, "%s\n%s\n%s\n%s\n%lf\n%lf\n%lf\n%d\n%d", p->name, p->walk, p->kind, p->feature, p->weight, p->goodweight, p->stress, p->fat, p->goodtime);
	fclose(fp);
	return 1;
}
void strcopy(char str1[], char str2[])
{
	int len = 0, i;
	if (strlen(str1) > strlen(str2)) len = strlen(str2);
	else if (strlen(str2) > strlen(str1)) len = strlen(str1);
	else  len = strlen(str2);

	for (i = 0; i < len; i++)
	{
		if (str2[i] != '\0') str1[i] = str2[i];
	}
	str1[i] = '\0';
}

