//program 6-1-1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int N = 10;
bool bestx[N]; //��¼���Ž�
int w[N],v[N];//��������,���ڴ洢�����������ͼ�ֵ

struct Node//������,��¼��ǰ���Ľ���Ϣ
{
    int cp; //cpװ�빺�ﳵ����Ʒ��ֵ
    double up; //��ֵ�Ͻ�
    int rw; //����ʣ������
    int id; //��Ʒ��
    bool x[N];
    Node() {}
    Node(int _cp, double _up, int _rw, int _id)
    {
        cp = _cp;
        up = _up;
        rw = _rw;
        id = _id;
        memset(x, 0, sizeof(x));
    }
};

struct Goods //������Ʒ�ṹ�壬������Ʒ��������ֵ
{
    int weight;
    int value;
}goods[N];

struct Object//���帨����Ʒ�ṹ�壬������Ʒ��ź͵�λ������ֵ,���ڰ���λ������ֵ(��ֵ/������)����
{
    int id; //��Ʒ���
    double d;//��λ������ֵ
}S[N];

//�����������ȼ�������Ʒ��λ������ֵ�ɴ�С����
bool cmp(Object a1,Object a2)
{
    return a1.d>a2.d;
}

//������е����ȼ��� ��upΪ���ȣ�upֵԽ��Ҳ��Խ����
bool operator <(const Node &a, const Node &b)
{
    return a.up<b.up;
}

int bestp,W,n,sumw,sumv;
/*
  bestv ������¼���Ž⡣
  WΪ���������������
  nΪ��Ʒ�ĸ�����
  sumw Ϊ������Ʒ����������
  sumv Ϊ������Ʒ���ܼ�ֵ��
*/

double Bound(Node tnode)
{
    double maxvalue=tnode.cp;//��װ�빺�ﳵ��Ʒ��ֵ
    int t=tnode.id;//��������
    //cout<<"t="<<t<<endl;
    double left=tnode.rw;//ʣ������
    while(t<=n&&w[t]<=left)
    {
        maxvalue+=v[t];
       // cout<<"malvalue="<<maxvalue<<endl;
        left-=w[t];
        t++;
    }
    if(t<=n)
        maxvalue+=double(v[t])/w[t]*left;
    //cout<<"malvalue="<<maxvalue<<endl;
    return maxvalue;
}
//priorbfs Ϊ���ȶ���ʽ��֧�޽編������
int priorbfs()
{
     int t,tcp,trw;
     double tup; //��ǰ�������Ʒ���t����ǰװ�빺�ﳵ��Ʒ��ֵtcp��
    //��ǰװ�빺�ﳵ��Ʒ��ֵ�Ͻ�tup����ǰʣ������trw
    priority_queue<Node> q; //����һ�����ȶ���,���ȼ�Ϊװ�빺�ﳵ����Ʒ��ֵ�Ͻ�up
    q.push(Node(0, sumv, W, 1));//��ʼ��,�����������ȶ���
    while(!q.empty())
    {
        Node livenode, lchild, rchild;//������������ͱ���
        livenode=q.top();//ȡ����ͷԪ����Ϊ��ǰ��չ���livenode
        q.pop(); //��ͷԪ�س���
        cout<<"��ǰ����idֵ:"<<livenode.id<<"��ǰ����upֵ:"<<livenode.up<<endl;
        cout<<"��ǰ���Ľ�����:";
        for(int i=1; i<=n; i++)
        {
            cout<<livenode.x[i];
        }
        cout<<endl;
        t=livenode.id;//��ǰ�������Ʒ���
        // �ѵ����һ����Ʒ��ʱ����Ҫ����������
        // �����ǰ�Ĺ��ﳵû��ʣ������(�Ѿ�װ��)�ˣ�������չ��
        if(t>n||livenode.rw==0)
        {
            if(livenode.cp>=bestp)//�������Ž������ֵ
            {
              cout<<"�������Ž�����:";
              for(int i=1; i<=n; i++)
              {
                bestx[i]=livenode.x[i];
                cout<<bestx[i];
              }
              cout<<endl;
              bestp=livenode.cp;
            }
            continue;
        }
        //�жϵ�ǰ����Ƿ������޽���������������㲻����չ
        if(livenode.up<bestp)
          continue;
        //��չ����
        tcp=livenode.cp; //��ǰ���ﳵ�еļ�ֵ
        trw=livenode.rw; //���ﳵʣ������
        if(trw>=w[t]) //����Լ�����������Է��빺�ﳵ
        {
            lchild.cp=tcp+v[t];
            lchild.rw=trw-w[t];
            lchild.id=t+1;
            tup=Bound(lchild); //���������Ͻ�
            lchild=Node(lchild.cp,tup,lchild.rw,lchild.id);//���ݲ���
            for(int i=1;i<=n;i++)
            {
              lchild.x[i]=livenode.x[i];//������ǰ�Ľ�����
            }
            lchild.x[t]=true;
            if(lchild.cp>bestp)//������ֵ��Ÿ���
               bestp=lchild.cp;
            q.push(lchild);//�������
        }
        //��չ�Һ���
         rchild.cp=tcp;
         rchild.rw=trw;
         rchild.id=t+1;
         tup=Bound(rchild); //�Һ��Ӽ����Ͻ�
         if(tup>=bestp)//�����޽������������빺�ﳵ
         {
            rchild=Node(tcp,tup,trw,t+1);//���ݲ���
            for(int i=1;i<=n;i++)
            {
              rchild.x[i]=livenode.x[i];//������ǰ�Ľ�����
            }
            rchild.x[t]=false;
            q.push(rchild);//�Һ������
          }
    }
    return bestp;//��������ֵ��
}

int main()
{
    bestp=0; //bestv ������¼���Ž�
    sumw=0; //sumwΪ������Ʒ����������
    sumv=0;   //sum Ϊ������Ʒ���ܼ�ֵ
    cout << "��������Ʒ�ĸ��� n:";
    cin >> n;
    cout << "�����빺�ﳵ������W:";
    cin >> W;
    cout << "����������ÿ����Ʒ������w�ͼ�ֵv,�ÿո�ֿ�:";
    for(int i=1; i<=n; i++)
    {
        cin >> goods[i].weight >> goods[i].value;//����� i ����Ʒ������ͼ�ֵ��
        sumw+= goods[i].weight;
        sumv+= goods[i].value;
        S[i-1].id=i;
        S[i-1].d=1.0*goods[i].value/goods[i].weight;
    }
    if(sumw<=W)
    {
        bestp=sumv;
        cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
        cout<<"���е���Ʒ�����빺�ﳵ��";
        return 0;
    }
    sort(S, S+n, cmp);//����ֵ�����ȷǵ�������
    cout<<"��������Ʒ�����ͼ�ֵ:"<<endl;
    for(int i=1;i<=n;i++)
    {
        w[i]=goods[S[i-1].id].weight;//�����������ݴ��ݸ���������
        v[i]=goods[S[i-1].id].value;
        cout<<w[i]<<"  "<<v[i]<<endl;
    }
    priorbfs();//���ȶ��з�֧�޽編����
    // ������Ž�
    cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
    cout<<"���빺�ﳵ����Ʒ���Ϊ: ";
    //������Ž�
    for(int i=1;i<=n;i++)
    {
        if(bestx[i])
           cout<<S[i-1].id<<" ";//���ԭ��Ʒ���(����ǰ��)
    }
    return 0;
}
