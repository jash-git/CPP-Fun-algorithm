//program 5-1-1
#include <iostream>
#include <string>
#include <algorithm>
#include<cmath>   //�����ֵ������Ҫ�����ͷ�ļ�
#define M 105
using namespace std;

int i,j,n,W;//n��ʾn����Ʒ��W��ʾ���ﳵ������
double w[M],v[M];//w[i] ��ʾ��i����Ʒ��������v[i] ��ʾ��i����Ʒ�ļ�ֵ
bool x[M];  //x[i]��ʾ��i����Ʒ�Ƿ���빺�ﳵ
double cw;                   //��ǰ����
double cp;                   //��ǰ��ֵ
double bestp;                //��ǰ���ż�ֵ
bool bestx[M];               //��ǰ���Ž�

double Bound(int i)//�����Ͻ磨����ʣ����Ʒװ��ʣ��ı�������ʱ���ܻ�õ�����ֵ��
{
    //i��ʾʣ����ƷΪ��i~n����Ʒ
    double cleft=W-cw;//ʣ������
    double brp=0.0;
    while(i<=n && w[i]<cleft)
    {
        cleft-=w[i];
        brp+=v[i];
        i++;
    }
    if(i<=n)//װ������
    {
        brp+=v[i]/w[i]*cleft;
    }
    return cp+brp;
}


void Backtrack(int t)//���������ռ�����t��ʾ��ǰ��չ����ڵ�t��
{
    if(t>n)//�Ѿ�����Ҷ�ӽ��
    {
        for(j=1;j<=n;j++)
        {
            bestx[j]=x[j];
        }
        bestp=cp;//���浱ǰ���Ž�
        return ;
    }
    if(cw+w[t]<=W)//���������������������������
    {
        x[t]=1;
        cw+=w[t];
        cp+=v[t];
        Backtrack(t+1);
        cw-=w[t];
        cp-=v[t];
    }
    if(Bound(t+1)>bestp)//���������������������������
    {
        x[t]=0;
        Backtrack(t+1);
    }
}

struct Object//������Ʒ�ṹ�壬������Ʒ��ź͵�λ������ֵ
{
    int id; //��Ʒ���
    double d;//��λ������ֵ
};

bool cmp(Object a1,Object a2)//������Ʒ��λ������ֵ�ɴ�С����
{
    return a1.d>a2.d;
}

void Knapsack(int W, int n)
{
    //��ʼ��
    double sumw=0; //����ͳ��������Ʒ��������
    double sumv=0; //����ͳ��������Ʒ���ܼ�ֵ
    Object Q[n];   //��Ʒ�ṹ������,���ڰ���λ������ֵ(��ֵ/������)����
    double a[n+1],b[n+1];//��������,���ڰ������������ͼ�ֵ��ֵ��ԭ����������ֵ����
    for(i=1;i<=n;i++)
    {
        Q[i-1].id=i;
        Q[i-1].d=1.0*v[i]/w[i];
       // cout<<"��Ʒ��ż���λ������ֵΪ: "<<Q[i-1].id<<"   "<<Q[i-1].d<<endl;
        sumv+=v[i];
        sumw+=w[i];
    }
    if(sumw<=W)
    {
        bestp=sumv;
        cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
        cout<<"���е���Ʒ�����빺�ﳵ.";
        return;
    }
    sort(Q,Q+n,cmp);
    for(i=1;i<=n;i++)
    {
        a[i]=w[Q[i-1].id];//�����������ݴ��ݹ�ȥ
        b[i]=v[Q[i-1].id];
    }
    for(i=1;i<=n;i++)
    {
        w[i]=a[i];//�����������ݴ��ݹ�ȥ
        v[i]=b[i];
        //cout<<"�����������ͼ�ֵΪ: "<<w[i]<<"  "<<v[i]<<endl;
    }
    Backtrack(1);
    cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
    cout<<"���빺�ﳵ����Ʒ���Ϊ: ";
    for(i=1; i<=n; i++)
    {
        if(bestx[i]==1)
          cout<<Q[i-1].id<<" ";
    }
    cout<<endl;
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
    Knapsack(W,n);
    return 0;
}
