//mysort3
#include<cstdio>
#include<iostream>
#include<functional>
#include<algorithm>
using namespace std;

int main()
{
    int a[10]={7,4,5,23,2,73,41,52,28,60},i;
    for(i=0;i<10;i++)
      cout<<a[i]<<" ";
    cout<<endl;
    sort(a,a+10,greater<int>());//从大到小排序
    for(i=0;i<10;i++)
      cout<<a[i]<<" ";
    return 0;
}
