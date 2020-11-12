#pragma once
typedef struct myDog
{
	double weight;
	double goodweight;
	char name[50];
	char kind[50];
	char feature[50];
	int goodtime;
	int walk[8];
	double stress;
	int fat;
	
}myDog;
double getfat(myDog *dog);
void dogstate_screen(int *refresh);
void strcopy(char str1[], char str2[]);
int loadinfo(myDog* p);
int saveinfo(myDog* p);