//program 5-2
#include <iostream>
#include <string.h>

using namespace std;

const int N = 100;
int a[N][N];  //图用邻接矩阵表示
bool x[N];     //是否将第i个结点加入团中
bool bestx[N]; //记录最优解
int bestn;    //记录最优值
int cn;       //当前已放入团中的结点数量
int n,m;       //n为图中结点数，m为图中边数

bool Place(int t) //判断是否可以把结点t加入团中
{
    bool ok=true;
    for(int j=1;j<t; j++)  //结点t与前t-1个结点中被选中的结点是否相连
    {
        if(x[j]&&a[t][j]==0) //x[j]表示j是被选中的结点,a[t][j]==0表示t和j没有边相连
        {
            ok = false;
            break;
        }
    }
    return ok;
}

void Backtrack(int t)
{
    if(t>n) //到达叶结点
    {
        for(int i=1; i<=n; i++)
            bestx[i]=x[i];
        bestn=cn;
        return ;
    }
    if(Place(t)) //满足约束条件，进入左子树，即把结点t加入团中
    {
        x[t]=1;
        cn++;
        Backtrack(t+1);
        cn--;
    }
    if(cn+n-t>bestn) //满足限界条件，进入右子树
    {
        x[t] = 0;
        Backtrack(t + 1);
    }
}

int main() {

    int i,u, v;
    cout << "请输入部落的人数 n(结点数):";
    cin >> n;
    cout << "请输入人与人的友好关系数(边数):";
    cin >> m;
    memset(a,0,sizeof(a));//邻接矩阵里面的数据初始化为0,需要引入#include <string.h>
    cout << "请依次输入有友好关系的两个人(有边相连的两个结点u和v),用空格分开:";
    for(i=1;i<=m;i++)
    {
        cin>>u>>v;
        a[u][v]=a[v][u]=1;
    }
    bestn=0;
    cn=0;
    Backtrack(1);
    cout<<"国王护卫队的最大人数为："<<bestn<<endl;
    cout<<"国王护卫队的成员为：";
    for(int i=1;i<=n;i++)
        if(bestx[i])
            cout<<i<<"  ";
    return 0;
}
