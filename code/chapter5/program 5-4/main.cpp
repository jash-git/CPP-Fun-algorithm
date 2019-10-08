//program 5-4
#include <iostream>
#include<cmath>   //求绝对值函数需要引入该头文件
#define M 105
using namespace std;

int n;//n表示n个皇后
int x[M];  //x[i]表示第i个皇后放置在第i行第x[i]列
int countn;    //countn表示n皇后问题可行解的个数

bool Place(int t) //判断第t个皇后能否放置在第i个位置
{
    bool ok=true;
    for(int j=1;j<t;j++)   //判断该位置的皇后是否与前面t-1个已经放置的皇后冲突
    {
       if(x[t]==x[j]||t-j==fabs(x[t]-x[j]))//判断列、对角线是否冲突
       {
           ok=false;
           break;
       }
    }
    return ok;
}

void Backtrack(int t)
{
    if(t>n)  //如果当前位置为n,则表示已经找到了问题的一个解
    {
        countn++;
        for(int i=1; i<=n;i++) //打印选择的路径
          cout<<x[i]<<" ";
        cout<<endl;
        cout<<"----------"<<endl;
    }
    else
        for(int i=1;i<=n;i++) //分别判断n个分支,特别注意i不要定义为全局变量,否则递归调用有问题
        {
            x[t]=i;
            if(Place(t))
                Backtrack(t+1); //如果不冲突的话进行下一行的搜索
        }
}
int main()
{
    cout<<"请输入皇后的个数 n:";
    cin>>n;
    countn=0;
    Backtrack(1);
    cout <<"答案的个数是："<<countn<< endl;
    return 0;
}
