//program 7-3
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF=1000000;
const int N=100;
const int M=10000;
int top;  //当前边下标
int dist[N], pre[N];//dist[i]表示源点到点i最短距离，pre[i]记录前驱
bool vis[N];//标记数组
int c[N];//入队次数
int maxflow;//最大流

struct Vertex
{
   int first;
}V[N];
struct Edge
{
   int v, next;
   int cap, flow,cost;
}E[M];
void init()
{
    memset(V, -1, sizeof(V));
    top=0;
    maxflow=0;
}
void add_edge(int u, int v, int c,int cost)
{
    E[top].v = v;
    E[top].cap = c;
    E[top].flow = 0;
    E[top].cost = cost;
    E[top].next = V[u].first;
    V[u].first = top++;
}
void add(int u,int v, int c,int cost)
{
    add_edge(u,v,c,cost);
    add_edge(v,u,0,-cost);
}

bool SPFA(int s, int t, int n)//求最短费用路的SPFA
{
    int i, u, v;
    queue <int> qu; // 队列，STL实现
    memset(vis,false,sizeof(vis));//访问标记初始化
    memset(c,0,sizeof(c));   //入队次数初始化
    memset(pre,-1,sizeof(pre)); //前驱初始化
    for(i=1;i<=n;i++)
    {
        dist[i]=INF; //距离初始化
    }
    vis[s]=true; //顶点入队vis要做标记
    c[s]++;     //要统计顶点的入队次数
    dist[s]=0;
    qu.push(s);
    while(!qu.empty())
    {
        u=qu.front();
        qu.pop();
        vis[u]=false;
        //队头元素出队，并且消除标记
        for(i=V[u].first; i!=-1; i=E[i].next)//遍历顶点u的邻接表
        {
            v=E[i].v;
            if(E[i].cap>E[i].flow && dist[v]>dist[u]+E[i].cost)//松弛操作
            {
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i; //记录前驱
                if(!vis[v]) //顶点v不在队内
                {
                    c[v]++;
                    qu.push(v);   //入队
                    vis[v]=true; //标记
                    if(c[v]>n) //超过入队上限，说明有负环
                        return false;
                }
            }
        }
    }
    cout<<"最短路数组"<<endl;
    cout<<"dist[ ]=";
    for(int i=1;i<=n;i++)
       cout<<"  "<<dist[i];
    cout<<endl;
    if(dist[t]==INF)
        return false; //如果距离为INF，说明无法到达，返回false
    return true;
}
int MCMF(int s,int t,int n) //minCostMaxFlow
{
    int d; //可增流量
    int i,mincost;//maxflow 当前最大流量，mincost当前最小费用
    mincost=0;
    while(SPFA(s,t,n))//表示找到了从s到t的最短路
    {
        d=INF;
        cout<<endl;
        cout<<"增广路径："<<t;
        for(i=pre[t]; i!=-1; i=pre[E[i^1].v])
        {
            d=min(d, E[i].cap-E[i].flow); //找最小可增流量
            cout<<"--"<<E[i^1].v;
        }
        cout<<"增流："<<d<<endl;
        cout<<endl;
        maxflow+=d; //更新最大流
        for(i=pre[t]; i!=-1; i=pre[E[i^1].v])//修改残余网络，增加增广路上相应弧的容量，并减少其反向边容量
        {
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        mincost+=dist[t]*d; //dist[t]为该路径上单位流量费用之和 ，最小费用更新
   }
    return mincost;
}

void printg(int n)//输出网络邻接表
{
   cout<<"----------网络邻接表如下：----------"<<endl;
   for(int i=1;i<=n;i++)
   {
       cout<<"v"<<i<<"  ["<<V[i].first;
       for(int j=V[i].first;~j;j=E[j].next)
           cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].cost<<"   "<<E[j].next;
       cout<<"]"<<endl;

   }
   cout<<endl;
}
void printflow(int n)//输出实流边
{
   cout<<"----------实流边如下：----------"<<endl;
   for(int i=1;i<=n;i++)
     for(int j=V[i].first;~j;j=E[j].next)
        if(E[j].flow>0)
        {
           cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"   "<<E[j].flow<<"   "<<E[j].cost;
           cout<<endl;
        }
}

int main()
{
    int n, m;
    int u, v, w,c;
    cout<<"请输入结点个数n和边数m:"<<endl;
    cin>>n>>m;
    init();//初始化
    cout<<"请输入两个结点u,v,边(u--v)的容量w,单位容量费用c:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w>>c;
        add(u,v,w,c);
    }
    cout<<endl;
    printg(n);//输出初始网络邻接表
    cout<<"网络的最小费用:"<<MCMF(1,n,n)<<endl;
    cout<<"网络的最大流值:"<<maxflow<<endl;
    cout<<endl;
    printg(n);//输出最终网络
    printflow(n);//输出实流边
    return 0;
}
