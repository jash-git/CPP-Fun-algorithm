//program 4-3
#include<iostream>
using namespace std;
const int ms = 1000;
int r[ms][ms],m[ms][ms],s[ms][ms];    //i��jվ�����
int n;            //����n��վ��
void rent()
{
    int i,j,k,d;
    for(d=3;d<=n;d++) //�������ΪС��ģΪd
    {
        for(i=1;i<=n-d+1;i++)
            {
                j=i+d-1;
                for(k=i+1;k<j;k++)  //��¼ÿһ��С��ģ�ڵ����Ž�
                {
                    int temp;
                    temp=m[i][k]+m[k][j];
                    if(temp<m[i][j])
                        {
                           m[i][j]=temp;
                           s[i][j]=k;
                        }
                }
            }
    }
}
void print(int i,int j)
{
    if(s[i][j]==0 )
    {
       cout << "--"<<j;
       return ;
    }
    print(i,s[i][j]);
    print(s[i][j],j);
}
int main()
{
    int i,j;
    cout << "������վ��ĸ��� n:";
    cin >> n;
    cout << "�����������վ��֮������:";
    for(i=1;i<=n;i++)
        for(j=i+1;j<=n;++j)
        {
            cin>>r[i][j];
            m[i][j]=r[i][j];
        }
    rent();
    cout << "���ѵ��������Ϊ:" <<m[1][n] << endl;
    cout <<"������𾭹���վ�㣺"<<1;
    print(1,n);
    // /*���ڲ��� ���m[][]��s[][]����
    cout << endl;
    for (i = 1; i <= n; i++ )
    {
       for (j = 1; j <=2*(i-1); j++ )
          cout << "  " ;
       for (j=i; j<=n;j++ )
          cout << m[i][j]<<"   " ;
       cout << endl;
    }
    for (i=1; i<=n;i++ )
    {
         for (j =1; j <=2*(i-1);j++ )
           cout << "  " ;
         for (j=i; j<=n; j++ )
           cout << s[i][j]<<"   " ;
         cout << endl;
    }
    cout << endl;
    // /*/���ڲ���
    return 0;
}
