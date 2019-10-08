//program 4-4
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int msize = 100;
int p[msize];
int m[msize][msize];
int s[msize][msize];
int n;

void matrixchain()
{
    int i,j,r,k;
    memset(m,0,sizeof(m));
    memset(s,0,sizeof(s));
    for(r = 2; r <= n; r++)         //不同规模的子问题
    {
        for(i = 1; i <= n-r+1; i++)
        {
           j = i + r - 1;
           m[i][j] = m[i+1][j] + p[i-1] * p[i] * p[j];  //决策为k=i的乘法次数
           s[i][j] = i;                     //子问题的最优策略是i;
           for(k = i+1; k < j; k++) //对从i到j的所有决策，求最优值，记录最优策略
            {
                int t = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if(t < m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}
void print(int i,int j)
{
    if( i == j )
    {
       cout <<"A[" << i << "]";
       return ;
    }
    cout << "(";
    print(i,s[i][j]);
    print(s[i][j]+1,j);
    cout << ")";
}
int main()
{
    cout << "请输入矩阵的个数 n:";
    cin >> n;
    int i ,j;
    cout << "请依次输入每个矩阵的行数和最后一个矩阵的列数:";
    for (i = 0; i <= n; i++ )
        cin >> p[i];
    matrixchain();
    print(1,n);
    cout << endl;
    /*用于测试
    for (i = 1; i <= n; i++ )
        {
          for (j = i; j <= n; j++ )
            cout << m[i][j]<<"  " ;
          cout << endl;
        }
     for (i = 1; i <= n; i++ )
        {
          for (j = i; j <= n; j++ )
            cout << s[i][j]<<"  " ;
          cout << endl;
        }
    cout << endl;
    */
    cout << "最小计算量的值为 " << m[1][n] << endl;
}
