//program 7-9
#include<iostream>
#include<cstring>
#include<map>
#include <queue>
using namespace std;

#define INF 1000000000
#define M 150
#define N 10000
int top;  //��ǰ���±�
int dist[N], pre[N];//dist[i]��ʾԴ�㵽��i��̾��룬pre[i]��¼ǰ��
bool vis[N];//�������
int c[N];//��Ӵ���
int maxflow,mincost;//maxflow ��ǰ���������mincost��ǰ��С����
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

bool SPFA(int s, int t, int n)//����С����·��SPFA
{
    int i, u, v;
    queue <int> qu; // ���У�STLʵ��
    memset(vis,0,sizeof(vis));//���ʱ�ǳ�ʼ��
    memset(c,0,sizeof(c));   //��Ӵ�����ʼ��
    memset(pre,-1,sizeof(pre)); //ǰ����ʼ��
    for(i=1;i<=n;i++)
    {
        dist[i]=INF; //�����ʼ��
    }
    vis[s]=true; //������visҪ�����
    c[s]++;     //Ҫͳ�ƽ�����Ӵ���
    dist[s]=0;
    qu.push(s);
    while(!qu.empty())
    {
        u=qu.front();
        qu.pop();
        vis[u]=false;
        //��ͷԪ�س��ӣ������������
        for(i=V[u].first; i!=-1; i=E[i].next)//�������u���ڽӱ�
        {
            v=E[i].v;
            if(E[i].cap>E[i].flow && dist[v]>dist[u]+E[i].cost)//�ɳڲ���
            {
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i; //��¼ǰ��
                if(!vis[v]) //���v���ڶ���
                {
                    c[v]++;
                    qu.push(v);   //���
                    vis[v]=true; //���
                    if(c[v]>n) //����������ޣ�˵���и���
                        return false;
                }
            }
        }
    }
    cout<<"���·����"<<endl;
    cout<<"dist[ ]=";
    for(int i=1;i<=n;i++)
       cout<<"  "<<dist[i];
    cout<<endl;
    if(dist[t]==INF)
        return false; //�������ΪINF��˵���޷��������false
    return true;
}
int MCMF(int s,int t,int n) //minCostMaxFlow
{
    int d; //��������
    maxflow=mincost=0;//maxflow ��ǰ���������mincost��ǰ��С����
    while(SPFA(s,t,n))//��ʾ�ҵ��˴�s��t�����·
    {
        d=INF;
        cout<<endl;
        cout<<"����·����"<<t;
        for(int i=pre[t]; i!=-1; i=pre[E[i^1].v])
        {
            d=min(d, E[i].cap-E[i].flow); //����С��������
            cout<<"--"<<E[i^1].v;
        }
        cout<<"������"<<d<<endl;
        cout<<endl;
        for(int i=pre[t]; i!=-1; i=pre[E[i^1].v])//�޸Ĳ������磬��������·����Ӧ�����������������䷴�������
        {
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        maxflow+=d; //���������
        mincost+=dist[t]*d; //dist[t]Ϊ��·���ϵ�λ��������֮�� ����С���ø���
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
    cout<<"�����뾰�����n��ֱ����·��m:"<<endl;
    cin>>n>>m;
    init();//��ʼ��
    maze.clear();
    cout<<"�����뾰����str"<<endl;
    for(i=1;i<=n;i++)
    {
       cin>>str[i];
       maze[str[i]]=i;
       if(i==1||i==n)
         add(i,i+n,2,0);
       else
         add(i,i+n,1,0);
    }
    cout<<"���������ֱ�������������str1,str2"<<endl;
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
      cout<<"��ྭ���ľ������:"<<-mincost<<endl;
      cout<<"���ξ����ľ��㣺"<<endl;
      cout<<str[1]<<endl;
      memset(vis,0,sizeof(vis));//���ʱ�ǳ�ʼ��
      print(1,n);
      cout<<str[1]<<endl;
    }
    else
      cout<<"No Solution!"<<endl;
    return 0;
}
