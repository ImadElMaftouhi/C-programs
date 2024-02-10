
//version récursive
#include<stdlib.h>
#include<stdio.h>


void fusionner(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;


	int L[n1], R[n2];


	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];


	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}


	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}


	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}


void fusion_tri(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l+(r-l)/2;
		fusion_tri(arr, l, m);
		fusion_tri(arr, m+1, r);
		fusionner(arr, l, m, r);
	}
}


void affiche(int A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}


int main()
{
	int arr[] = {12, 11, 13, 5, 6, 7};
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	printf("tableau \n");
	affiche(arr, arr_size);

	fusion_tri(arr, 0, arr_size - 1);

	printf("\n tri \n");
	affiche(arr, arr_size);
	return 0;
}
/*

#include<stdlib.h>
#include<stdio.h>

//version itérative
void fusionner(int arr[], int l, int m, int r);

// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }



void fusion_tri(int arr[], int n)
{
int c;

int l;


for (c=1; c<=n-1; c = 2*c)
{

	for (l=0; l<n-1; l += 2*c)
	{

		int mid = min(l + c - 1, n-1);

		int r = min(l + 2*c - 1, n-1);


		fusionner(arr, l, mid, r);
	}
}
}


void fusionner(int arr[], int l, int m, int r)
{int i, j, k,n1 = m - l + 1, n2 = r - m,L[n1], R[n2];
		for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];
	i = j=0;k = l;
		while (i < n1 && j < n2)
	{
		if (L[i] <= R[j]){arr[k] = L[i];i++;}
		else{arr[k] = R[j];j++;}
				k++;
	}
	while (i < n1)
	{arr[k] = L[i];i++;k++;}
	while (j < n2)
	{arr[k] = R[j];j++;k++;}
}

void affiche(int A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}


int main()
{
	int arr[] = {12, 11, 13, 5, 6, 7};
	int n = sizeof(arr)/sizeof(arr[0]);

	printf("tableau is \n");
	affiche(arr, n);

	fusion_tri(arr, n);
	printf("\nTri \n");
	affiche(arr, n);
	return 0;
}
*/
