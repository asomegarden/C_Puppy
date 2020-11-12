#pragma once
typedef struct mrDog
{
	double weight;
	double goodweight;
	char name[50];
	char kind[50];
	char feature[50];
	int goodtime;
	char walk[7];
	double stress;
	int fat;
	
}myDog;
double getfat(double weight, double *fat);
void dogstate_screen(int *refresh);
int loadinfo(myDog* p);
int saveinfo(myDog* p);