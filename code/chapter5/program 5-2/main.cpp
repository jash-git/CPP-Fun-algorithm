//program 5-2
#include <iostream>
#include <string.h>

using namespace std;

const int N = 100;
int a[N][N];  //ͼ���ڽӾ����ʾ
bool x[N];     //�Ƿ񽫵�i������������
bool bestx[N]; //��¼���Ž�
int bestn;    //��¼����ֵ
int cn;       //��ǰ�ѷ������еĽ������
int n,m;       //nΪͼ�н������mΪͼ�б���

bool Place(int t) //�ж��Ƿ���԰ѽ��t��������
{
    bool ok=true;
    for(int j=1;j<t; j++)  //���t��ǰt-1������б�ѡ�еĽ���Ƿ�����
    {
        if(x[j]&&a[t][j]==0) //x[j]��ʾj�Ǳ�ѡ�еĽ��,a[t][j]==0��ʾt��jû�б�����
        {
            ok = false;
            break;
        }
    }
    return ok;
}

void Backtrack(int t)
{
    if(t>n) //����Ҷ���
    {
        for(int i=1; i<=n; i++)
            bestx[i]=x[i];
        bestn=cn;
        return ;
    }
    if(Place(t)) //����Լ�����������������������ѽ��t��������
    {
        x[t]=1;
        cn++;
        Backtrack(t+1);
        cn--;
    }
    if(cn+n-t>bestn) //�����޽�����������������
    {
        x[t] = 0;
        Backtrack(t + 1);
    }
}

int main() {

    int i,u, v;
    cout << "�����벿������� n(�����):";
    cin >> n;
    cout << "�����������˵��Ѻù�ϵ��(����):";
    cin >> m;
    memset(a,0,sizeof(a));//�ڽӾ�����������ݳ�ʼ��Ϊ0,��Ҫ����#include <string.h>
    cout << "�������������Ѻù�ϵ��������(�б��������������u��v),�ÿո�ֿ�:";
    for(i=1;i<=m;i++)
    {
        cin>>u>>v;
        a[u][v]=a[v][u]=1;
    }
    bestn=0;
    cn=0;
    Backtrack(1);
    cout<<"���������ӵ��������Ϊ��"<<bestn<<endl;
    cout<<"���������ӵĳ�ԱΪ��";
    for(int i=1;i<=n;i++)
        if(bestx[i])
            cout<<i<<"  ";
    return 0;
}
