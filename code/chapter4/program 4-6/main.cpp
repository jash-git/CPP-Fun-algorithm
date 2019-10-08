//program 4-6
#include <iostream>
#include <string>
using namespace std;

const int INF = 1 << 30;
const int N = 205;
int Min[N][N], Max[N][N];
int sum[N];
int a[N];
int min_Circular,max_Circular;

void straight(int a[],int n)
{
    for(int i=1;i<=n;i++)  // ��ʼ��
        Min[i][i]=0, Max[i][i]=0;
    sum[0]=0;
    for(int i=1;i<=n;i++)
       sum[i]=sum[i-1]+a[i];
    for(int v=2; v<=n; v++) // ö�ٺϲ��Ķ�����ģ
    {
        for(int i=1; i<=n-v+1; i++) //ö����ʼ��i
        {
            int j = i + v-1; //ö���յ�j
            Min[i][j] = INF; //��ʼ��Ϊ���ֵ
            Max[i][j] = -1; //��ʼ��Ϊ-1
            int tmp = sum[j]-sum[i-1];//��¼i...j֮���ʯ����֮��
            for(int k=i; k<j; k++) {   //ö���м�ָ���
                Min[i][j] = min(Min[i][j], Min[i][k] + Min[k+1][j] + tmp);
                Max[i][j] = max(Max[i][j], Max[i][k] + Max[k+1][j] + tmp);
            }
        }
    }
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
