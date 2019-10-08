//program 4-7
#include <iostream>
#include<cstring>
using namespace std;
#define maxn 10005
#define M 105
int dp[maxn];//dp[j] ��ʾ��ǰ�ѷ�������Ϊj�Ĺ��ﳵ��õ�����ֵ
int w[M],v[M];//w[i] ��ʾ��i����Ʒ��������v[i] ��ʾ��i����Ʒ�ļ�ֵ
int x[M];  //x[i]��ʾ��i����Ʒ�Ƿ���빺�ﳵ
int i,j,n,W;//n��ʾn����Ʒ��W��ʾ���ﳵ������
void opt1(int n,int W)
{
     for(i=1;i<=n;i++)
        for(j=W;j>0;j--)
            if(j>=w[i])  //����Ʒ���������ڹ��ﳵ���������Ƚϴ���Ʒ���벻���Ƿ���ʹ�ù��ﳵ�ڵļ�ֵ���
              dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
}

void opt2(int n,int W)
{
     for(i=1;i<= n;i++)
        for(j=W;j>=w[i];j--)
            //����Ʒ���������ڹ��ﳵ���������Ƚϴ���Ʒ���벻���Ƿ���ʹ�ù��ﳵ�ڵļ�ֵ���
           dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
}

void opt3(int n,int W)
{
     int sum[n];//sum[i]��ʾ��1...i����Ʒ����֮��
     sum[0]=0;
     for(i=1;i<=n;i++)
        sum[i]=sum[i-1]+w[i];
     for(i=1;i<=n;i++)
     {
         int bound=max(w[i],W-(sum[n]-sum[i-1]));//w[i]��ʣ������ȡ���ֵ,sum[n]-sum[i-1]��ʾ��i...n����Ʒ����֮��
         for(j=W;j>=bound;j--)
            //����Ʒ���������ڹ��ﳵ���������Ƚϴ���Ʒ���벻���Ƿ���ʹ�ù��ﳵ�ڵļ�ֵ���
           dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
     }
}

int main()
{
    cout << "��������Ʒ�ĸ��� n:";
    cin >> n;
    cout << "�����빺�ﳵ������W:";
    cin >> W;
    cout << "����������ÿ����Ʒ������w�ͼ�ֵv,�ÿո�ֿ�:";
    for(i=1;i<=n;i++)
        cin>>w[i]>>v[i];
    for(j=1;j<=W;j++)//��ʼ����0��Ϊ0
        dp[j]=0;
    opt1(n,W);
    //opt2(n,W);
    //opt3(n,W);
    cout<<"װ�빺�ﳵ������ֵΪ:"<<dp[W]<<endl;

    //����dp[]������
    for(j=1;j<=W;j++)
        cout<<dp[j]<<"  ";
    cout<<endl;

   /* //���������Ž�,�޷��������Ž�
    j=W;
    for(i=n;i>0;i--)
    {
        while(dp[j]==dp[j-1])
            j--;
        if(dp[j]<=(dp[j-w[i]]+v[i]))
        {
            x[i]=1;
            j-=w[i];
        }
        else
            x[i]=0;
    }
    cout<<"װ�빺�ﳵ����ƷΪ:";
    for(i=1;i<=n;i++)
        if(x[i]==1)
           cout<<i<<"  ";
    */
    return 0;
}

