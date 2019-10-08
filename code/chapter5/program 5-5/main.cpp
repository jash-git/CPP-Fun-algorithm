//program 5-5
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
const int MX=10000+5;
int n,bestf,f1,f2;//f1在第一台机器上加工的完成时间,f2在第二台机器上加工的完成时间
int x[MX],bestx[MX];
struct node
{
    int x,y;//机器零件在第一台机器上的加工时间x和第二台机器上的加工时间y
}T[MX];
void Backtrack(int t)
{
    if(t>n)
    {
        for(int i=1;i<=n;i++) //记录最优排列
           bestx[i]=x[i] ;
        bestf=f2;   // 更新最优值
        return ;
    }
    for(int i=t;i<=n;i++)  // 枚举
    {
        f1+=T[x[i]].x;
        int temp=f2;
        f2=max(f1,f2)+T[x[i]].y;
        if(f2<bestf)  //限界条件
        {
            swap(x[t] ,x[i]);  // 交换
            Backtrack(t+1);          // 继续深搜
            swap(x[t],x[i]);  // 复位，反操作
        }
        f1-=T[x[i]].x ;
        f2=temp ;
    }
}
int main()
{
    cout<<"请输入机器零件的个数 n:";
    cin>>n;
    cout<<"请依次输入每个机器零件在第一台机器上的加工时间x和第二台机器上的加工时间y:";
    for(int i=1;i<=n;i++)
    {
        cin>>T[i].x>>T[i].y;
        x[i]=i;
    }
    bestf=INF;    // 初始化
    f1=f2=0;
    memset(bestx,0,sizeof(bestx));
    Backtrack(1);         // 深搜排列树
    cout<<"最优的机器零件加工顺序为:";
    for(int i=1;i<=n;i++) //输出最优加工顺序
       cout<<bestx[i]<<" ";
    cout<<endl;
    cout<<"最优的机器零件加工的时间为:";
    cout<<bestf<<endl;
    return 0 ;
}
