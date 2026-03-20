#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int get_Max(int arr[], int n){
    int max=arr[0];
    for(int i=0;i<n;i++){
        if(arr[i]>max)
            max=arr[i];
    }
    return max;
}
void Counting_Sort(int arr[],int n,int place){
    int *output = (int*)malloc(n*sizeof(int));
    if (output == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    int count[10] = {0};

    for(int i=0;i<n;i++){
        count[(arr[i]/place)%10]++;
    }
    for(int i =1;i<10;i++){
        count[i]+=count[i-1];
    }
    for(int i=n-1;i>=0;i--){
        int digit=(arr[i]/place)%10;
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }
    for(int i=0;i<n;i++){
        arr[i]=output[i];
    }
    free(output);
}
void radix_sort(int arr[],int n){
    int max = get_Max(arr,n);
    for(int place=1;place<=max;place*=10){
        Counting_Sort(arr,n,place);
    }
}
int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    printf("Enter Elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    radix_sort(arr,n);
    printf("Sorted array: \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}