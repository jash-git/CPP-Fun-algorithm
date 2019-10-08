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
   int low=0,high=n-1;  //low指向有序数组的第一个元素，high指向有序数组的最后一个元素
   while(low<=high)
   {
       int middle=(low+high)/2;  //middle为查找范围的中间值
       if(x==s[middle])  //x等于查找范围的中间值，算法结束
          return middle;
       else if(x>s[middle])   //x大于查找范围的中间元素，则从左半部分查找
              low=middle+1;
            else   //x小于查找范围的中间元素，则从右半部分查找
              high=middle-1;
    }
    return -1;
}

int main()
{
    cout<<"该数列中的元素个数n为：";
    while(cin>>n)
    {
        cout<<"请依次输入数列中的元素：";
        for(i=0;i<n;i++)
           cin>>s[i];
        sort(s,s+n);
        cout<<"排序后的数组为：";
        for(i=0;i<n;i++)
        {
           cout<<s[i]<<" ";
        }
        cout<<endl;
        cout<<"请输入要查找的元素：";
        cin>>x;
        i=BinarySearch(n,s,x);
        if(i==-1)
          cout<<"该数列中没有要查找的元素"<<endl;
        else
          cout<<"要查找的元素在第"<<i+1<<"位"<<endl;
    }
    return 0;
}

