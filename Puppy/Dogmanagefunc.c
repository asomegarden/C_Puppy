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
			printf("���� ������ ã�� �� �����ϴ�. �ʱ� ������ �����մϴ�.\n");
			printf("�̸� : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("���� : ");
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
		printf("%2d�� %2d��", tm.tm_mon + 1, tm.tm_mday);
		printf("  %s", dog.name);
		printf("(%s)", dog.kind);
		setCur(0, 1);
		printf("Ư¡ : %s", dog.feature);
		setCur(0, 35);

		if (dog.fat == 0)
		{
			printf("�ְ��� BCS�� �Է����ּ���.");
		}
		else
		{
			printf("ü����� : ��%d%%", dog.fat);
			if (dog.fat == 5) printf("�ʹ� �������");
			else if (dog.fat == 10) printf(" �������");
			else if (dog.fat == 20) printf(" �����ؿ�");
			else if (dog.fat == 30) printf(" �����ؿ�");
			else if (dog.fat == 40) printf(" ���̿���");
		}
		printf("\t����ü�� : %.2lfkg || ����ü�� : %.2lfkg", dog.weight, dog.goodweight);
		setCur(0, 37);
		printf("�Ϸ翡 %d�о� ��å�� �����ؿ�", dog.goodtime);
		setCur(0, 38);
		printf("��Ʈ���� ���� : %lf  ", dog.stress);
		if (dog.stress > 14)
		{
			printf("��å �屸�� ���� �׿����!");
		}
		else if (dog.stress <= 14)
		{
			printf("���� �������� �� ���� �����ּ���");
		}
		else
		{
			printf("%s�� �����ϰ� �־��", dog.name);
		}

		setCur(65, 5);
		printf("1. ü�� �Է�");
		setCur(65, 6);
		printf("2. BCS �Է�");
		setCur(65, 7);
		printf("3. ������ ��å �ð� ���");
		setCur(65, 8);
		printf("4. �ְ� ���� ����");
		setCur(65, 9);
		printf("5. �ְ� �����ͺ��̽� ����\n");
		setCur(65, 10);
		printf("6. �ʱ�ȭ\n");
		setCur(65, 11);
		printf("0. ����");

		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			printf("�ְ��� ���Ը� �Է��ϼ��� : ");
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
			printf("���� ��å�� �ð��� ����ϼ���(���� : ��) : ");
			scanf_s("%d", &dog.walk[6]);
			loop = 0;
			saveinfo(&dog);
			break;
		case 4:
			printf("�ְ� ������ �����ϼ���");
			printf("\n�̸� : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("���� : ");
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

	printf("�� ���񽺴� �ְ��� ����ü���� ��ü�������(BCS)�� ������� �����մϴ�.\n");
	printf("��ü��������� ���� ���̰� �������� ���� �� 5���� �������� ��Ÿ���� �̴� ������ �����ϴ�.\n\n");
	printf("1. ����, ô��, ���,�� �� ��� ���� ����ΰ� �ָ��� ���Ƶ� �ε巯�� ���δ�. (ü����� ��5%)\n");
	printf("2. ������ �ս��� ��������. ������ ���� ���κ�, ��� ���� Ƣ��� ���δ�.\n   �㸮�� �ſ� �߷��ϸ� ����� �ε巯�� ���̴� ���� �� �� �ִ�. (ü����� ��10%)\n");
	printf("3. ������ ������ Ȯ���� �� �ִ� ���� ���������� �����ϰ� �پ� �ִ�.\n   ������ ���� �㸮�� �� ���� ���� �� �� �ִ�. (ü����� ��20%)\n");
	printf("4. ���������� �β��� ������ ������ ��ƴ�. �㸮�� �������� ���� ������ ���� ������ �׿��ִ�.\n   �㸮�� �߷����� ������ �ʴ´�. (ü����� ��30%)\n");
	printf("5. ����, ��, ���� ���� ������ ������ �ſ� ����. ���̳� �� �ٸ����� ������ �ְ�, \n   ���ΰ� �ѷ��ϰ� �ҷ��ϴ�. (ü����� ��40%)\n\n");
	printf("�ش��ϴ� �׸��� ��ȣ�� �Է����ּ���.(0�� ������ ����)\n : ");

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
			printf("���� ���� ���ڸ� �Է����ּ��� : ");
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
		printf("����\n");
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

