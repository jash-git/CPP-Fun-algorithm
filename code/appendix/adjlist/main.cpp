//adjlist
#include <iostream>

using namespace std;

const   int N=10000;

 struct Node { //定义表结点
  int v; //以v为弧头的顶点编号
  int w; //边的权值
  Node *next; //指向下一个邻接结点
};

 struct Hnode{ //定义顶点类型
   Node *first; //指向第一个邻接点
};

Hnode g[N];
int n,m,i,u,v,w;

void insertedge(Hnode &p,int x,int y) //插入一条边
{
    Node *q;
    q=new(Node);
    q->v=x;
    q->w=y;
    q->next=p.first;
    p.first=q;
}

void printg(int n)//输出邻接表
{
   cout<<"----------邻接表如下：----------"<<endl;
   for(int i=1;i<=n;i++)
   {
       Node *t=g[i].first;
       cout<<"v"<<i<<"：  ";
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
    cout<<"请输入顶点数n和边数m:"<<endl;
    cin >>n>>m;
    for(i=1; i<=n; i++)
        g[i].first=NULL;
    cout<<"请依次输入每条边的两个顶点u,v和边的权值w:"<<endl;
    for(i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        insertedge(g[u],v,w);
        //无向图时还要插入一条反向边
    }
    printg(n);//输出邻接表
    return 0;
}
