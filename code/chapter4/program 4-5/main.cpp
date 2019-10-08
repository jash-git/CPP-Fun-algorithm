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
    for(int i = 1 ;i <= n ; i++)    // ��ʼ��
    {
        m[i][i] = 0 ;
        s[i][i] = 0 ;
    }
    for(int d = 2 ;d <= n ; d++)         // ö�ٵ�ĸ���
      for(int i = 1 ;i <= n - d + 1 ; i++)  // ö����ʼ��
      {
          int j = i + d - 1 ;         // �յ�
          m[i][j] = m[i+1][j] + g[i-1][i] + g[i][j] + g[i-1][j] ;
          s[i][j] = i ;
          for(int k = i + 1 ;k < j ; k++)     // ö���м��
          {
              double temp = m[i][k] + m[k+1][j] + g[i-1][k] + g[k][j] + g[i-1][j] ;
              if(m[i][j] > temp)
              {
                  m[i][j] = temp ;   // ��������ֵ
                  s[i][j] = k ;      // ��¼�м��
              }
          }
      }
}
void print(int i , int j)  // ������е���
{
    if(i == j)  return ;
    if(s[i][j]>i)
      cout<<"{v"<<i-1<<"v"<<s[i][j]<<"}"<<endl;
    if(j>s[i][j]+1)
      cout<<"{v"<<s[i][j]<<"v"<<j<<"}"<<endl;
    print(i ,s[i][j]);
    print(s[i][j]+1 ,j);
    //cout<<"{ v"<<i-1<<" , v"<<s[i][j]<<" , v"<<j<<" }"<<endl; //��������ʷֺ��������
}
int main()
{
    int i,j;
    cout << "�����붥��ĸ��� n:";
    cin >> n;
    n-- ;
    cout << "��������������������Ȩֵ:";
    for(int i = 0 ;i <= n ; i++)   // �����������֮��ľ���
        for(int j = 0 ;j <= n ; j++)
            cin>>g[i][j] ;
    Convexpolygontriangulation();
    cout<<m[1][n]<<endl;
    // /*���ڲ��� ���m[][]��s[][]����
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
    // /*/���ڲ���
    print(1 ,n); // ��ӡ·��
    return 0 ;
}
