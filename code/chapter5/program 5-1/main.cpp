#include <iostream>
#include <string>
#include <algorithm>
#define M 105
using namespace std;

int i,j,n,W;//n��ʾn����Ʒ��W��ʾ���ﳵ������
double w[M],v[M];//w[i] ��ʾ��i����Ʒ��������v[i] ��ʾ��i����Ʒ�ļ�ֵ
bool x[M];  //x[i]��ʾ��i����Ʒ�Ƿ���빺�ﳵ
double cw;                   //��ǰ����
double cp;                   //��ǰ��ֵ
double bestp;                //��ǰ���ż�ֵ
bool bestx[M];               //��ǰ���Ž�

double Bound(int i)//�����Ͻ磨����װ����Ʒ��ֵ+ʣ����Ʒ���ܼ�ֵ��
{
    //ʣ����ƷΪ��i~n����Ʒ
    int rp=0;
    while(i<=n)//���μ���ʣ����Ʒ�ļ�ֵ
    {
        rp+=v[i];
        i++;
    }
    return cp+rp;
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
    if(cw+w[t]<=W)//�������Լ������������������
    {
        x[t]=1;
        cw+=w[t];
        cp+=v[t];
        Backtrack(t+1);
        cw-=w[t];
        cp-=v[t];
    }
    if(Bound(t+1)>bestp)//��������޽�����������������
    {
        x[t]=0;
        Backtrack(t+1);
    }
}

void Knapsack(double W, int n)
{
    //��ʼ��
    cw=0;//��ʼ����ǰ���빺�ﳵ����Ʒ����Ϊ0
    cp=0; //��ʼ����ǰ���빺�ﳵ����Ʒ��ֵΪ0
    bestp=0; //��ʼ����ǰ����ֵΪ0
    double sumw=0.0; //����ͳ��������Ʒ��������
    double sumv=0.0; //����ͳ��������Ʒ���ܼ�ֵ
    for(i=1; i<=n; i++)
    {
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
    Backtrack(1);
    cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
    cout<<"���빺�ﳵ����Ʒ���Ϊ: ";
    for(i=1;i<=n;i++) //������Ž�
    {
        if(bestx[i]==1)
        cout<<i<<" ";
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
