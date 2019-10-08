//program 6-1
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int N = 10;
bool bestx[N];
//定义结点。每个节点来记录当前的解。
struct Node
{
    int cp, rp; //cp背包的物品总价值，rp剩余物品的总价值
    int rw; //剩余容量
    int id; //物品号
    bool x[N];//解向量
    Node() {}
    Node(int _cp, int _rp, int _rw, int _id){
        cp = _cp;
        rp = _rp;
        rw = _rw;
        id = _id;
        memset(x, 0, sizeof(x));//解向量初始化为0
    }
};
struct Goods
{
    int value;
    int weight;
} goods[N];

int bestp,W,n,sumw,sumv;
/*
  bestp 用来记录最优解。
  W为购物车最大容量。
  n为物品的个数。
  sumw 为所有物品的总重量。
  sumv 为所有物品的总价值。
*/
//bfs 来进行子集树的搜索。
int bfs()
{
    int t,tcp,trp,trw;
    queue<Node> q; //创建一个普通队列(先进先出)
    q.push(Node(0, sumv, W, 1)); //压入一个初始结点
    while(!q.empty()) //如果队列不空
    {
        Node livenode, lchild, rchild;//定义三个结点型变量
        livenode=q.front();//取出队头元素作为当前扩展结点livenode
        q.pop(); //队头元素出队
        //cp+rp>bestp当前装入的价值+剩余物品价值小于当前最优值时，不再扩展。
        cout<<"当前结点的id值:"<<livenode.id<<"当前结点的cp值:"<<livenode.cp<<endl;
        cout<<"当前结点的解向量:";
        for(int i=1; i<=n; i++)
        {
            cout<<livenode.x[i];
        }
        cout<<endl;
        t=livenode.id;//当前处理的物品序号
        // 搜到最后一个物品的时候不需要往下搜索。
        // 如果当前的购物车没有剩余容量(已经装满)了，不再扩展。
        if(t>n||livenode.rw==0)
        {
            if(livenode.cp>=bestp)//更新最优解和最优值
            {
              for(int i=1; i<=n; i++)
              {
                bestx[i]=livenode.x[i];
              }
              bestp=livenode.cp;
            }
            continue;
        }
        if(livenode.cp+livenode.rp<bestp)//判断当前结点是否满足限界条件，如果不满足不再扩展
          continue;
        //扩展左孩子
        tcp=livenode.cp; //当前购物车中的价值
        trp=livenode.rp-goods[t].value; //不管当前物品装入与否，剩余价值都会减少。
        trw=livenode.rw; //购物车剩余容量
        if(trw>=goods[t].weight) //满足约束条件，可以放入购物车
        {
            lchild.rw=trw-goods[t].weight;
            lchild.cp=tcp+goods[t].value;
            lchild=Node(lchild.cp,trp,lchild.rw,t+1);//传递参数
            for(int i=1;i<t;i++)
            {
              lchild.x[i]=livenode.x[i];//复制以前的解向量
            }
            lchild.x[t]=true;
            if(lchild.cp>bestp)//比最优值大才更新
               bestp=lchild.cp;
            q.push(lchild);//左孩子入队
        }
        //扩展右孩子
        if(tcp+trp>=bestp)//满足限界条件，不放入购物车
        {
            rchild=Node(tcp,trp,trw,t+1);//传递参数
            for(int i=1;i<t;i++)
            {
              rchild.x[i]=livenode.x[i];//复制以前的解向量
            }
            rchild.x[t]=false;
            q.push(rchild);//右孩子入队
        }
    }
    return bestp;//返回最优值。
}

int main()
{
    //输入物品的个数和背包的容量
    cout << "请输入物品的个数 n:";
    cin >> n;
    cout << "请输入购物车的容量W:";
    cin >> W;
    cout << "请依次输入每个物品的重量w和价值v,用空格分开:";
    bestp=0; //bestv 用来记录最优解
    sumw=0; //sumw为所有物品的总重量。
    sumv=0;   //sum 为所有物品的总价值
    for(int i=1; i<=n; i++)
    {
        cin >> goods[i].weight >> goods[i].value;//输入第 i 件物品的体积和价值。
        sumw+= goods[i].weight;
        sumv+= goods[i].value;
    }
    if(sumw<=W)
    {
        bestp=sumv;
        cout<<"放入购物车的物品最大价值为: "<<bestp<<endl;
        cout<<"所有的物品均放入购物车。";
        return 0;
    }
    bfs();
    cout<<"放入购物车的物品最大价值为: "<<bestp<<endl;
    cout<<"放入购物车的物品序号为: ";
    // 输出最优解
    for(int i=1; i<=n; i++)
    {
        if(bestx[i])
           cout<<i<<"  ";
    }
    return 0;
}
