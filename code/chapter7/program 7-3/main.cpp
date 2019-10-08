//program 7-3
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF=1000000;
const int N=100;
const int M=10000;
int top;  //��ǰ���±�
int dist[N], pre[N];//dist[i]��ʾԴ�㵽��i��̾��룬pre[i]��¼ǰ��
bool vis[N];//�������
int c[N];//��Ӵ���
int maxflow;//�����

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

bool SPFA(int s, int t, int n)//����̷���·��SPFA
{
    int i, u, v;
    queue <int> qu; // ���У�STLʵ��
    memset(vis,false,sizeof(vis));//���ʱ�ǳ�ʼ��
    memset(c,0,sizeof(c));   //��Ӵ�����ʼ��
    memset(pre,-1,sizeof(pre)); //ǰ����ʼ��
    for(i=1;i<=n;i++)
    {
        dist[i]=INF; //�����ʼ��
    }
    vis[s]=true; //�������visҪ�����
    c[s]++;     //Ҫͳ�ƶ������Ӵ���
    dist[s]=0;
    qu.push(s);
    while(!qu.empty())
    {
        u=qu.front();
        qu.pop();
        vis[u]=false;
        //��ͷԪ�س��ӣ������������
        for(i=V[u].first; i!=-1; i=E[i].next)//��������u���ڽӱ�
        {
            v=E[i].v;
            if(E[i].cap>E[i].flow && dist[v]>dist[u]+E[i].cost)//�ɳڲ���
            {
                dist[v]=dist[u]+E[i].cost;
                pre[v]=i; //��¼ǰ��
                if(!vis[v]) //����v���ڶ���
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
    int i,mincost;//maxflow ��ǰ���������mincost��ǰ��С����
    mincost=0;
    while(SPFA(s,t,n))//��ʾ�ҵ��˴�s��t�����·
    {
        d=INF;
        cout<<endl;
        cout<<"����·����"<<t;
        for(i=pre[t]; i!=-1; i=pre[E[i^1].v])
        {
            d=min(d, E[i].cap-E[i].flow); //����С��������
            cout<<"--"<<E[i^1].v;
        }
        cout<<"������"<<d<<endl;
        cout<<endl;
        maxflow+=d; //���������
        for(i=pre[t]; i!=-1; i=pre[E[i^1].v])//�޸Ĳ������磬��������·����Ӧ�����������������䷴�������
        {
            E[i].flow+=d;
            E[i^1].flow-=d;
        }
        mincost+=dist[t]*d; //dist[t]Ϊ��·���ϵ�λ��������֮�� ����С���ø���
   }
    return mincost;
}

void printg(int n)//��������ڽӱ�
{
   cout<<"----------�����ڽӱ����£�----------"<<endl;
   for(int i=1;i<=n;i++)
   {
       cout<<"v"<<i<<"  ["<<V[i].first;
       for(int j=V[i].first;~j;j=E[j].next)
           cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].cost<<"   "<<E[j].next;
       cout<<"]"<<endl;

   }
   cout<<endl;
}
void printflow(int n)//���ʵ����
{
   cout<<"----------ʵ�������£�----------"<<endl;
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
    cout<<"�����������n�ͱ���m:"<<endl;
    cin>>n>>m;
    init();//��ʼ��
    cout<<"�������������u,v,��(u--v)������w,��λ��������c:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w>>c;
        add(u,v,w,c);
    }
    cout<<endl;
    printg(n);//�����ʼ�����ڽӱ�
    cout<<"�������С����:"<<MCMF(1,n,n)<<endl;
    cout<<"����������ֵ:"<<maxflow<<endl;
    cout<<endl;
    printg(n);//�����������
    printflow(n);//���ʵ����
    return 0;
}
