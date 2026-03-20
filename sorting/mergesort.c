#include<stdio.h>
#include<stdlib.h>

void merge(int *arr,int left,int mid,int right)
{
    int left_len=mid-left+1,right_len=right-mid;
    int *left_arr= (int*)malloc(left_len*sizeof(int));
    int *right_arr= (int*)malloc(right_len*sizeof(int));
    int i,j,k;
    for (i=0;i<left_len;i++)
        left_arr[i] = arr[left+i];
    for (i=0;i<right_len;i++)
        right_arr[i] = arr[mid+1+i];
    i=j=k=0;
    for(i=0,j=0,k=left;k<=right;k++)
    {
        if((i<left_len)&&(j>=right_len || left_arr[i]<right_arr[j]))
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
    }
    
}

void merge_recursive(int arr[],int left, int right)
{
    if(left>=right) return;
    int mid =left+(right-left)/2;
    merge_recursive(arr,left,mid);
    merge_recursive(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void merge_sort(int *arr,int length)
{
    merge_recursive(arr,0,length-1);
}
int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int *arr=(int*)malloc(n*sizeof(int));
    printf("Enter Elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    merge_sort(arr,n);
    printf("Sorted array: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}