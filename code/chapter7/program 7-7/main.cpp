//program 7-7
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
bool flag[N];//���ѡ�еĽ��

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
    cout<<"��ʼ���߶�"<<endl;
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
                   cout<<"����·����"<<t;
                   while(u!=s)
                   {
                       int j=pre[u];
                       E[j].flow+=d;
                       E[j^1].flow-=d;
                       u=E[j^1].v;
                       cout<<"--"<<u;
                   }
                   cout<<"������"<<d<<endl;
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
           cout<<"������ǩ��߶�"<<endl;
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
void printg(int n)//��������ڽӱ�
{
   cout<<"----------�����ڽӱ����£�----------"<<endl;
   for(int i=0;i<=n;i++)
   {
       cout<<"v"<<i<<"  ["<<V[i].first;
       for(int j=V[i].first;~j;j=E[j].next)
           cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].next;
       cout<<"]"<<endl;
   }
}
void DFS(int s)//������������淽��
{
   for(int i=V[s].first;~i;i=E[i].next)//����ǰ�����ڽӱ�
       if(E[i].cap>E[i].flow)
       {
           int u=E[i].v;
           if(!flag[u])
           {
               flag[u]=true;
               DFS(u);
           }
       }
}
void print(int m,int n)//�����ѷ���
{
   cout<<"----------�����淽�����£�----------"<<endl;
   DFS(0);
   cout<<"ѡ�е�ʵ���ţ�"<<endl;
   for(int i=1;i<=m;i++)
       if(flag[i])
          cout<<i<<"  ";
   cout<<endl;
   cout<<"ѡ�е�������ţ�"<<endl;
   for(int i=m+1;i<=m+n;i++)
      if(flag[i])
          cout<<i-m<<"  ";
}

int main()
{
    int n, m,sum=0,total;
    int cost,num;
    memset(flag, 0, sizeof(flag));
    cout<<"������ʵ����m��������n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    cout<<"����������ʵ�������Ч��͸�ʵ����Ҫ���������(Ϊ0����):"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>cost;
        sum+=cost;
        add(0, i, cost);//Դ�㵽ʵ����Ŀ�ıߣ�����Ϊ����ĿЧ��
        while(cin>>num,num) //numΪ����Ŀ��Ҫ���������
            add(i, m+num, INF);//ʵ����Ŀ����Ҫ�����ıߣ�����Ϊ�����
    }
    cout<<"�������������������ķ���:"<<endl;
    for(int j=m+1;j<=total;j++)
    {
        cin>>cost;
        add(j, total+1, cost);//ʵ�����������ıߣ�����Ϊʵ����������
    }
    cout<<endl;
    printg(total+2);//�����ʼ�����ڽӱ�
    cout<<"�������:"<<sum-Isap(0,total+1,total+2)<<endl;
    cout<<endl;
    printg(total+2);//������������ڽӱ�
    print(m,n);//�����ѷ���
    return 0;
}
