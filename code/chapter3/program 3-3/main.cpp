//program 3-3
#include <iostream>
using namespace std;
int Partition(int r[],int low,int high)//���ֺ���
{
    int i=low,j=high,pivot=r[low];//��׼Ԫ��
    while(i<j)
    {
        while(i<j&&r[j]>pivot) j--;//����ɨ��
        if(i<j)
        {
            swap(r[i++],r[j]);//r[i]��r[j]������i+1����һλ
        }
        while(i<j&&r[i]<=pivot) i++;//����ɨ��
        if(i<j)
        {
            swap(r[i],r[j--]);//r[i]��r[j]���� ��j-1����һλ
        }
    }

    return i;//�������ջ�����ɺ��׼Ԫ�����ڵ�λ��
}

int Partition2(int r[],int low,int high)//���ֺ���
{
    int i=low,j=high,pivot=r[low];//��׼Ԫ��
    while(i<j)
    {
        while(i<j&&r[j]>pivot) j--;//����ɨ��
        while(i<j&&r[i]<=pivot) i++;//����ɨ��
        if(i<j)
        {
            swap(r[i++],r[j--]);//r[i]��r[j]����
        }
    }
    if(r[i]>pivot)
    {
        swap(r[i-1],r[low]);//r[i-1]��r[low]����
        return i-1;//�������ջ�����ɺ��׼Ԫ�����ڵ�λ��
    }
    swap(r[i],r[low]);//r[i]��r[low]����
    return i;//�������ջ�����ɺ��׼Ԫ�����ڵ�λ��
}

void QuickSort(int R[],int low,int high)//ʵ�ֿ����㷨
{
    int mid;
    if(low<high)
    {
        mid=Partition2(R,low,high); //��׼λ��
        QuickSort(R,low,mid-1);//������ݹ����
        QuickSort(R,mid+1,high);//������ݹ����
    }
}
int main()
{
    int a[100];
    int i,N;
    cout<<"��������Ҫ��������ݵĸ�����";
    cin>>N;
    cout<<"������Ҫ��������ݣ�";
    for(i=0;i<N;i++)
        cin>>a[i];
    cout<<endl;
    QuickSort(a,0,N-1);
    cout<<"����������Ϊ��"<<endl;
    for(i=0;i<N;i++)
        cout<<a[i]<<" " ;
    cout<<endl;
    return 0;
}
