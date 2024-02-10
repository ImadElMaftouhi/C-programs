#include <math.h>
#include <stdio.h>
void insertiontri(int arr[], int n)
{
	int i, k, j;
	for (i = 1; i < n; i++) {
		k = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > k) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = k;
	}
}
void insertionRecursive(int *arr, int n)
{

    if (n == 1)
        return;
// trier les n-1 elements
    insertionRecursive( arr, n-1 );
//inserer le dernier element dans sa position correcte du tableau tri�
    int k = *(arr+n-1);
    int j = n-2;

// echanger les �lements qui sont sup�rieur � k
    while (j >= 0 && *(arr+j) > k)
    {
       *(arr+j+1) = *(arr+j);
        j--;
    }
    *(arr+j+1) = k;
}


void affiche(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main()
{
	int arr[] = { 12, 11, 13, 5, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);
	affiche(arr, n);
	//insertionRecursive(arr, n);
	insertiontri(arr, n);
	printf("Tri Insertion: \n");
	affiche(arr, n);
	return 0;
}
