//program 5-3
#include <iostream>
#include <string.h>
#define MX 50
using namespace std;

int x[MX];         //�����
int map[MX][MX];  //ͼ���ڽӾ���
int sum=0;   //��¼��ĸ���
int n,m,edge;  //�ڵ�������ɫ��

//�����ڽӾ���
void CreatMap()
{
    int u,v;
    cout << "���������:";
    cin >> edge;
    memset(map,0,sizeof(map));//�ڽӾ�����������ݳ�ʼ��Ϊ0,meset��Ҫ����#include <string.h>
    cout << "�����������б��������������u��v,�ÿո�ֿ�:";
    for(int i=1;i<=edge;i++)
    {
        cin>>u>>v;
        map[u][v]=map[v][u]=1;
    }
}
//Լ������
bool OK(int t)
{
    for(int j=1;j<t;j++)
    {
        if(map[t][j])      //���t��j�ڽ�
        {
            if(x[j]==x[t]) //�ж�t��j����ɫ���Ƿ���ͬ
                return false;
        }
    }
    return true;
}
//��������
void Backtrack(int t)
{

    if(t>n) //����Ҷ��,�ҵ�һ����ɫ����
    {
        sum++;
        cout<<"��"<<sum<<"�ַ�����";
        for(int i=1;i<=n;i++) //�������ɫ����
            cout<<x[i]<<" ";
        cout<<endl;
    }
    else{
        for(int i=1;i<=m;i++) //ÿ����㳢��m����ɫ
        {
            x[t]=i;
            if(OK(t))
                Backtrack(t+1);
        }
    }
}
int main()
{
    cout<<"����ڵ����� ";
    cin>>n;
    cout<<"������ɫ���� ";
    cin>>m;
    cout<<"��������ͼ���ڽӾ���"<<endl;
    CreatMap();
    Backtrack(1);
}
