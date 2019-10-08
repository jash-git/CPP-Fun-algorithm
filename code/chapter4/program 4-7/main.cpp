//program 4-7
#include <iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 10005
#define M 105
int c[M][maxn];//c[i][j] 表示前i个物品放入容量为j购物车获得的最大价值
int w[M],v[M];//w[i] 表示第i个物品的重量，v[i] 表示第i个物品的价值
int x[M];  //x[i]表示第i个物品是否放入购物车
int main(){
    int i,j,n,W;//n表示n个物品，W表示购物车的容量
    cout << "请输入物品的个数 n:";
    cin >> n;
    cout << "请输入购物车的容量W:";
    cin >> W;
    cout << "请依次输入每个物品的重量w和价值v，用空格分开:";
    for(i=1;i<=n;i++)
        cin>>w[i]>>v[i];
    for(i=1;i<=n;i++)//初始化第0列为0
        c[i][0]=0;
    for(j=1;j<=W;j++)//初始化第0行为0
        c[0][j]=0;
    for(i=1;i<= n;i++)//计算c[i][j]
        for(j=1;j<=W;j++)
            if(j<w[i])  //当物品的重量大于购物车的容量，则不放此物品
                c[i][j] = c[i-1][j];
            else    //否则比较此物品放与不放是否能使得购物车内的价值最大
                c[i][j] = max(c[i-1][j],c[i-1][j-w[i]] + v[i]);
    cout<<"装入购物车的最大价值为:"<<c[n][W]<<endl;

    //用于测试
    for (i=1; i<=n; i++ )
    {
        for (j=1; j<=W; j++ )
          cout << c[i][j]<<"\t" ;
        cout << endl;
    }
    cout << endl;

    //逆向构造最优解
    j=W;
    for(i=n;i>0;i--)
        if(c[i][j]>c[i-1][j])
        {
            x[i]=1;
            j-=w[i];
        }
        else
            x[i]=0;
    cout<<"装入购物车的物品序号为:";
    for(i=1;i<=n;i++)
        if(x[i]==1)
           cout<<i<<"  ";
    return 0;
}

