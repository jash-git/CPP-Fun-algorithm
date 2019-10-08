//program 7-2
#include<iostream>
#include<queue>
#include<iomanip>
#include<cstring>
using namespace std;

const int maxn = 100; //最大顶点数
const int INF = (1<<30)-1;
int g[maxn][maxn]; //残余网络（初始时各边为容量）
int f[maxn][maxn]; //实流网络（初始时各边为0流）
int pre[maxn]; //前驱数组
bool vis[maxn];//访问数组
int n,m; //顶点个数n和边的数量m

bool bfs(int s,int t)
{
    memset(pre,-1,sizeof(pre));
    memset(vis,false,sizeof(vis));
    queue<int>q;
    vis[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i=1;i<=n; i++)//寻找可增广路
        {
            if(!vis[i]&&g[now][i]>0)//未被访问且有边相连
            {
                vis[i] = true;
                pre[i] = now;
                if(i==t)  return true;//找到一条可增广路
                q.push(i);
            }
        }
    }
    return false;//找不到可增广路
}

int EK(int s, int t)
{
    int v,w,d,maxflow;
    maxflow = 0;
    while(bfs(s,t))//可以增广
    {
        v=t;
        d=INF;
        while(v!=s)//找可增量d
        {
            w=pre[v];//w记录v的前驱
            if(d>g[w][v])
                d=g[w][v];
            v=w;
        }
        maxflow+=d;
        v=t;
        while(v!=s)//沿可增广路增流
        {
            w=pre[v];
            g[w][v]-=d;  //残余网络中正向边减流
            g[v][w]+=d;  //残余网络中反向边增流
            if(f[v][w]>0) //实流网络中如果是反向边,则减流,否则正向边增流
                f[v][w]-=d;
            else
                f[w][v]+=d;
            v=w;
         }
    }
    return maxflow;
}
void print()//输出实流网络
{
    cout<<endl;
    cout<<"----------实流网络如下：----------"<<endl;
    cout<<"  ";
    for(int i=1;i<=n;i++)
       cout<<setw(7)<<"v"<<i;
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<"v"<<i;
        for(int j=1;j<=n;j++)
           cout<<setw(7)<<f[i][j]<<" ";
        cout<<endl;
    }
}
int main()
{
    int u,v,w;
    memset(g,0,sizeof(g));//残余网络初始化为0
    memset(f,0,sizeof(f));//实流网络初始化为0
    cout<<"请输入结点个数n和边数m:"<<endl;
    cin>>n>>m;
    cout<<"请输入两个结点u,v及边(u--v)的容量w:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        g[u][v]+=w;
    }
    cout<<"网络的最大流值:"<<EK(1,n)<<endl;
    print();//输出实流网络
    return 0;
}
