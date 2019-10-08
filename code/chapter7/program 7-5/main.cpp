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
void print(int m,int n)//������ŷ���
{
   cout<<"----------���ŷ������£�----------"<<endl;
   cout<<"ÿ�������ŵİ��������"<<endl;
   for(int i=1;i<=m;i++)//��ÿ�������ŵ��ڽӱ�
   {
       cout<<"��"<<i<<"�������Ű��ŵĻ�������:";
       for(int j=V[i].first;~j;j=E[j].next)//����i�������ŵ��ڽӱ�
          if(E[j].flow==1)
             cout<<E[j].v-m<<"  ";
       cout<<endl;
   }
}

int main()
{
    int n, m,sum=0,total;
    int cost;
    cout<<"�������������m�ͻ�������n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    cout<<"����������ÿ������������:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>cost;
        sum+=cost;
        add(0, i, cost);//Դ�㵽�����ŵıߣ�����Ϊ�ô���������
    }
    cout<<"����������ÿ���������ɰ�������:"<<endl;
    for(int j=m+1;j<=total;j++)
    {
        cin>>cost;
        add(j, total+1, cost);//�����������ıߣ�����Ϊ�������ɰ�������
    }
    for(int i=1;i<=m;i++)
        for(int j=m+1;j<=total;j++)
           add(i, j, 1);//�����ŵ��������ıߣ�����Ϊ1
    cout<<endl;
    printg(total+2);//�����ʼ�����ڽӱ�
    if(sum==Isap(0,total+1,total+2))
    {
        cout<<"���������ųɹ���";
        cout<<endl;
        print(m,n);//�����ѷ���
        cout<<endl;
        printg(total+2);//������������ڽӱ�
    }
    else
        cout<<"�޷��������д����ţ�";
    return 0;
}
