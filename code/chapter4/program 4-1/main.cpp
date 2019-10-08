//program 4-1
#include <iostream>
#include<cstring>
using namespace std;
const int N=1002;
int c[N][N],b[N][N];
char s1[N],s2[N];
int len1,len2;

void LCSL()
{
    int i,j;
    for(i = 1;i <= len1;i++)//����s1���в�ͬ��������
      for(j = 1;j <= len2;j++)//����s2���в�ͬ��������
      {
        if(s1[i-1]==s2[j-1])
        {
            c[i][j] = c[i-1][j-1]+1;//�����ǰ�ַ���ͬ���򹫹������еĳ���Ϊ���ַ�ǰ�����������+1
            b[i][j] = 1;
        }
        else
        {
             if(c[i][j-1]>=c[i-1][j])
            {
                c[i][j] = c[i][j-1];
                b[i][j] = 2;
            }
            else
            {
                c[i][j] = c[i-1][j];
                b[i][j] = 3;
            }
        }
     }
}

void print(int i, int j)//���ݼ�¼��������Ϣ��������������У���b[i][j]��ʼ���ƣ�
{
    if(i==0 || j==0) return;
    if(b[i][j]==1)
    {
        print(i-1,j-1);
        cout<<s1[i-1];
    }
    else if(b[i][j]==2)
            print(i,j-1);
         else
            print(i-1,j);
}

int main()
{
    int i,j;
    cout << "�����ַ���s1:"<<endl;
    cin >> s1;
    cout << "�����ַ���s2:"<<endl;
    cin >> s2;
    len1 = strlen(s1);//���������ַ����ĳ���
    len2 = strlen(s2);
    for(i = 0;i <= len1;i++)
    {
        c[i][0]=0;//��ʼ����һ��Ϊ0
    }
    for(j = 0;j<= len2;j++)
    {
        c[0][j]=0;//��ʼ����һ��Ϊ0
    }
    LCSL();
    cout << "s1��s2������������г�����:"<<c[len1][len2]<<endl;
    cout << "s1��s2���������������:";
    print(len1,len2);
    cout<<endl;
    // /*���ڲ���
    cout<<"c[i][j]���飺"<<endl;
    for(i = 0;i <= len1;i++)
    {
        for(j = 0;j <= len2;j++)
          cout <<"  "<<c[i][j];
        cout<<endl;
    }
    cout<<"b[i][j]���飺"<<endl;
    for(i = 0;i <= len1;i++)
    {
        for(j = 0;j <= len2;j++)
          cout <<"  "<<b[i][j];
        cout<<endl;
    }
    // */���ڲ���
    return 0;
}
