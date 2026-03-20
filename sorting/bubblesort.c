#include<stdio.h>
#include<stdlib.h>

void bubble(int arr[],int n)
{
    int i,j;
    for (i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if (arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
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
    bubble(arr,n);
    printf("Sorted array: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}