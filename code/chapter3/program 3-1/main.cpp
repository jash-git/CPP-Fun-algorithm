//program 3-1
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M=10000;
int x,n,i;
int s[M];

int BinarySearch(int n,int s[],int x)
{
   int low=0,high=n-1;  //lowָ����������ĵ�һ��Ԫ�أ�highָ��������������һ��Ԫ��
   while(low<=high)
   {
       int middle=(low+high)/2;  //middleΪ���ҷ�Χ���м�ֵ
       if(x==s[middle])  //x���ڲ��ҷ�Χ���м�ֵ���㷨����
          return middle;
       else if(x>s[middle])   //x���ڲ��ҷ�Χ���м�Ԫ�أ������벿�ֲ���
              low=middle+1;
            else   //xС�ڲ��ҷ�Χ���м�Ԫ�أ�����Ұ벿�ֲ���
              high=middle-1;
    }
    return -1;
}

int main()
{
    cout<<"�������е�Ԫ�ظ���nΪ��";
    while(cin>>n)
    {
        cout<<"���������������е�Ԫ�أ�";
        for(i=0;i<n;i++)
           cin>>s[i];
        sort(s,s+n);
        cout<<"����������Ϊ��";
        for(i=0;i<n;i++)
        {
           cout<<s[i]<<" ";
        }
        cout<<endl;
        cout<<"������Ҫ���ҵ�Ԫ�أ�";
        cin>>x;
        i=BinarySearch(n,s,x);
        if(i==-1)
          cout<<"��������û��Ҫ���ҵ�Ԫ��"<<endl;
        else
          cout<<"Ҫ���ҵ�Ԫ���ڵ�"<<i+1<<"λ"<<endl;
    }
    return 0;
}

