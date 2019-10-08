//program 6-1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int N = 10;
bool bestx[N];
//�����㡣ÿ���ڵ�����¼��ǰ�Ľ⡣
struct Node
{
    int cp, rp; //cp��������Ʒ�ܼ�ֵ��rpʣ����Ʒ���ܼ�ֵ
    int rw; //ʣ������
    int id; //��Ʒ��
    bool x[N];//������
    Node() {}
    Node(int _cp, int _rp, int _rw, int _id){
        cp = _cp;
        rp = _rp;
        rw = _rw;
        id = _id;
        memset(x, 0, sizeof(x));//��������ʼ��Ϊ0
    }
};
struct Goods
{
    int value;
    int weight;
} goods[N];

int bestp,W,n,sumw,sumv;
/*
  bestp ������¼���Ž⡣
  WΪ���ﳵ���������
  nΪ��Ʒ�ĸ�����
  sumw Ϊ������Ʒ����������
  sumv Ϊ������Ʒ���ܼ�ֵ��
*/
//bfs �������Ӽ�����������
int bfs()
{
    int t,tcp,trp,trw;
    queue<Node> q; //����һ����ͨ����(�Ƚ��ȳ�)
    q.push(Node(0, sumv, W, 1)); //ѹ��һ����ʼ���
    while(!q.empty()) //������в���
    {
        Node livenode, lchild, rchild;//������������ͱ���
        livenode=q.front();//ȡ����ͷԪ����Ϊ��ǰ��չ���livenode
        q.pop(); //��ͷԪ�س���
        //cp+rp>bestp��ǰװ��ļ�ֵ+ʣ����Ʒ��ֵС�ڵ�ǰ����ֵʱ��������չ��
        cout<<"��ǰ����idֵ:"<<livenode.id<<"��ǰ����cpֵ:"<<livenode.cp<<endl;
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
              for(int i=1; i<=n; i++)
              {
                bestx[i]=livenode.x[i];
              }
              bestp=livenode.cp;
            }
            continue;
        }
        if(livenode.cp+livenode.rp<bestp)//�жϵ�ǰ����Ƿ������޽���������������㲻����չ
          continue;
        //��չ����
        tcp=livenode.cp; //��ǰ���ﳵ�еļ�ֵ
        trp=livenode.rp-goods[t].value; //���ܵ�ǰ��Ʒװ�����ʣ���ֵ������١�
        trw=livenode.rw; //���ﳵʣ������
        if(trw>=goods[t].weight) //����Լ�����������Է��빺�ﳵ
        {
            lchild.rw=trw-goods[t].weight;
            lchild.cp=tcp+goods[t].value;
            lchild=Node(lchild.cp,trp,lchild.rw,t+1);//���ݲ���
            for(int i=1;i<t;i++)
            {
              lchild.x[i]=livenode.x[i];//������ǰ�Ľ�����
            }
            lchild.x[t]=true;
            if(lchild.cp>bestp)//������ֵ��Ÿ���
               bestp=lchild.cp;
            q.push(lchild);//�������
        }
        //��չ�Һ���
        if(tcp+trp>=bestp)//�����޽������������빺�ﳵ
        {
            rchild=Node(tcp,trp,trw,t+1);//���ݲ���
            for(int i=1;i<t;i++)
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
    //������Ʒ�ĸ����ͱ���������
    cout << "��������Ʒ�ĸ��� n:";
    cin >> n;
    cout << "�����빺�ﳵ������W:";
    cin >> W;
    cout << "����������ÿ����Ʒ������w�ͼ�ֵv,�ÿո�ֿ�:";
    bestp=0; //bestv ������¼���Ž�
    sumw=0; //sumwΪ������Ʒ����������
    sumv=0;   //sum Ϊ������Ʒ���ܼ�ֵ
    for(int i=1; i<=n; i++)
    {
        cin >> goods[i].weight >> goods[i].value;//����� i ����Ʒ������ͼ�ֵ��
        sumw+= goods[i].weight;
        sumv+= goods[i].value;
    }
    if(sumw<=W)
    {
        bestp=sumv;
        cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
        cout<<"���е���Ʒ�����빺�ﳵ��";
        return 0;
    }
    bfs();
    cout<<"���빺�ﳵ����Ʒ����ֵΪ: "<<bestp<<endl;
    cout<<"���빺�ﳵ����Ʒ���Ϊ: ";
    // ������Ž�
    for(int i=1; i<=n; i++)
    {
        if(bestx[i])
           cout<<i<<"  ";
    }
    return 0;
}
