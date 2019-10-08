//program 6-2
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int INF=1e7;  //����������ֵΪ10^7
const int N=100;
double g[N][N];  //�����ͼ�ڽӾ���
int bestx[N];   //��¼��ǰ����·��
double bestl;     //��ǰ����·������
int n,m;       //�������n,����m
struct Node//������,��¼��ǰ���Ľ���Ϣ
{
    double cl; //��ǰ���߹���·������
    int id; //�������
    int x[N];//��¼��ǰ·��
    Node() {}
    Node(double _cl,int _id)
    {
        cl = _cl;
        id = _id;
    }
};

//������е����ȼ��� ��clΪ���ȼ���clֵԽС��Խ����
bool operator <(const Node &a, const Node &b)
{
    return a.cl>b.cl;
}

//Travelingbfs Ϊ���ȶ���ʽ��֧�޽編����
double Travelingbfs()
{
    int t; //��ǰ����ľ������t
    Node livenode,newnode;//���嵱ǰ��չ���livenode,�����½��newnode
    priority_queue<Node> q; //����һ�����ȶ���,���ȼ�Ϊ�Ѿ��߹���·������cl,clֵԽС��Խ����
    newnode=Node(0,2);//�������ڵ�
    for(int i=1;i<=n;i++)
    {
       newnode.x[i]=i;//��ʱ�������Ľ�����
    }
    q.push(newnode);//�����������ȶ���
    cout<<"�����ȼ�����˳��"<<endl;//���ڵ���
    while(!q.empty())
    {
        livenode=q.top();//ȡ����ͷԪ����Ϊ��ǰ��չ���livenode
        q.pop(); //��ͷԪ�س���
        //���ڵ���
        cout<<"��ǰ����idֵ:"<<livenode.id<<"��ǰ����clֵ:"<<livenode.cl<<endl;
        cout<<"��ǰ���Ľ�����:";
        for(int i=1; i<=n; i++)
        {
            cout<<livenode.x[i];
        }
        cout<<endl;
        t=livenode.id;//��ǰ����ľ������
        // �ѵ�������2�����ʱ�������ʱ����Ҫ��������
        if(t==n)  //�����ж��Ƿ�������Ž⣬
            //���統ǰ�ҵ�һ��·��(1243)������4�Ž��ʱ�������ж�g[4][3]��g[3][1]�Ƿ��б�������
            //����б����жϵ�ǰ·������cl+g[4][3]+g[3][1]<bestl���������������ֵ�����Ž�
        {
           //˵���ҵ���һ�����õ�·������¼�����Ϣ
           if(g[livenode.x[n-1]][livenode.x[n]]!=INF&&g[livenode.x[n]][1]!=INF)
             if(livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1]<bestl)
             {
                bestl=livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1];
                cout<<endl;
                cout<<"��ǰ���ŵĽ�����:";
                for(int i=1;i<=n;i++)
                {
                  bestx[i]=livenode.x[i];
                  cout<<bestx[i];
                }
                cout<<endl;
                cout<<endl;
              }
            continue;
        }
        //�жϵ�ǰ����Ƿ������޽���������������㲻����չ
       if(livenode.cl>=bestl)
          continue;
        //��չ
        //û�е���Ҷ�ӽ��
        for(int j=t; j<=n; j++)//������չ�������з�֧
        {
            if(g[livenode.x[t-1]][livenode.x[j]]!=INF)//���x[t-1]������x[j]�����б�����
            {
                double cl=livenode.cl+g[livenode.x[t-1]][livenode.x[j]];
                if(cl<bestl)//�п��ܵõ����̵�·��
                {
                    newnode=Node(cl,t+1);
                    for(int i=1;i<=n;i++)
                    {
                      newnode.x[i]=livenode.x[i];//������ǰ�Ľ�����
                    }
                    swap(newnode.x[t], newnode.x[j]);//����x[t]��x[j]����Ԫ�ص�ֵ
                    q.push(newnode);//�½�����
                }
            }
        }
    }
    return bestl;//��������ֵ��
}

void init()//��ʼ��
{
    bestl=INF;
    for(int i=0; i<=n; i++)
    {
        bestx[i]=0;
    }
    for(int i=1;i<=n;i++)
       for(int j=i;j<=n;j++)
          g[i][j]=g[j][i]=INF;//��ʾ·�����ɴ�
}
void print()//��ӡ·��
{
    cout<<endl;
    cout<<"���·��:  ";
    for(int i=1;i<=n;i++)
        cout<<bestx[i]<<"--->";
    cout<<"1"<<endl;
    cout<<"���·�����ȣ�"<<bestl;
}

int main()
{
    int u, v, w;//u,v������У�w����u��v����֮��·�ĳ���
    cout << "�����뾰���� n(�����):";
    cin >> n;
    init();
    cout << "�����뾰��֮���������(����):";
    cin >> m;
    cout << "������������������u��v֮��ľ���w,��ʽ:����u ����v ����w:"<<endl;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        g[u][v]=g[v][u]=w;
    }
    Travelingbfs();
    print();
    return 0;
}
