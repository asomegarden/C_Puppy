#pragma once
typedef struct myDog
{
	char name[50];
	char kind[50];
	char feature[50];
	double weight;
	double goodweight;
	double stress;
	int fat;
	int walk[7];
	int goodtime;

}myDog;
typedef struct tDate
{
	int month;
	int day;
}tDate;

double getfat(myDog *dog);
void getstress(myDog *dog);
void dogstate_screen(int *refresh);
void strcopy(char str1[], char str2[]);
void help();
int checkpast(myDog* dog, tDate* past, int mon, int day);
int loadinfo(myDog* p, tDate *q);
int saveinfo(myDog* p, int mon, int day);