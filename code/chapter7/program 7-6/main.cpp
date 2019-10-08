//program 7-6
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
void print(int m,int n)//输出抽取方案
{
   cout<<"----------试题抽取方案：----------"<<endl;
   for(int i=1;i<=m;i++)//读每个题型的邻接表
   {
       cout<<"第"<<i<<"个题型抽取的试题号:";
       for(int j=V[i].first;~j;j=E[j].next)//读第i个题型的邻接表
          if(E[j].flow==1)
             cout<<E[j].v-m<<"  ";
       cout<<endl;
   }
}

int main()
{
    int n, m,sum=0,total;
    int cost,num;
    cout<<"请输入题型数m和试题总数n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    cout<<"请依次输入每种题型选择的数量:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>cost;
        sum+=cost;
        add(0, i, cost);//源点到题型的边，容量为该题型选择数量
    }
    cout<<"请依次输入每个试题所属的题型(0结束):"<<endl;
    for(int j=m+1;j<=total;j++)
    {
        while(cin>>num,num) //num为试题j属于的题型号，为0时结束
            add(num, j, 1);//题型号num到试题j的边，容量为1
        add(j, total+1,1);//试题j到汇点的边，容量为1
    }
    cout<<endl;
    printg(total+2);//输出初始网络邻接表
    if(sum==Isap(0,total+1,total+2))
    {
        cout<<"试题抽取成功！";
        cout<<endl;
        print(m,n);//输出抽取方案
        cout<<endl;
        printg(total+2);//输出最终网络邻接表
    }
    else
        cout<<"抽取试题不成功！";
    return 0;
}
