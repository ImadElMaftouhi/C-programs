//Tri par bulle itérative
/*
#include <stdio.h>
void echange(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void affiche(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
void bulle(int arr[], int n)
{
int i, j;
for (i = 0; i < n-1; i++){
 printf("Passe :%d\n",i+1);
	for (j = 0; j < n-1-i; j++){
		if (arr[j] > arr[j+1])
			echange(&arr[j], &arr[j+1]);
                    affiche(arr, n);
	                        }



                 }
}

int main()
{
	int arr[] = {5, 1, 4, 2, 8 };
	int n = sizeof(arr)/sizeof(arr[0]);
	affiche(arr, n);
	printf("-----------------\n");
	bulle(arr, n);
	printf("Tri: \n");
	affiche(arr, n);
	return 0;
}

*/
//Tri par bulle récursive
#include <stdio.h>

void echange(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}


void bulle2(int *arr, int n)
{
int i;
	if (n == 1)
		return;


	for (i=0; i<n-1; i++)
		if (*(arr+i) > *(arr+i+1))
			echange(arr+i, arr+i+1);


	bulle2(arr, n-1);
}

void affiche(int *arr, int n)
{
    int i;
	for (i=0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	int n = sizeof(arr)/sizeof(arr[0]);
	affiche(arr, n);
	printf("tri bulle: \n");
	bulle2(arr, n);

	affiche(arr, n);
	return 0;
}

