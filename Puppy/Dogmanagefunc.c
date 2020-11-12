#include <time.h>
#include "LinkedList.h"
#include "Interface.h"
#include "Dogmanagefunc.h"
double getfat(double weight, double *fat)
{
	int sel;
	float goodweight;

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
			goodweight = weight * (95) * 0.8 / 100;
			*fat = 5;
			return goodweight;
			break;

		case 2:
			goodweight = (weight * (90) * 0.8) / 100;
			*fat = 10;
			return goodweight;
			break;

		case 3:
			goodweight= (weight * (80) * 0.8) / 100;
			*fat = 20;
			return goodweight;
			break;

		case 4:
			goodweight = (weight * (70) * 0.8) / 100;
			*fat = 30;
			return goodweight;
			break;

		case 5:
			goodweight= (weight * (60) * 0.8) / 100;
			*fat = 40;
			return goodweight;
			break;

		case 0:
			return 0;

		default:
			printf("���� ���� ���ڸ� �Է����ּ��� : ");
			break;
		}
	}
}

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
			printf("���� ������ ã�� �� �����ϴ�. �ʱ� ������ �����մϴ�.");
			printf("�̸� : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("���� : ");
			scanf_s("%lf", &dog.weight);
			mydogdata = getData(head);
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
		printf("(%s)", mydogdata.Name);
		setCur(0, 24);

		if (dog.fat == 0)
		{
			printf("�ְ��� BCS�� �Է����ּ���.");
		}
		else
		{
			printf("ü����� : ��%d%", dog.fat);
			if (dog.fat == 5) printf("�ʹ� �������");
			else if (dog.fat == 10) printf("�������");
			else if (dog.fat == 20) printf("�����ؿ�");
			else if (dog.fat == 30) printf("�����ؿ�");
			else if (dog.fat == 40) printf("���̿���");
		}
		printf("\t��Ʈ���� ���� : %lf", dog.stress);
		if (dog.stress > 14)
		{
			printf("����");
		}
		else if (dog.stress <= 14)
		{
			printf("����");
		}
		else
		{
			printf("����");
		}

		setCur(55, 5);
		printf("1. ü�� �Է�");
		setCur(55, 6);
		printf("2. BCS �Է�");
		setCur(55, 7);
		printf("3. ������ ��å �ð� ���");
		setCur(55, 8);
		printf("4. �ְ� ���� ����");
		setCur(55, 9);
		printf("5. �ְ� �����ͺ��̽� ����\n");
		setCur(55, 10);
		printf("6. �ʱ�ȭ\n");

		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			printf("�ְ��� ���Ը� �Է��ϼ��� : ");
			scanf_s("%lf", &dog.weight);
			loop = 0;
			break;
		case 2:
			system("cls");
			dog.goodweight = getfat(dog.weight, &dog.fat);
			loop = 0;
			break;
		case 3:
			printf("���� ��å�� �ð��� ����ϼ���(���� : ��) : ");
			scanf_s("%d", dog.walk[6]);
			loop = 0;
			break;
		case 4:
			printf("�ְ� ������ �����ϼ���");
			printf("�̸� : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("���� : ");
			scanf_s("%d", &dog.weight);
			saveinfo(&dog);
			loop = 0;
			break;
		case 5:
			listmenu(head, tail);
			break;

		case 6:
			remove("./myinfo.txt");
			break;
		case 0:
			loop = 0;
			*refresh = 0;
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

		fgets(p->walk, 7, fp);
		p->walk[strlen(p->walk) - 1] = '\0';

		fscanf_s(fp, "%lf", &p->weight);
		fscanf_s(fp, "%lf", &p->stress);
		fscanf_s(fp, "%lf", &p->fat);
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

	fprintf(fp, "%s\n%s\n%lf\n%lf", p->name, p->walk, p->weight, p->stress, p->fat);
	fclose(fp);
	return 1;
}

