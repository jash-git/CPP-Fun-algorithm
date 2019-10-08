//program 2-4-1
#include <queue>
#include <iostream>
#include<cstring>
#include<windows.h>
using namespace std;
const int N = 100; // 城市的个数可修改
const int INF = 1e7; // 无穷大
int map[N][N],dist[N],n,m;
int flag[N];
struct  Node{
    int u,step;
    Node(){};
    Node(int a,int sp){
        u=a;step=sp;
    }
    bool operator < (const  Node& a)const{  // 重载 <
        return step>a.step;
    }
};
void Dijkstra(int st){
    priority_queue <Node> Q;  // 优先队列优化
    Q.push(Node(st,0));
    memset(flag,0,sizeof(flag));//初始化flag数组为0
    for(int i=1;i<=n;++i)
      dist[i]=INF; // 初始化所有距离为，无穷大
    dist[st]=0;
    while(!Q.empty())
    {
        Node it=Q.top();//优先队列队头元素为最小值
        Q.pop();
        int t=it.u;
        if(flag[t])//说明已经找到了最短距离，该结点是队列里面的重复元素
            continue;
        flag[t]=1;
        for(int i=1;i<=n;i++)
        {
            if(!flag[i]&&map[t][i]<INF){ // 判断与当前点有关系的点，并且自己不能到自己
                if(dist[i]>dist[t]+map[t][i])
                {   // 求距离当前点的每个点的最短距离,进行松弛操作
                    dist[i]=dist[t]+map[t][i];
                    Q.push(Node(i,dist[i]));// 把更新后的最短距离压入优先队列，注意：里面的元素有重复
                 }
            }
        }
    }
}
int main()
{
        int u,v,w,st;
        system("color 0d");//设置背景及字体颜色
        cout << "请输入城市的个数："<<endl;
        cin >> n;
        cout << "请输入城市之间的路线的个数:"<<endl;
        cin >>m;
        for(int i=1;i<=n;i++)//初始化图的邻接矩阵
          for(int j=1;j<=n;j++)
          {
              map[i][j]=INF;//初始化邻接矩阵为无穷大
          }
        cout << "请输入城市之间u,v的路线以及距离w："<<endl;
        while(m--)
        {
            cin>>u>>v>>w;
            map[u][v]=min(map[u][v],w); //邻接矩阵储存，保留最小的距离
        }
        cout<<"请输入小明所在的位置:"<<endl; ;
        cin>>st;
        Dijkstra(st);
        cout <<"小明所在的位置:"<<st<<endl;
        for(int i=1;i<=n;i++)
        {
             cout <<"小明:"<<st<<"--->"<<"要去的位置:"<<i;
             if(dist[i]==INF)
                cout << "sorry,无路可达"<<endl;
             else
                cout << " 最短距离为:"<<dist[i]<<endl;
        }
    return 0;
}


