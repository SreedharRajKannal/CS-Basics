#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partation(int *arr,int low, int high)
{
    int piviot = arr[high];
    int i = low;
    for(int j = low; j< high;j++)
    {
        if(arr[j]<=piviot)
        {
            swap(&arr[j],&arr[j]);
            i++;
        }
    }
    swap(&arr[i],&arr[high]);
    return i;
}

void quicksort_recursive(int *arr, int low, int high)
{
    if(low>=high) return;
    int pivot = arr[high];
    pivot = partation(arr,low,high);
    quicksort_recursive(arr,low,pivot-1);
    quicksort_recursive(arr,pivot+1,high);
}

void quicksort(int *arr, int len)
{
    quicksort_recursive(arr,0,len-1);
}



int main()
{
    printf("Enter the number of elements: ");
    int n;
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    printf("Enter Elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Entered array:");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    quicksort(arr,n);
    printf("Sorted array: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;

}