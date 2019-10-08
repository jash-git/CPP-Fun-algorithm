//program 3-2
#include <iostream>
#include <cstdlib>
using namespace std;
void Merge(int A[], int low, int mid, int high)
{
    int *B=new int[high-low+1];//申请一个辅助数组
    int i=low, j=mid+1, k=0;
    while(i<=mid && j<=high) {//按从小到大存放到辅助数组B[]中
        if(A[i]<=A[j])
            B[k++]=A[i++];
        else
            B[k++]=A[j++];
    }
    while(i<=mid) B[k++]=A[i++];//将数组中剩下的元素放置B中
    while(j<=high) B[k++]=A[j++];
    for(i=low, k=0; i<=high; i++)
        A[i]=B[k++];
}
void MergeSort(int A[], int low, int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;//取中点
        MergeSort(A, low, mid);//对A[low:mid]中的元素合并排序
        MergeSort(A, mid+1, high);//对A[mid+1:high]中的元素合并排序
        Merge(A, low, mid, high);//合并
    }
}
int main()
{
    int n, A[100];
    cout<<"请输入数列中的元素个数n为："<<endl;
    cin>>n;
    cout<<"请依次输入数列中的元素："<<endl;
    for(int i=0; i<n; i++)
       cin>>A[i];
    MergeSort(A,0,n-1);
    cout<<"合并排序结果："<<endl;
    for(int i=0;i<n;i++)
       cout<<A[i]<<" ";
    cout<<endl;
    return 0;
}
