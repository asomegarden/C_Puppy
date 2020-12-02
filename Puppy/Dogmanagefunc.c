#include <time.h>
#include "LinkedList.h"
#include "Interface.h"
#include "Dogmanagefunc.h"

void dogstate_screen(int *refresh) //���� ȭ�� ����
{
	List* head = (List*)malloc(sizeof(List));
	List* tail = head;
	head->Next = NULL; //���� ����Ʈ�� �ҷ����� ����

	if (Setup(tail) == NULL);
	else tail = Setup(tail); //���� ����Ʈ �ҷ���

	int loop = 1; //���� ȭ�鿡�� ���� ����
	List mydogdata; 
	tDate pastdate;

	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t); //���� �ð� ������

	while (loop)
	{
		myDog dog;
		if (!(loadinfo(&dog, &pastdate))) //������ �ҷ����� ���� ���ٸ� �ʱ� ����
		{
			system("cls");
			printf("���� ������ ã�� �� �����ϴ�. �ʱ� ������ �����մϴ�.\n");
			printf("�̸� : ");
			scanf_s("%s", dog.name, sizeof(dog.name));
			printf("���� : ");
			scanf_s("%lf", &dog.weight);
			mydogdata = getData(head); //���� ����Ʈ���� ���� ������
			strcopy(dog.kind, mydogdata.Name); //���ڿ� ������ ����
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
		checkpast(&dog, &pastdate, tm.tm_mon + 1, tm.tm_mday); //��å ���� ������
		getstress(&dog); //��Ʈ���� ���� ������Ʈ

		system("cls");
		setCur(0, 0);
		printf("%2d�� %2d��", tm.tm_mon + 1, tm.tm_mday);
		printf("  %s", dog.name);
		printf("(%s)", dog.kind);
		setCur(0, 1);
		printf("Ư¡ : %s", dog.feature);
		setCur(0, 33); //��� ȭ�� ����

		if (dog.fat == 0) //���⼭���� �ְ� ü�� ���� ����
		{
			printf("�ְ��� BCS�� �Է����ּ���.");
		}
		else
		{
			printf("ü����� : ��%d%%", dog.fat);
			if (dog.fat == 5)
			{
				textcolor(12);
				printf("�ʹ� �������");
			}
			else if (dog.fat == 10)
			{
				textcolor(14);
				 printf(" �������");
			}
			else if (dog.fat == 20)
			{
				textcolor(9);
				 printf(" �����ؿ�");
			}
			else if (dog.fat == 30)
			{
				textcolor(14);
				 printf(" �����ؿ�");
			}
			else if (dog.fat == 40)
			{
				textcolor(12);
				 printf(" ���̿���");
			}
			textcolor(15);
		}
		printf("\t����ü�� : %.2lfkg || ����ü�� : %.2lfkg", dog.weight, dog.goodweight);
		setCur(0, 35);
		printf("�Ϸ翡 %d�о� ��å�� �����ؿ�", dog.goodtime); //���⼭���� �ְ� ��å ���� ����
		setCur(0, 36);
		printf("�ֱ� 7�ϰ� ��å ��� : ");
		for (int i = 0; i < 7; i++)
		{
			printf("%d�� ", dog.walk[i]);
		}
		setCur(0, 37);
		if (dog.stress < 0)
		{
			printf("��å ��¥�� ����غ�����");
		}
		else if (dog.stress >= 0 && dog.stress < 20)
		{
			printf("��Ʈ���� ���� : %.2lf%%  ", dog.stress);
			textcolor(14);
			printf("%s�� �����ϰ� �־��", dog.name);
		}
		else if (dog.stress >= 20 && dog.stress < 40)
		{
			printf("��Ʈ���� ���� : %.2lf%%  ", dog.stress);
			textcolor(14);
			printf("���� �������� �� ���� �����ּ���");
		}
		else if (dog.stress >= 40 && dog.stress < 60)
		{
			printf("��Ʈ���� ���� : %.2lf%%  ", dog.stress);
			textcolor(13);
			printf("%s�� ���� ��Ʈ������ �ް� �־��", dog.name);
		}
		else if (dog.stress >= 60)
		{
			printf("��Ʈ���� ���� : %.2lf%%  ", dog.stress);
			textcolor(12);
			printf("���� ��å�� �����ּ���!");
		}
		textcolor(15);

		setCur(65, 5); //���� �޴�
		printf("1. ü�� �Է�");
		setCur(65, 6);
		printf("2. BCS �Է�");
		setCur(65, 7);
		printf("3. ������ ��å �ð� ���");
		setCur(65, 8);
		printf("4. �ְ� ���� ����");
		setCur(65, 9);
		printf("5. �ְ� �����ͺ��̽� ����");
		setCur(65, 10);
		printf("6. �ʱ�ȭ");
		setCur(65, 11);
		printf("7. ���ǻ���");
		setCur(65, 12);
		printf("0. ����");
		setCur(65, 13);
		printf("�Է� >> ");

		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			printf("�ְ��� ���Ը� �Է��ϼ��� : ");
			scanf_s("%lf", &dog.weight);
			dog.goodweight = (double)(dog.weight * (100-(double)dog.fat) / 100) / 0.8;
			loop = 0;  //�Լ��� ����ƴٰ� �ٽ� ����� (���ΰ�ħ)
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday); //������ �ٲ� ������ ���Ͽ� ����
			break;
		case 2:
			system("cls");
			dog.goodweight = getfat(&dog); //���� ü�� ������
			loop = 0;
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
			break;
		case 3:
			printf("���� ��å�� �ð��� ����ϼ���(���� : ��) : ");
			scanf_s("%d", &dog.walk[6]);
			getstress(&dog);
			loop = 0;
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
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
			saveinfo(&dog, tm.tm_mon + 1, tm.tm_mday);
			break;
		case 5:
			listmenu(head, tail); //���� ����Ʈ �޴� ����
			break;

		case 6:
			remove("./myinfo.txt"); //�ְ� ���� ���� ����
			break;
		case 7:
			help(); //���� ����
			loop = 0;
			break;
		case 0:
			system("cls");
			loop = 0;
			*refresh = 0; //���� �Լ����� ������ ����� (���α׷� ����)
			break;
		}
	}
}

double getfat(myDog* dog) //ü����� ����, ���� ü�� ��ȯ
{
	int sel;

	printf("�� ���񽺴� �ְ��� ����ü���� ��ü�������(BCS)�� ������� �����մϴ�.\n");
	printf("��ü��������� ���� ���̰� �������� ���� �� 5���� �������� ��Ÿ���� �̴� ������ �����ϴ�.\n\n");
	printf("1. ����, ô��, ���,�� �� ��� ���� ����ΰ� �ָ��� ���Ƶ� �ε巯�� ���δ�. ");
	textcolor(4);
	printf("(ü����� ��5%)\n\n");
	textcolor(15);
	printf("2. ������ �ս��� ��������. ������ ���� ���κ�, ��� ���� Ƣ��� ���δ�.\n   �㸮�� �ſ� �߷��ϸ� ����� �ε巯�� ���̴� ���� �� �� �ִ�. ");
	textcolor(6);
	printf("(ü����� ��10%)\n\n");
	textcolor(15);
	printf("3. ������ ������ Ȯ���� �� �ִ� ���� ���������� �����ϰ� �پ� �ִ�.\n   ������ ���� �㸮�� �� ���� ���� �� �� �ִ�. ");
	textcolor(2);
	printf("(ü����� ��20%)\n\n");
	textcolor(15);
	printf("4. ���������� �β��� ������ ������ ��ƴ�. �㸮�� �������� ���� ������ ���� ������ �׿��ִ�.\n   �㸮�� �߷����� ������ �ʴ´�. ");
	textcolor(6);
	printf("(ü����� ��30%)\n\n");
	textcolor(15);
	printf("5. ����, ��, ���� ���� ������ ������ �ſ� ����. ���̳� �� �ٸ����� ������ �ְ�, \n   ���ΰ� �ѷ��ϰ� �ҷ��ϴ�. ");
	textcolor(4);
	printf("(ü����� ��40%)\n\n");
	textcolor(15);
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

void getstress(myDog* dog) //��å ������ �������� ���� ��Ʈ���� ���� ����
{
	double max = (double)dog->goodtime * 7;
	double stress = max;
	int temp[7];

	for (int i = 0; i < 7; i++)
	{
		if (dog->walk[i] + 10 > dog->goodtime)
		{
			temp[i] = dog->goodtime + 10; //�ƹ��� ��å�� �����߾ �ִ� +10�б����� ����
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
		dog->stress = stress/max*100; //������� ��Ÿ��
	}
}

int loadinfo(myDog* p, tDate *q) //myinfo.txt���� ���� ������
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
int saveinfo(myDog* p, int mon, int day) //myinfo.txt�� ���� ��������
{
	FILE* fp;
	fopen_s(&fp, "myinfo.txt", "w");

	if (fp == NULL)
	{
		printf("����\n");
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
void strcopy(char str1[], char str2[]) //���ڿ��� �������ֱ� ���� ����
{
	int i = 0;

	for (i = 0; i < strlen(str2); i++)
	{
		if (str2[i] != '\0') str1[i] = str2[i];
	}
	str1[i] = '\0';
}
void help() //���� ���
{
	system("cls");
	setCur(40, 5);
	textcolor(9);
	printf("���ǻ���");
	textcolor(13);
	setCur(10, 10);
	printf("*�� ���α׷����� �����ϴ� ������ �������� '�����'�Դϴ�.*");
	textcolor(15);
	setCur(10, 11);
	printf("�������� ���� ü�߰� ü������� ���� ��ó�� ���� �����Ͽ����ϴ�.");
	textcolor(9);
	setCur(10, 12);
	printf("https://ddaen1225.tistory.com/15");
	textcolor(15);
	setCur(10, 13);
	printf("������ ������ �����ϴ�. : ����ü�� = ����ü�� x(100 - ü�����) / 100 �� 0.8");
	setCur(10, 15);
	printf("���� �ٲ�� ��å ����� �ʱ�ȭ�˴ϴ�.");
	setCur(10, 16);
	printf("���� ��å �ð��� ���� ��ó�� ���� �����Ͽ����ϴ�.");
	textcolor(9);
	setCur(10, 17);
	printf("https://devotedtodog.com/how-often-should-you-walk-your-dog/");
	textcolor(15);
	setCur(10, 18);
	printf("������ ������ �����ϴ�.");
	setCur(10, 19);
	printf("���� ��Ʈ���� = (���� ��å �ð� * 7) - (6���� ��å �ð� * 1.1 * 0.8)");
	setCur(10, 20);
	printf(" - (5���� ��å �ð� * 1.1 * 0.9) - ... - (���� ��å �ð� * 1.1 * 0.8)");
	setCur(10, 22);
	printf("�������� ���� ������ �ִٸ� �����ͺ��̽��� ���� �����Ͽ� ����� �� �ֽ��ϴ�.");
	setCur(10, 23);
	printf("�ְ��� Ư¡ ������ ���ߵ鿡�� ���� �˷��� �Ϲ����� ������ �Է��صξ����ϴ�.");
	setCur(10, 25);
	system("pause");
}
int checkpast(myDog* dog, tDate* past, int mon, int day) //��ĥ�� �������� Ȯ���ϰ� �׿� ���߾� �迭 ����Ʈ
{
	if (mon == past->month && day == past->day) return 0;
	else
	{
		if (mon != past->month) //���� �ٲ������ ��å ��� �ʱ�ȭ
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
	

