//program 5-5-2
#include<iostream>
#include<algorithm>
using namespace std ;
const int MX=10000+5 ;
int n;
struct node
{
    int id;
    int x,y;
}T[MX] ;
bool cmp(node a,node b)
{
    return min(b.x,a.y)>=min(b.y,a.x);//���ձ�������������
}
int main()
{
    cout<<"�������������ĸ��� n:";
    cin>>n;
    cout<<"����������ÿ����������ڵ�һ̨�����ϵļӹ�ʱ��x�͵ڶ�̨�����ϵļӹ�ʱ��y:";
    for(int i=0;i<n;i++)
    {
        cin>>T[i].x>>T[i].y;
        T[i].id=i+1;
    }
    sort(T,T+n,cmp);   //����
    int f1=0,f2=0;
    for(int i=0;i<n;i++)  //������ʱ��
    {
       f1+=T[i].x;
       f2=max(f1,f2)+T[i].y;
     }
    cout<<"���ŵĻ�������ӹ�˳��Ϊ:";
     for(int i=0;i<n;i++) //������żӹ�˳��
       cout<<T[i].id<<" ";
    cout<<endl;
    cout<<"���ŵĻ�������ӹ���ʱ��Ϊ:";
    cout<<f2<<endl;
    return 0 ;
}
