//program 2-5
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define MAXBIT    100
#define MAXVALUE  10000
#define MAXLEAF   30
#define MAXNODE   MAXLEAF*2 -1

typedef struct
{
    double weight;
    int parent;
    int lchild;
    int rchild;
    char value;
} HNodeType;        /* 结点结构体 */

typedef struct
{
    int bit[MAXBIT];
    int start;
} HCodeType;        /* 编码结构体 */
HNodeType HuffNode[MAXNODE]; /* 定义一个结点结构体数组 */
HCodeType HuffCode[MAXLEAF];/* 定义一个编码结构体数组*/
/* 构造哈夫曼树 */
void HuffmanTree (HNodeType HuffNode[MAXNODE],  int n){
    /* i、j： 循环变量，m1、m2：构造哈夫曼树不同过程中两个最小权值结点的权值，
       x1、x2：构造哈夫曼树不同过程中两个最小权值结点在数组中的序号。*/
    int i, j, x1, x2;
    double m1,m2;
    /* 初始化存放哈夫曼树数组 HuffNode[] 中的结点 */
    for (i=0; i<2*n-1;i++)
    {
        HuffNode[i].weight=0;//权值
        HuffNode[i].parent=-1;
        HuffNode[i].lchild=-1;
        HuffNode[i].rchild=-1;
    }
    /* 输入 n 个叶子结点的权值 */
    for (i=0; i<n; i++)
    {
        cout<<"Please input value and weight of leaf node "<<i+1<<endl;
        cin>>HuffNode[i].value>>HuffNode[i].weight;
    }
    /* 构造 Huffman 树 */
    for (i=0; i<n-1; i++)
    {//执行n-1次合并
         m1=m2=MAXVALUE;
         /* m1、m2中存放两个无父结点且结点权值最小的两个结点 */
        x1=x2=0;
        /* 找出所有结点中权值最小、无父结点的两个结点，并合并之为一棵二叉树 */
        for (j=0;j<n+i;j++)
        {
            if (HuffNode[j].weight<m1&&HuffNode[j].parent==-1)
            {
                m2 = m1;
                x2 = x1;
                m1 = HuffNode[j].weight;
                x1 = j;
            }
            else if (HuffNode[j].weight < m2 && HuffNode[j].parent==-1)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
        /* 设置找到的两个子结点 x1、x2 的父结点信息 */
        HuffNode[x1].parent  = n+i;
        HuffNode[x2].parent  = n+i;
        HuffNode[n+i].weight = m1+m2;
        HuffNode[n+i].lchild = x1;
        HuffNode[n+i].rchild = x2;
        cout<<"x1.weight and x2.weight in round "<<i+1<<"\t"<<HuffNode[x1].weight<<"\t"<<HuffNode[x2].weight<<endl; /* 用于测试 */
    }
}
/* 哈夫曼树编码 */
void HuffmanCode(HCodeType HuffCode[MAXLEAF],  int n){
    HCodeType cd;       /* 定义一个临时变量来存放求解编码时的信息 */
    int i,j,c,p;
    for(i=0;i<n;i++)
    {
        cd.start=n-1;
        c=i;
        p=HuffNode[c].parent;
        while(p!=-1)
        {
            if(HuffNode[p].lchild==c)
                cd.bit[cd.start]=0;
            else
                cd.bit[cd.start]=1;
            cd.start--;        /*前移一位 */
            c=p;
            p=HuffNode[c].parent;    /* 设置下一循环条件 */
        }
        /* 把叶子结点的编码信息从临时编码cd中复制出来，放入编码结构体数组 */
        for (j=cd.start+1; j<n; j++)
           HuffCode[i].bit[j]=cd.bit[j];
        HuffCode[i].start=cd.start;
    }
}
int main()
{
    int i,j,n;
    cout<<"Please input n:"<<endl;
    cin>>n;
    HuffmanTree(HuffNode,n);  //构造哈夫曼树
    HuffmanCode(HuffCode,n);  // 哈夫曼树编码
    //输出已保存好的所有存在编码的哈夫曼编码
    for(i=0;i<n;i++)
    {
        cout<<HuffNode[i].value<<": Huffman code is: ";
        for(j=HuffCode[i].start+1;j<n;j++)
            cout<<HuffCode[i].bit[j];
        cout<<endl;
    }
    return 0;
}
