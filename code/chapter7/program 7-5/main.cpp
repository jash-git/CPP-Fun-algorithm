//program 7-5
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF=0x3fffffff;
const int N=100;
const int M=10000;
int top;
int h[N], pre[N], g[N];

struct Vertex
{
   int first;
}V[N];
struct Edge
{
   int v, next;
   int cap, flow;
}E[M];
void init()
{
    memset(V, -1, sizeof(V));
    top = 0;
}
void add_edge(int u, int v, int c)
{
    E[top].v = v;
    E[top].cap = c;
    E[top].flow = 0;
    E[top].next = V[u].first;
    V[u].first = top++;
}
void add(int u,int v, int c)
{
    add_edge(u,v,c);
    add_edge(v,u,0);
}
void set_h(int t,int n)
{
    queue<int> Q;
    memset(h, -1, sizeof(h));
    memset(g, 0, sizeof(g));
    h[t] = 0;
    Q.push(t);
    while(!Q.empty())
    {
       int v = Q.front(); Q.pop();
       ++g[h[v]];
       for(int i = V[v].first; ~i; i = E[i].next)
       {
          int u = E[i].v;
          if(h[u] == -1)
          {
             h[u] = h[v] + 1;
             Q.push(u);
           }
        }
    }
    cout<<"初始化高度"<<endl;
    cout<<"h[ ]=";
    for(int i=1;i<=n;i++)
       cout<<"  "<<h[i];
    cout<<endl;
}
int Isap(int s, int t,int n)
{
    set_h(t,n);
    int ans=0, u=s;
    int d;
    while(h[s]<n)
    {
        int i=V[u].first;
        if(u==s)
           d=INF;
        for(; ~i; i=E[i].next)
        {
           int v=E[i].v;
           if(E[i].cap>E[i].flow && h[u]==h[v]+1)
           {
                u=v;
                pre[v]=i;
                d=min(d, E[i].cap-E[i].flow);
                if(u==t)
                {
                   cout<<endl;
                   cout<<"增广路径："<<t;
                   while(u!=s)
                   {
                       int j=pre[u];
                       E[j].flow+=d;
                       E[j^1].flow-=d;
                       u=E[j^1].v;
                       cout<<"--"<<u;
                   }
                   cout<<"增流："<<d<<endl;
                   ans+=d;
                   d=INF;
                }
                break;
            }
        }
        if(i==-1)
        {
           if(--g[h[u]]==0)
              break;
           int hmin=n-1;
           for(int j=V[u].first; ~j; j=E[j].next)
              if(E[j].cap>E[j].flow)
                 hmin=min(hmin, h[E[j].v]);
           h[u]=hmin+1;
           cout<<"重贴标签后高度"<<endl;
           cout<<"h[ ]=";
           for(int i=1;i<=n;i++)
              cout<<"  "<<h[i];
           cout<<endl;
           ++g[h[u]];
           if(u!=s)
              u=E[pre[u]^1].v;
        }
    }
    return ans;
}
void printg(int n)//输出网络邻接表
{
   cout<<"----------网络邻接表如下：----------"<<endl;
   for(int i=0;i<=n;i++)
   {
       cout<<"v"<<i<<"  ["<<V[i].first;
       for(int j=V[i].first;~j;j=E[j].next)
           cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].next;
       cout<<"]"<<endl;
   }
}
void print(int m,int n)//输出安排方案
{
   cout<<"----------安排方案如下：----------"<<endl;
   cout<<"每个代表团的安排情况："<<endl;
   for(int i=1;i<=m;i++)//读每个代表团的邻接表
   {
       cout<<"第"<<i<<"个代表团安排的会议桌号:";
       for(int j=V[i].first;~j;j=E[j].next)//读第i个代表团的邻接表
          if(E[j].flow==1)
             cout<<E[j].v-m<<"  ";
       cout<<endl;
   }
}

int main()
{
    int n, m,sum=0,total;
    int cost;
    cout<<"请输入代表团数m和会议桌数n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    cout<<"请依次输入每个代表团人数:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>cost;
        sum+=cost;
        add(0, i, cost);//源点到代表团的边，容量为该代表团人数
    }
    cout<<"请依次输入每个会议桌可安排人数:"<<endl;
    for(int j=m+1;j<=total;j++)
    {
        cin>>cost;
        add(j, total+1, cost);//会议桌到汇点的边，容量为会议桌可安排人数
    }
    for(int i=1;i<=m;i++)
        for(int j=m+1;j<=total;j++)
           add(i, j, 1);//代表团到会议桌的边，容量为1
    cout<<endl;
    printg(total+2);//输出初始网络邻接表
    if(sum==Isap(0,total+1,total+2))
    {
        cout<<"会议桌安排成功！";
        cout<<endl;
        print(m,n);//输出最佳方案
        cout<<endl;
        printg(total+2);//输出最终网络邻接表
    }
    else
        cout<<"无法安排所有代表团！";
    return 0;
}
