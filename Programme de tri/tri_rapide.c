
#include <stdio.h>


void echange(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


int partition(int arr[], int l, int h)
{ int j;
	int x = arr[h];
	int i = (l - 1);

	for (j = l; j <= h - 1; j++) {
		if (arr[j] <= x) {
			i++;
			echange(&arr[i], &arr[j]);
		}
	}
	echange(&arr[i + 1], &arr[h]);
	return (i + 1);
}
void tri_rapide(int arr[], int l, int h)   //version récursive
{
	if (l < h)
	{

		int pi = partition(arr, l, h);

		tri_rapide(arr, l, pi - 1);
		tri_rapide(arr, pi + 1, h);
	}
}

void tri_rapide2(int arr[], int l, int h)   //version itérative
{

	int stack[h - l + 1];


	int top = -1;


	stack[++top] = l;
	stack[++top] = h;


	while (top >= 0) {

		h = stack[top--];
		l = stack[top--];


		int p = partition(arr, l, h);


		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}


		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
}


void affiche(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d ", arr[i]);
		printf("\n");
}


int main()
{
	int arr[] = { 4, 3, 5, 2, 1, 3, 2, 3 };
	int n = sizeof(arr) / sizeof(*arr);
	affiche(arr, n);
	tri_rapide(arr, 0, n - 1);
	printf("Tri: \n");
	affiche(arr, n);
	return 0;
}

