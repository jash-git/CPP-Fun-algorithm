//mysort2
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

bool compare(int a,int b)
{
      return a<b;   //�������У������Ϊreturn a>b����Ϊ����
}
int main()
{
    int a[10]={7,4,5,23,2,73,41,52,28,60},i;
    for(i=0;i<10;i++)
      cout<<a[i]<<" ";
    cout<<endl;
    sort(a,a+10,compare);
    for(i=0;i<10;i++)
      cout<<a[i]<<" ";
    return 0;
}

