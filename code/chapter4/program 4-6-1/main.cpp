//program 4-6-1
#include <iostream>
#include <string>
using namespace std;

const int INF = 1 << 30;
const int N = 205;
int Min[N][N], Max[N][N],s[N][N];
int sum[N];
int a[N];
int min_Circular,max_Circular;

void get_Min(int n)
{
    for(int v=2; v<=n; v++) // ö�ٺϲ��Ķ�����ģ
    {
        for(int i=1; i<=n-v+1; i++) //ö����ʼ��i
        {
            int j = i + v-1; //ö���յ�j
            int tmp = sum[j]-sum[i-1];//��¼i...j֮���ʯ����֮��
            int i1=s[i][j-1]>i?s[i][j-1]:i;
            int j1=s[i+1][j]<j?s[i+1][j]:j;
            Min[i][j]=Min[i][i1]+Min[i1+1][j];
            s[i][j]=i1;
            for(int k=i1+1; k<=j1; k++) //ö���м�ָ���
                if(Min[i][k]+ Min[k+1][j]<Min[i][j])
                {
                    Min[i][j]=Min[i][k]+Min[k+1][j];
                    s[i][j]=k;
                }
            Min[i][j]+=tmp;
        }
    }
}

void get_Max(int n)
{
    for(int v=2; v<=n; v++) // ö�ٺϲ��Ķ�����ģ
    {
        for(int i=1; i<=n-v+1; i++) //ö����ʼ��i
        {
            int j = i + v-1; //ö���յ�j
            Max[i][j] = -1; //��ʼ��Ϊ-1
            int tmp = sum[j]-sum[i-1];//��¼i...j֮���ʯ����֮��
            if(Max[i+1][j]>Max[i][j-1])
               Max[i][j]=Max[i+1][j]+tmp;
            else
               Max[i][j]=Max[i][j-1]+tmp;
        }
    }
}

void straight(int a[],int n)
{
    for(int i=1;i<=n;i++)  // ��ʼ��
        Min[i][i]=0, Max[i][i]=0, s[i][i]=0;
    sum[0]=0;
    for(int i=1;i<=n;i++)
       sum[i]=sum[i-1]+a[i];
    get_Min(n);
    get_Max(n);
}
void Circular(int a[],int n)
{
    for(int i=1;i<=n-1;i++)
        a[n+i]=a[i];
    n=2*n-1;
    straight(a, n);
    n=(n+1)/2;
    min_Circular=Min[1][n];
    max_Circular=Max[1][n];
    for(int i=2;i<=n;i++)
    {
        if(Min[i][n+i-1]<min_Circular)
           min_Circular=Min[i][n+i-1];
        if(Max[i][n+i-1]>max_Circular)
           max_Circular=Max[i][n+i-1];
    }
}

int main()
{
    int n;
    cout << "������ʯ�ӵĶ��� n:";
    cin >> n;
    cout << "������������ѵ�ʯ����:";
    for(int i=1;i<=n;i++)
       cin>>a[i];
    straight(a, n);
    cout<<"·���淨(ֱ����)��С����Ϊ��"<<Min[1][n]<<endl;
    cout<<"·���淨(ֱ����)��󻨷�Ϊ��"<<Max[1][n]<<endl;
    Circular(a,n);
    cout<<"�ٳ��淨(Բ��)��С����Ϊ��"<<min_Circular<<endl;
    cout<<"�ٳ��淨(Բ��)��󻨷�Ϊ��"<<max_Circular<<endl;
    return 0;
}
