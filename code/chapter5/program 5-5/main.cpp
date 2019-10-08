//program 5-5
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f;
const int MX=10000+5;
int n,bestf,f1,f2;//f1�ڵ�һ̨�����ϼӹ������ʱ��,f2�ڵڶ�̨�����ϼӹ������ʱ��
int x[MX],bestx[MX];
struct node
{
    int x,y;//��������ڵ�һ̨�����ϵļӹ�ʱ��x�͵ڶ�̨�����ϵļӹ�ʱ��y
}T[MX];
void Backtrack(int t)
{
    if(t>n)
    {
        for(int i=1;i<=n;i++) //��¼��������
           bestx[i]=x[i] ;
        bestf=f2;   // ��������ֵ
        return ;
    }
    for(int i=t;i<=n;i++)  // ö��
    {
        f1+=T[x[i]].x;
        int temp=f2;
        f2=max(f1,f2)+T[x[i]].y;
        if(f2<bestf)  //�޽�����
        {
            swap(x[t] ,x[i]);  // ����
            Backtrack(t+1);          // ��������
            swap(x[t],x[i]);  // ��λ��������
        }
        f1-=T[x[i]].x ;
        f2=temp ;
    }
}
int main()
{
    cout<<"�������������ĸ��� n:";
    cin>>n;
    cout<<"����������ÿ����������ڵ�һ̨�����ϵļӹ�ʱ��x�͵ڶ�̨�����ϵļӹ�ʱ��y:";
    for(int i=1;i<=n;i++)
    {
        cin>>T[i].x>>T[i].y;
        x[i]=i;
    }
    bestf=INF;    // ��ʼ��
    f1=f2=0;
    memset(bestx,0,sizeof(bestx));
    Backtrack(1);         // ����������
    cout<<"���ŵĻ�������ӹ�˳��Ϊ:";
    for(int i=1;i<=n;i++) //������żӹ�˳��
       cout<<bestx[i]<<" ";
    cout<<endl;
    cout<<"���ŵĻ�������ӹ���ʱ��Ϊ:";
    cout<<bestf<<endl;
    return 0 ;
}
