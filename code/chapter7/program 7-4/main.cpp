//program 7-4
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int inf = 0x3fffffff;
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
           d=inf;
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
                   d=inf;
                }
                break;
            }
        }
        if(i==-1)
        {
           if(--g[h[u]]==0)
              break;
           int hmin=n-1;
           //cur[u]=V[u].first;
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
void printflow(int n)//输出配对方案
{
   cout<<"----------配对方案如下：----------"<<endl;
   for(int i=1;i<=n;i++)
     for(int j=V[i].first;~j;j=E[j].next)
        if(E[j].flow>0)
        {
           cout<<i<<"--"<<E[j].v<<endl;
           break;
        }
}

int main()
{
    int n, m,total;
    int u, v;
    cout<<"请输入女推销员人数m和男推销员人数n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    for(int i=1;i<=m;i++)
        add(0, i, 1);//源点到女推销员的边
    for(int j=m+1;j<=total;j++)
        add(j, total+1, 1);//男推销员到汇点的边
    cout<<"请输入可以配合的女推销员编号u和男推销员编号v(两个都为-1结束):"<<endl;
    while(cin>>u>>v,u+v!=-2)
        add(u,v,1);
    cout<<endl;
    printg(total+2);//输出初始网络邻接表
    cout<<"最大配对数:"<<Isap(0,total+1,total+2)<<endl;
    cout<<endl;
    printg(total+2);//输出最终网络邻接表
    printflow(m);//输出配对方案
    return 0;
}
