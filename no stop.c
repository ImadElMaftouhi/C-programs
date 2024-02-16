#include<stdio.h>

int main ()
{
	int j, i;

	scanf("%d");
	for(i=1;i>0;i++)
	{	for(j=1;j<=i;j++)
	{	printf("O");	}
	printf("\t\v\f\b\t");}
		return 0;
}       