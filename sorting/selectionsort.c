#include<stdio.h>
#include<string.h>
int selectionSort(int arr[],int n)
{
    int i,j,min=0,temp=0;
    for(i = 0;i < n-1;i++)
    {
        min = arr[i];
        for(j = i+1;j < n; j++)
        {
            if(arr[j]<min)
            {
                min=arr[j];
                temp=arr[i];
                arr[i]=min;
                arr[j]=temp;
            }
        }
    }
}
int main()
{
    int n,i;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    printf("Enter Elements:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    selectionSort(arr,n);
    printf("Sorted array is:\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}