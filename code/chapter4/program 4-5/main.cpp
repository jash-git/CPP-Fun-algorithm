//program 4-5
#include<iostream>
#include<sstream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std  ;
const int M= 1000 + 5 ;
int n ;
int s[M][M] ;
double m[M][M],g[M][M];
void  Convexpolygontriangulation()
{
    for(int i = 1 ;i <= n ; i++)    // 初始化
    {
        m[i][i] = 0 ;
        s[i][i] = 0 ;
    }
    for(int d = 2 ;d <= n ; d++)         // 枚举点的个数
      for(int i = 1 ;i <= n - d + 1 ; i++)  // 枚举起始点
      {
          int j = i + d - 1 ;         // 终点
          m[i][j] = m[i+1][j] + g[i-1][i] + g[i][j] + g[i-1][j] ;
          s[i][j] = i ;
          for(int k = i + 1 ;k < j ; k++)     // 枚举中间点
          {
              double temp = m[i][k] + m[k+1][j] + g[i-1][k] + g[k][j] + g[i-1][j] ;
              if(m[i][j] > temp)
              {
                  m[i][j] = temp ;   // 更新最优值
                  s[i][j] = k ;      // 记录中间点
              }
          }
      }
}
void print(int i , int j)  // 输出所有的弦
{
    if(i == j)  return ;
    if(s[i][j]>i)
      cout<<"{v"<<i-1<<"v"<<s[i][j]<<"}"<<endl;
    if(j>s[i][j]+1)
      cout<<"{v"<<s[i][j]<<"v"<<j<<"}"<<endl;
    print(i ,s[i][j]);
    print(s[i][j]+1 ,j);
    //cout<<"{ v"<<i-1<<" , v"<<s[i][j]<<" , v"<<j<<" }"<<endl; //输出所有剖分后的三角形
}
int main()
{
    int i,j;
    cout << "请输入顶点的个数 n:";
    cin >> n;
    n-- ;
    cout << "请依次输入各顶点的连接权值:";
    for(int i = 0 ;i <= n ; i++)   // 输入各个顶点之间的距离
        for(int j = 0 ;j <= n ; j++)
            cin>>g[i][j] ;
    Convexpolygontriangulation();
    cout<<m[1][n]<<endl;
    // /*用于测试 输出m[][]和s[][]数组
    for (i = 1; i <= n; i++ )
    {
       for (j = 1; j <=2*(i-1); j++ )
          cout << "  " ;
       for (j = i; j <= n; j++ )
          cout << m[i][j]<<"   " ;
       cout << endl;
    }
    for (i = 1; i <= n; i++ )
    {
         for (j = 1; j <=2*(i-1); j++ )
           cout << "  " ;
         for (j = i; j <= n; j++ )
           cout << s[i][j]<<"   " ;
         cout << endl;
    }
    cout << endl;
    // /*/用于测试
    print(1 ,n); // 打印路径
    return 0 ;
}
