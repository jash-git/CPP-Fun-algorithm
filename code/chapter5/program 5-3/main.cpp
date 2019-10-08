//program 5-3
#include <iostream>
#include <string.h>
#define MX 50
using namespace std;

int x[MX];         //解分量
int map[MX][MX];  //图的邻接矩阵
int sum=0;   //记录解的个数
int n,m,edge;  //节点数和颜色数

//创建邻接矩阵
void CreatMap()
{
    int u,v;
    cout << "请输入边数:";
    cin >> edge;
    memset(map,0,sizeof(map));//邻接矩阵里面的数据初始化为0,meset需要引入#include <string.h>
    cout << "请依次输入有边相连的两个结点u和v,用空格分开:";
    for(int i=1;i<=edge;i++)
    {
        cin>>u>>v;
        map[u][v]=map[v][u]=1;
    }
}
//约束条件
bool OK(int t)
{
    for(int j=1;j<t;j++)
    {
        if(map[t][j])      //如果t与j邻接
        {
            if(x[j]==x[t]) //判断t与j的着色号是否相同
                return false;
        }
    }
    return true;
}
//搜索函数
void Backtrack(int t)
{

    if(t>n) //到达叶子,找到一个着色方案
    {
        sum++;
        cout<<"第"<<sum<<"种方案：";
        for(int i=1;i<=n;i++) //输出该着色方案
            cout<<x[i]<<" ";
        cout<<endl;
    }
    else{
        for(int i=1;i<=m;i++) //每个结点尝试m种颜色
        {
            x[t]=i;
            if(OK(t))
                Backtrack(t+1);
        }
    }
}
int main()
{
    cout<<"输入节点数： ";
    cin>>n;
    cout<<"输入颜色数： ";
    cin>>m;
    cout<<"输入无向图的邻接矩阵："<<endl;
    CreatMap();
    Backtrack(1);
}
