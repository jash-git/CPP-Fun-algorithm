//program 6-2-1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int INF=1e7;  //����������ֵΪ107
const int N=100;
double g[N][N];  //�����ͼ�ڽӾ���
double minout[N]; //��¼ÿ����������ٳ���
double minsum;    //��¼���о�������ٳ���֮��
int bestx[N];   //��¼��ǰ����·��
double bestl;     //��ǰ����·������
int n,m;       //�������n,����m
struct Node//������,��¼��ǰ���Ľ���Ϣ
{
    double cl; //��ǰ���߹���·������
    double rl; //ʣ��·�����ȵ��½�
    double zl; //��ǰ·�����ȵ��½�zl=rl+cl
    int id; //�������
    int x[N];//��¼��ǰ������
    Node() {}
    Node(double _cl,double _rl,double _zl,int _id)
    {
        cl = _cl;
        rl = _rl;
        zl = _zl;
        id = _id;
    }
};

//������е����ȼ��� ��zlΪ���ȼ���zlֵԽС��Խ����
bool operator <(const Node &a, const Node &b)
{
    return a.zl>b.zl;
}

bool Bound()//�����½磨��ÿ��������С����Ȩֵ֮�ͣ�
{
    for(int i=1;i<=n;i++)
    {
       double minl=INF;//��ʱ������������Сֵ
       for(int j=1;j<=n;j++)//��ÿ���������С����
         if(g[i][j]!=INF&&g[i][j]<minl)
            minl=g[i][j];
       if(minl==INF)
          return false;//��ʾ�޻�·
       minout[i]=minl;//��¼ÿ����������ٳ���
       cout<<"��"<<i<<"����������ٳ���:"<<minout[i]<<" "<<endl;
       minsum+=minl;//��¼���о�������ٳ���֮��
    }
    cout<<"ÿ����������ٳ���֮��:""minsum= "<<minsum<<endl;
    return true;
}

//Travelingbfsopt Ϊ�Ż������ȶ���ʽ��֧�޽編
double Travelingbfsopt()
{
    if(!Bound())
        return -1;//��ʾ�޻�·
    Node livenode,newnode;//���嵱ǰ��չ���livenode,�����½��newnode
    priority_queue<Node> q; //����һ�����ȶ���,���ȼ�Ϊ��ǰ·�����ȵ��½�zl=rl+cl,zlֵԽС��Խ����
    newnode=Node(0,minsum,minsum,2);//�������ڵ�
    for(int i=1;i<=n;i++)
    {
       newnode.x[i]=i;//��ʱ�������Ľ�����
    }
    q.push(newnode);//�����������ȶ���
    while(!q.empty())
    {
        livenode=q.top();//ȡ����ͷԪ����Ϊ��ǰ��չ���livenode
        q.pop(); //��ͷԪ�س���
        cout<<"��ǰ����idֵ:"<<livenode.id<<"��ǰ����zlֵ:"<<livenode.zl<<endl;
        cout<<"��ǰ���Ľ�����:";
        for(int i=1; i<=n; i++)
        {
            cout<<livenode.x[i];
        }
        cout<<endl;
        int t=livenode.id;//��ǰ����ľ������
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
                double rl=livenode.rl-minout[livenode.x[j]];
                double zl=cl+rl;
                if(zl<bestl)//�п��ܵõ����̵�·��
                {
                    newnode=Node(cl,rl,zl,t+1);
                    for(int i=1;i<=n;i++)
                    {
                      newnode.x[i]=livenode.x[i];//������ǰ�Ľ�����
                    }
                    swap(newnode.x[t], newnode.x[j]);//��������Ԫ�ص�ֵ
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
    minsum=0;
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
    for(int i=1;i<=n; i++)
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
    Travelingbfsopt();
    print();
    return 0;
}
