//program 2-4
#include <iostream>
#include<windows.h>
#include<stack>
using namespace std;
const int N=100; // ���еĸ������޸�
const int INF=1e7; // �����10000000
int map[N][N],dist[N],p[N],n,m;//n���еĸ�����mΪ���м�·�ߵ�����
bool flag[N]; //���s[i]����true��˵������i�Ѿ����뵽����S;���򶥵�i���ڼ���V-S
void Dijkstra(int u)
{
   for(int i=1; i<=n; i++)
    {
     dist[i] =map[u][i]; //��ʼ��Դ��u������������������·������
     flag[i]=false;
     if(dist[i]==INF)
       p[i]=-1; //Դ��u���ö����·������Ϊ�����˵������i��Դ��u������
     else
       p[i]=u; //˵������i��Դ��u���ڣ����ö���i��ǰ��p[i]=u
     }
    dist[u] = 0;
    flag[u]=true;   //��ʼʱ������S��ֻ��һ��Ԫ�أ�Դ��u
    for(int i=1; i<=n; i++)
     {
        int temp = INF,t = u;
        for(int j=1; j<=n; j++) //�ڼ���V-S��Ѱ�Ҿ���Դ��u����Ķ���t
          if(!flag[j]&&dist[j]<temp)
           {
            t=j;
            temp=dist[j];
          }
        if(t==u) return ; //�Ҳ���t������ѭ��
        flag[t]= true;  //���򣬽�t���뼯��
        for(int j=1;j<=n;j++)//������t���ڽӵĶ��㵽Դ��u�ľ���
          if(!flag[j]&& map[t][j]<INF)
            if(dist[j]>(dist[t]+map[t][j]))
             {
               dist[j]=dist[t]+map[t][j] ;
               p[j]=t ;
             }
       }
}
void findpath(int u)
{
  int x;
  stack<int>s;
  cout<<"Դ��Ϊ��"<<u<<endl;
  for(int i=1;i<=n;i++)
  {
    x=p[i];
    while(x!=-1)
    {
      s.push(x);
      x=p[x];
    }
    cout<<"Դ�㵽�������������·��Ϊ��";
    while(!s.empty())
    {
      cout<<s.top()<<"--";
      s.pop();
    }
    cout<<i<<";��̾���Ϊ��"<<dist[i]<<endl;
  }
}

int main()
{
        int u,v,w,st;
        system("color 0d");
        cout << "��������еĸ�����"<<endl;cin >> n;
        cout << "���������֮���·�ߵĸ���:"<<endl;cin >>m;
        cout << "���������֮���·���Լ����룺"<<endl;
        for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
          {
             map[i][j]=INF;//��ʼ���ڽӾ���Ϊ�����
          }
        while(m--)
        {
            cin >> u >> v >> w;
            map[u][v] =min(map[u][v],w); //�ڽӾ��󴢴棬������С�ľ���
        }
        cout <<"������С�����ڵ�λ��:"<<endl; ;
        cin >> st;
        Dijkstra(st);
        cout <<"С�����ڵ�λ��:"<<st<<endl;
        for(int i=1;i<=n;i++)
        {
             cout <<"С��:"<<st<<" - "<<"Ҫȥ��λ��:"<<i;
             if(dist[i] == INF)
               cout << "sorry,��·�ɴ�"<<endl;
             else
               cout << " ��̾���Ϊ:"<<dist[i]<<endl;
         }

         findpath(st);
         return 0;
}

