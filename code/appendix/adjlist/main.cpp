//adjlist
#include <iostream>

using namespace std;

const   int N=10000;

 struct Node { //�������
  int v; //��vΪ��ͷ�Ķ�����
  int w; //�ߵ�Ȩֵ
  Node *next; //ָ����һ���ڽӽ��
};

 struct Hnode{ //���嶥������
   Node *first; //ָ���һ���ڽӵ�
};

Hnode g[N];
int n,m,i,u,v,w;

void insertedge(Hnode &p,int x,int y) //����һ����
{
    Node *q;
    q=new(Node);
    q->v=x;
    q->w=y;
    q->next=p.first;
    p.first=q;
}

void printg(int n)//����ڽӱ�
{
   cout<<"----------�ڽӱ����£�----------"<<endl;
   for(int i=1;i<=n;i++)
   {
       Node *t=g[i].first;
       cout<<"v"<<i<<"��  ";
       while(t!=NULL)
       {
           cout<<"["<<t->v<<"  "<<t->w<<"]   ";
           t=t->next;
       }
       cout<<endl;
   }
}


int main()
{
    cout<<"�����붥����n�ͱ���m:"<<endl;
    cin >>n>>m;
    for(i=1; i<=n; i++)
        g[i].first=NULL;
    cout<<"����������ÿ���ߵ���������u,v�ͱߵ�Ȩֵw:"<<endl;
    for(i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        insertedge(g[u],v,w);
        //����ͼʱ��Ҫ����һ�������
    }
    printg(n);//����ڽӱ�
    return 0;
}
