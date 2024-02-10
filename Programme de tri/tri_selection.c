/*
#include <stdio.h>
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
		for (i = 0; i < n-1; i++)
	{
				min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;
		swap(&arr[min_idx], &arr[i]);
	}
}
void affiche(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main()
{
	int arr[] = {64, 25, 12, 22, 11};
	int n = sizeof(arr)/sizeof(arr[0]);
	affiche(arr, n);
	selectionSort(arr, n);
	printf("Tri selection: \n");
	affiche(arr, n);
	return 0;
}
*/
#include <stdio.h>
#include<stdio.h>
void swap2(int *x, int *y)
{
	int tmp;
	tmp=*x;
	*x=*y;
	*y=tmp;
return;
}
void triselect(int *array,int n)
{
	int i,j,lowindex=0;
	for(i=0;i<n-1;i++)
	{
		 lowindex=i;
		for(j=i+1;j<n;j++)
		{ if (*(array+j)>*(array+lowindex))
			lowindex=j;
		    swap2(&(array[j]),&(array[lowindex]));
		}
	}
}
void affiche(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
void main(void)
{
int *tab,i,n;
n=7;
int t[7]={1,12,3,4,10,7,6};
tab=t;
affiche(tab, n);
triselect(tab,n);
printf("Tri selection: \n");
affiche(tab, n);

}
