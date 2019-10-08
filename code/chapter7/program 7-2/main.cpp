//program 7-2
#include<iostream>
#include<queue>
#include<iomanip>
#include<cstring>
using namespace std;

const int maxn = 100; //��󶥵���
const int INF = (1<<30)-1;
int g[maxn][maxn]; //�������磨��ʼʱ����Ϊ������
int f[maxn][maxn]; //ʵ�����磨��ʼʱ����Ϊ0����
int pre[maxn]; //ǰ������
bool vis[maxn];//��������
int n,m; //�������n�ͱߵ�����m

bool bfs(int s,int t)
{
    memset(pre,-1,sizeof(pre));
    memset(vis,false,sizeof(vis));
    queue<int>q;
    vis[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i=1;i<=n; i++)//Ѱ�ҿ�����·
        {
            if(!vis[i]&&g[now][i]>0)//δ���������б�����
            {
                vis[i] = true;
                pre[i] = now;
                if(i==t)  return true;//�ҵ�һ��������·
                q.push(i);
            }
        }
    }
    return false;//�Ҳ���������·
}

int EK(int s, int t)
{
    int v,w,d,maxflow;
    maxflow = 0;
    while(bfs(s,t))//��������
    {
        v=t;
        d=INF;
        while(v!=s)//�ҿ�����d
        {
            w=pre[v];//w��¼v��ǰ��
            if(d>g[w][v])
                d=g[w][v];
            v=w;
        }
        maxflow+=d;
        v=t;
        while(v!=s)//�ؿ�����·����
        {
            w=pre[v];
            g[w][v]-=d;  //��������������߼���
            g[v][w]+=d;  //���������з��������
            if(f[v][w]>0) //ʵ������������Ƿ����,�����,�������������
                f[v][w]-=d;
            else
                f[w][v]+=d;
            v=w;
         }
    }
    return maxflow;
}
void print()//���ʵ������
{
    cout<<endl;
    cout<<"----------ʵ���������£�----------"<<endl;
    cout<<"  ";
    for(int i=1;i<=n;i++)
       cout<<setw(7)<<"v"<<i;
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<"v"<<i;
        for(int j=1;j<=n;j++)
           cout<<setw(7)<<f[i][j]<<" ";
        cout<<endl;
    }
}
int main()
{
    int u,v,w;
    memset(g,0,sizeof(g));//���������ʼ��Ϊ0
    memset(f,0,sizeof(f));//ʵ�������ʼ��Ϊ0
    cout<<"�����������n�ͱ���m:"<<endl;
    cin>>n>>m;
    cout<<"�������������u,v����(u--v)������w:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        g[u][v]+=w;
    }
    cout<<"����������ֵ:"<<EK(1,n)<<endl;
    print();//���ʵ������
    return 0;
}
