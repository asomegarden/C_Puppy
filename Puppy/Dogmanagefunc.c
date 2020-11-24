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
	tDate pastdate;

	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	while (loop)
	{
		myDog dog;
		if (!(loadinfo(&dog, &pastdate)))
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
			dog.stress = -1;
			dog.fat = 0;
			dog.goodweight = 0;
			saveinfo(&dog, tm.tm_mon+1, tm.tm_mday);
			pastdate.month = tm.tm_mon + 1;
			pastdate.month = tm.tm_mday;
		}
		int sel;
		checkpast(&dog, &pastdate, tm.tm_mon + 1, tm.tm_mday);
		getstress(&dog);

		system("cls");
		setCur(0, 0);
		printf("%2d월 %2d일", tm.tm_mon + 1, tm.tm_mday);
		printf("  %s", dog.name);
		printf("(%s)", dog.kind);
		setCur(0, 1);
		printf("특징 : %s", dog.feature);
		setCur(0, 33);

		if (dog.fat == 0)
		{
			printf("애견의 BCS를 입력해주세요.");
		}
		else
		{
			printf("체지방률 : 약%d%%", dog.fat);
			if (dog.fat == 5)
			{
				textcolor(12);
				printf("너무 말랐어요");
			}
			else if (dog.fat == 10)
			{
				textcolor(14);
				 printf(" 말랐어요");
			}
			else if (dog.fat == 20)
			{
				textcolor(9);
				 printf(" 적당해요");
			}
			else if (dog.fat == 30)
			{
				textcolor(14);
				 printf(" 통통해요");
			}
			else if (dog.fat == 40)
			{
				textcolor(12);
				 printf(" 비만이에요");
			}
			textcolor(15);
		}
		printf("\t현재체중 : %.2lfkg || 적정체중 : %.2lfkg", dog.weight, dog.goodweight);
		setCur(0, 35);
		printf("하루에 %d분씩 산책이 적당해요", dog.goodtime);
		setCur(0, 36);
		printf("최근 7일간 산책 기록 : ");
		for (int i = 0; i < 7; i++)
		{
			printf("%d분 ", dog.walk[i]);
		}
		setCur(0, 37);
		if (dog.stress < 0)
		{
			printf("산책 날짜를 기록해보세요");
		}
		else if (dog.stress >= 0 && dog.stress < 20)
		{
			printf("스트레스 지수 : %.2lf%%  ", dog.stress);
			textcolor(14);
			printf("%s가 만족하고 있어요", dog.name);
		}
		else if (dog.stress >= 20 && dog.stress < 40)
		{
			printf("스트레스 지수 : %.2lf%%  ", dog.stress);
			textcolor(14);
			printf("아직 괜찮지만 더 자주 나가주세요");
		}
		else if (dog.stress >= 40 && dog.stress < 60)
		{
			printf("스트레스 지수 : %.2lf%%  ", dog.stress);
			textcolor(13);
			printf("%s가 점점 스트레스를 받고 있어요", dog.name);
		}
		else if (dog.stress >= 60)
		{
			printf("스트레스 지수 : %.2lf%%  ", dog.stress);
			textcolor(12);
			printf("당장 산책을 나가주세요!");
		}
		textcolor(15);

		setCur(65, 5);
		printf("1. 체중 입력");
		setCur(65, 6);
		printf("2. BCS 입력");
		setCur(65, 7);
		printf("3. 오늘의 산책 시간 기록");
		setCur(65, 8);
		printf("4. 애견 정보 수정");
		setCur(65, 9);
		printf("5. 애견 데이터베이스 관리");
		setCur(65, 10);
		printf("6. 초기화");
		setCur(65, 11);
		printf("7. 주의사항");
		setCur(65, 12);
		printf("0. 종료");
		setCur(65, 13);
		printf("입력 >> ");

		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			printf("애견의 무게를 입력하세요 : ");
			scanf_s("%lf", &dog.weight);
			dog.goodweight = (double)(dog.weight * (100-dog.fat) / 100) / 0.8;
			loop = 0;
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
			break;
		case 2:
			system("cls");
			dog.goodweight = getfat(&dog);
			loop = 0;
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
			break;
		case 3:
			printf("오늘 산책한 시간을 기록하세요(단위 : 분) : ");
			scanf_s("%d", &dog.walk[6]);
			getstress(&dog);
			loop = 0;
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
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
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
			break;
		case 5:
			listmenu(head, tail);
			break;

		case 6:
			remove("./myinfo.txt");
			break;
		case 7:
			help();
			loop = 0;
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
	printf("1. 늑골, 척추, 골반,뼈 등 모든 뼈의 돌기부가 멀리서 보아도 두드러져 보인다. ");
	textcolor(4);
	printf("(체지방률 약5%)\n\n");
	textcolor(15);
	printf("2. 늑골이 손쉽게 만져진다. 요추의 앞쪽 끝부분, 골반 뼈도 튀어나와 보인다.\n   허리는 매우 잘록하며 골반이 두드러져 보이는 것을 알 수 있다. ");
	textcolor(6);
	printf("(체지방률 약10%)\n\n");
	textcolor(15);
	printf("3. 늑골을 만지면 확인할 수 있는 정도 피하지방이 적당하게 붙어 있다.\n   위에서 보면 허리가 들어간 것을 쉽게 알 수 있다. ");
	textcolor(2);
	printf("(체지방률 약20%)\n\n");
	textcolor(15);
	printf("4. 피하지방이 두껍고 늑골을 만지기 어렵다. 허리와 엉덩이의 시작 부위에 많은 지방이 쌓여있다.\n   허리의 잘록함이 보이지 않는다. ");
	textcolor(6);
	printf("(체지방률 약30%)\n\n");
	textcolor(15);
	printf("5. 가슴, 등, 꼬리 시작 부위에 지방이 매우 많다. 목이나 네 다리에도 지방이 있고, \n   복부가 뚜렷하게 불룩하다. ");
	textcolor(4);
	printf("(체지방률 약40%)\n\n");
	textcolor(15);
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

void getstress(myDog* dog)
{
	double max = (double)dog->goodtime * 7;
	double stress = max;
	int temp[7];

	for (int i = 0; i < 7; i++)
	{
		if (dog->walk[i] + 10 > dog->goodtime)
		{
			temp[i] = dog->goodtime + 10;
		}
		else
		{
			temp[i] = dog->walk[i];
		}
	}

	stress -= (temp[0] * 1.1) * 0.8;
	stress -= (temp[1] * 1.1) * 0.9;
	stress -= (temp[2] * 1.1) * 1.0;
	stress -= (temp[3] * 1.1) * 1.1;
	stress -= (temp[4] * 1.1) * 1.2;
	stress -= (temp[5] * 1.1) * 1.3;
	stress -= (temp[6] * 1.1) * 1.4;

	if (stress < 0)
	{
		dog->stress = 0;
	}
	else
	{
		dog->stress = stress/max*100;
	}
}

int loadinfo(myDog* p, tDate *q)
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

		fgets(p->kind, 50, fp);
		p->kind[strlen(p->kind) - 1] = '\0';

		fgets(p->feature, 50, fp);
		p->feature[strlen(p->feature) - 1] = '\0';

		fscanf_s(fp, "%lf", &p->weight);
		fscanf_s(fp, "%lf", &p->goodweight);
		fscanf_s(fp, "%lf", &p->stress);
		fscanf_s(fp, "%d", &p->fat);
		fscanf_s(fp, "%d", &p->goodtime);
		for (int i = 0; i < 7; i++)
		{
			fscanf_s(fp, "%d", &p->walk[i]);
		}
		fscanf_s(fp, "%d", &q->month);
		fscanf_s(fp, "%d", &q->day);
	}
	fclose(fp);
	return 1;
}
int saveinfo(myDog* p, int mon, int day)
{
	FILE* fp;
	fopen_s(&fp, "myinfo.txt", "w");

	if (fp == NULL)
	{
		printf("오류\n");
		return 0;
	}

	fprintf(fp, "%s\n%s\n%s\n%lf\n%lf\n%lf\n%d\n%d", p->name, p->kind, p->feature, p->weight, p->goodweight, p->stress, p->fat, p->goodtime);
	for (int i = 0; i < 7; i++)
	{
		fprintf(fp, "\n%d", p->walk[i]);
	}
	fprintf(fp, "\n%d\n%d", mon, day);
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
void help()
{
	system("cls");
	setCur(40, 5);
	textcolor(9);
	printf("주의사항");
	textcolor(13);
	setCur(10, 10);
	printf("*본 프로그램에서 제공하는 정보는 어디까지나 '참고용'입니다.*");
	textcolor(15);
	setCur(10, 11);
	printf("강아지의 적정 체중과 체지방률은 다음 출처를 통해 산출하였습니다.");
	textcolor(9);
	setCur(10, 12);
	printf("https://ddaen1225.tistory.com/15");
	textcolor(15);
	setCur(10, 13);
	printf("공식은 다음과 같습니다. : 적정체중 = 현재체중 x(100 - 체지방률) / 100 ÷ 0.8");
	setCur(10, 15);
	printf("달이 바뀌면 산책 기록이 초기화됩니다.");
	setCur(10, 16);
	printf("적정 산책 시간은 다음 출처를 통해 산출하였습니다.");
	textcolor(9);
	setCur(10, 17);
	printf("https://devotedtodog.com/how-often-should-you-walk-your-dog/");
	textcolor(15);
	setCur(10, 18);
	printf("공식은 다음과 같습니다.");
	setCur(10, 19);
	printf("현재 스트레스 = (권장 산책 시간 * 7) - (6일전 산책 시간 * 1.1 * 0.8)");
	setCur(10, 20);
	printf(" - (5일전 산책 시간 * 1.1 * 0.9) - ... - (오늘 산책 시간 * 1.1 * 0.8)");
	setCur(10, 22);
	printf("적합하지 않은 정보가 있다면 데이터베이스를 직접 수정하여 사용할 수 있습니다.");
	setCur(10, 23);
	printf("애견의 특징 정보는 대중들에게 많이 알려진 일반적인 정보를 입력해두었습니다.");
	setCur(10, 25);
	system("pause");
}
int checkpast(myDog* dog, tDate* past, int mon, int day)
{
	if (mon == past->month && day == past->day) return 0;
	else
	{
		if (mon != past->month)
		{
			for (int i = 0; i < 7; i++)
			{
				dog->walk[i] = 0;
			}
			dog->stress = -1;
		}
		else
		{
			int temp = day - past->day;
			for (int i = 0; i < temp; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					dog->walk[j] = dog->walk[j + 1];
				}
				dog->walk[6] = 0;
			}
			
		}
	}
}
	

