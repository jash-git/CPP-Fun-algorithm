//program 7-4-1
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int inf = 0x3fffffff;
const int N=100;
const int M=10000;
int match[N];
bool vis[N];
int top;

struct Vertex
{
   int first;
}V[N];
struct Edge
{
   int v, next;
}E[M];
void init()
{
    memset(V, -1, sizeof(V));
    top = 0;
    memset(match, 0, sizeof(match));
}
void add(int u, int v)
{
    E[top].v = v;
    E[top].next = V[u].first;
    V[u].first = top++;
}

void printg(int n)//��������ڽӱ�
{
   cout<<"----------�ڽӱ����£�----------"<<endl;
   for(int i=1;i<=n;i++)
   {
       cout<<"v"<<i<<"  ["<<V[i].first;
       for(int j=V[i].first;~j;j=E[j].next)
           cout<<"]--["<<E[j].v<<"   "<<E[j].next;
       cout<<"]"<<endl;
   }
}
void print(int n)//�����Է���
{
   cout<<"----------��Է������£�----------"<<endl;
   for(int i=1;i<=n;i++)
      if(match[i])
        cout<<i<<"--"<<match[i]<<endl;
}
bool maxmatch(int u)
{
    int v;
    for(int j=V[u].first;~j;j=E[j].next) //��u�������ڽӱ�
    {
       v=E[j].v;//u���ڽӵ�v
       if(!vis[v])
       {
           vis[v]=1;
           if(!match[v]||maxmatch(match[v]))
           {
               match[u]=v;
               match[v]=u;
               return true;
           }
       }
    }
    return false;
}

int main()
{
    int n, m,total,num=0;
    int u, v;
    cout<<"������Ů����Ա����m��������Ա����n:"<<endl;
    cin>>m>>n;
    init();
    total=m+n;
    cout<<"�����������ϵ�Ů����Ա���u��������Ա���v(������Ϊ-1����):"<<endl;
    while(cin>>u>>v,u+v!=-2)
    {
        add(u,v);
        add(v,u);
    }
    cout<<endl;
    printg(total);//��������ڽӱ�
    for(int i=1;i<=m;i++)
    {
        memset(vis,0,sizeof(vis));
        if(maxmatch(i))
            num++;
    }
    cout<<"��������:"<<num<<endl;
    cout<<endl;
    print(m);//�����Է���
    return 0;
}
