#include<stdio.h>
#include<stdlib.h>
void insertionSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];  // Shift element to the right
            j--;
        }
        arr[j + 1] = temp;  // Insert temp at correct position
    }
}


int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    printf("Enter Elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    inserionSort(arr,n);
    printf("Sorted array: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}