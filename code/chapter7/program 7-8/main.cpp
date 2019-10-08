//program 7-8
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
bool flag[N*N];//标记染黑色的结点
bool dfsflag[N*N];//深度搜索到的结点

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
void DFS(int s)//深度搜索
{
   for(int i=V[s].first;~i;i=E[i].next)//读当前结点的邻接表
       if(E[i].cap>E[i].flow)
       {
           int u=E[i].v;
           if(!dfsflag[u])
           {
               dfsflag[u]=true;
               DFS(u);
           }
       }
}
void print(int m,int n)//输出最佳方案
{
   cout<<"----------最佳方案如下：----------"<<endl;
   cout<<"选中的物品编号："<<endl;
   DFS(0);
   for(int i=1;i<=m*n;i++)
       if((flag[i]&&dfsflag[i])||(!flag[i]&&!dfsflag[i]))
           cout<<i<<"  ";
}

int main()
{
    int n, m, total,sum=0;;
    int map[N][N];
    memset(flag, 0, sizeof(flag));
    memset(dfsflag, 0, sizeof(dfsflag));
    int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//右下左上四个方向
    cout<<"请输入货架的行数m和列数n:"<<endl;
    cin>>m>>n;
    init();
    total=m*n;
    cout<<"请依次输入每行每个商品的价值:"<<endl;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>map[i][j];
            sum+=map[i][j];
        }
    //创建残余网络
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if((i+j)%2==0) //染黑色,当前物品位置(i,j)
            {
                add(0,(i-1)*n+j,map[i][j]);//从源点到当前物品结点有一条有向边，容量为该物品价值
                flag[(i-1)*n+j]=1;//标记染黑色物品
                //当前物品结点到四个相邻物品结点发出一条有向边，容量为无穷大
                for(int k=0;k<4;k++)
                {
                    int x=i+dir[k][0];
                    int y=j+dir[k][1];
                    if(x<=m&&x>0 && y<=n&&x>0)//边界限制
                       add((i-1)*n+j,(x-1)*n+y,INF);
                }
            }
            else //染白色,当前物品位置(i,j)
                add((i-1)*n+j,total+1,map[i][j]);//从当前物品结点到汇点有一条有向边，容量为该物品价值
        }
    cout<<endl;
    printg(total+2);//输出初始网络邻接表
    cout<<"挑选物品的最大价值:"<<sum-Isap(0,total+1,total+2)<<endl;
    cout<<endl;
    printg(total+2);//输出最终网络邻接表
    print(m,n);//输出最佳方案
    return 0;
}
