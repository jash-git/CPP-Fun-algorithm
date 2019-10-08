//program 5-5-2
#include<iostream>
#include<algorithm>
using namespace std ;
const int MX=10000+5 ;
int n;
struct node
{
    int id;
    int x,y;
}T[MX] ;
bool cmp(node a,node b)
{
    return min(b.x,a.y)>=min(b.y,a.x);//按照贝尔曼规则排序
}
int main()
{
    cout<<"请输入机器零件的个数 n:";
    cin>>n;
    cout<<"请依次输入每个机器零件在第一台机器上的加工时间x和第二台机器上的加工时间y:";
    for(int i=0;i<n;i++)
    {
        cin>>T[i].x>>T[i].y;
        T[i].id=i+1;
    }
    sort(T,T+n,cmp);   //排序
    int f1=0,f2=0;
    for(int i=0;i<n;i++)  //计算总时间
    {
       f1+=T[i].x;
       f2=max(f1,f2)+T[i].y;
     }
    cout<<"最优的机器零件加工顺序为:";
     for(int i=0;i<n;i++) //输出最优加工顺序
       cout<<T[i].id<<" ";
    cout<<endl;
    cout<<"最优的机器零件加工的时间为:";
    cout<<f2<<endl;
    return 0 ;
}
