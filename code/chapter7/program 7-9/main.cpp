//program 7-9
#include<iostream>
#include<cstring>
#include<map>
#include <queue>
using namespace std;

#define INF 1000000000
#define M 150
#define N 10000
int top;  //当前边下标
int dist[N], pre[N];//dist[i]表示源点到点i最短距离，pre[i]记录前驱
bool vis[N];//标记数组
int c[N];//入队次数
int maxflow,mincost;//maxflow 当前最大流量，mincost当前最小费用
string str[M];
map<string,int> maze;

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

bool SPFA(int s, int t, int n)//求最小费用路的SPFA
{
    int i, u, v;
    queue <int> qu; // 队列，STL实现
    memset(vis,0,sizeof(vis));//访问标记初始化
    memset(c,0,sizeof(c));   //入队次数初始化
    memset(pre,-1,sizeof(pre)); //前驱初始化
    for(i=1;i<=n;i++)
    {
        dist[i]=INF; //距离初始化
    }
    vis[s]=true; //结点入队vis要做标记
    c[s]++;     //要统计结点的入队次数
    dist[s]=0;
    qu.push(s);
    while(!qu.empty())
    {
        u=qu.front();
        qu.pop();
        vis[u]=false;
        //队头元素出队，并且消除标记
        for(i=V[u].first; i!=-1; i=E[i].next)//遍历结点u的邻接表
        {
            v=E[i].v;
            if(E[i].cap>E[i].flow && dist[v]>dist[u]+E[i].cost)//松弛操作
            {
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i; //记录前驱
                if(!vis[v]) //结点v不在队内
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
    maxflow=mincost=0;//maxflow 当前最大流量，mincost当前最小费用
    while(SPFA(s,t,n))//表示找到了从s到t的最短路
    {
        d=INF;
        cout<<endl;
        cout<<"增广路径："<<t;
        for(int i=pre[t]; i!=-1; i=pre[E[i^1].v])
        {
            d=min(d, E[i].cap-E[i].flow); //找最小可增流量
            cout<<"--"<<E[i^1].v;
        }
        cout<<"增流："<<d<<endl;
        cout<<endl;
        for(int i=pre[t]; i!=-1; i=pre[E[i^1].v])//修改残余网络，增加增广路上相应弧的容量，并减少其反向边容量
        {
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        maxflow+=d; //更新最大流
        mincost+=dist[t]*d; //dist[t]为该路径上单位流量费用之和 ，最小费用更新
   }
   return maxflow;
}

void print(int s,int t)
{
    int v;
    vis[s]=1;
    for(int i=V[s].first;~i;i=E[i].next)
      if(!vis[v=E[i].v]&&((E[i].flow>0&&E[i].cost<=0)||(E[i].flow<0&&E[i].cost>=0)))
      {
         print(v,t);
         if(v<=t)
           cout<<str[v]<<endl;
      }
}
int main()
{
    int n,m,i;
    string str1,str2;
    cout<<"请输入景点个数n和直达线路数m:"<<endl;
    cin>>n>>m;
    init();//初始化
    maze.clear();
    cout<<"请输入景点名str"<<endl;
    for(i=1;i<=n;i++)
    {
       cin>>str[i];
       maze[str[i]]=i;
       if(i==1||i==n)
         add(i,i+n,2,0);
       else
         add(i,i+n,1,0);
    }
    cout<<"请输入可以直达的两个景点名str1,str2"<<endl;
    for(i=1;i<=m;i++)
    {
        cin>>str1>>str2;
        int a=maze[str1],b=maze[str2];
        if(a<b)
        {
          if(a==1&&b==n)
            add(a+n,b,2,-1);
          else
            add(a+n,b,1,-1);
        }
        else
        {
           if(b==1&&a==n)
             add(b+n,a,2,-1);
           else
             add(b+n,a,1,-1);
         }
    }
    if(MCMF(1,2*n,2*n)==2)
    {
      cout<<"最多经过的景点个数:"<<-mincost<<endl;
      cout<<"依次经过的景点："<<endl;
      cout<<str[1]<<endl;
      memset(vis,0,sizeof(vis));//访问标记初始化
      print(1,n);
      cout<<str[1]<<endl;
    }
    else
      cout<<"No Solution!"<<endl;
    return 0;
}
