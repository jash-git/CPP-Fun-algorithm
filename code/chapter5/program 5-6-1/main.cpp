//program 5-6-1
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M = 1<<13;
#define INF 0x3f3f3f3f
int dp[M+2][20];//dp[i][j] 表示第i个状态，到达第j个城市的最短路径
int g[15][15];
int path[M+2][15];    //最优路径
int n,m;              //n个城市，m条路
int bestl;            //最短路径长度
int sx,S;
void Init()           //初始化
{
    memset(dp,INF,sizeof(dp));
    memset(path,0,sizeof(path));
    memset(g,INF,sizeof(g));
    bestl = INF;
}
void Traveling()//计算dp[i][j]
{
    dp[1][0]=0;
    S=1<<n;
    for(int i=0; i<S; i++)
    {
        for(int j=0; j < n; j++)
        {
            if(!(i&(1<<j))) continue;
            for(int k = 0; k < n; k++)
            {
                if(i&(1<<k)) continue;
                if(dp[i|(1<<k)][k] > dp[i][j] + g[j][k])
                {
                    dp[i|(1<<k)][k] = dp[i][j] + g[j][k];
                    path[i|(1<<k)][k] = j ;
                }
            }
        }
    }
    for(int i=0; i<n; i++)    //查找最短路径长度
    {
        if(bestl>dp[S-1][i]+g[i][0])
        {
            bestl=dp[S-1][i]+g[i][0] ;
            sx=i ;
        }
    }
}
void print(int S ,int value)    //打印路径
{
    if(!S)  return ;
    for(int i=0; i<n ; i++)
    {
        if(dp[S][i]==value)
        {
            print(S^(1<<i) ,value - g[i][path[S][i]]) ;
            cout<<i+1<<"--->";
            break ;
        }
    }
}
int main()
{
    int u, v, w;//u,v代表城市，w代表u和v城市之间路的长度
    cout << "请输入景点数 n(结点数):";
    cin >> n;
    cout << "请输入景点之间的连线数(边数):";
    cin >> m;
    Init();
    cout << "请依次输入两个景点u和v之间的距离w,格式:景点u 景点v 距离w";
    for(int i=0; i<m; i++)
    {
       cin >> u >> v >> w;
       g[u-1][v-1] = g[v-1][u-1] = w;
    }
    Traveling();
    cout<<"最短路径: ";
    print(S-1 ,bestl-g[sx][0]) ;
    cout << 1 << endl;
    cout<<"最短路径长度:" ;
    cout << bestl << endl;
    return 0;
}
