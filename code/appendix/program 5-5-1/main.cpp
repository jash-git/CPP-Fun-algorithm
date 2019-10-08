//program 5-5-1
#include <iostream>
#define MX 50
using namespace std;
int x[MX];         //解分量
int n;

void myarray(int t)
{
    if(t>n)
    {
        for(int i=1;i<=n;i++) // 输出排列
            cout<<x[i]<<" ";
        cout<<endl;

        return ;
    }
    for(int i=t;i<=n;i++)  // 枚举
    {
       swap(x[t],x[i]);  // 交换
       myarray(t+1);  // 继续深搜
       swap(x[t],x[i]); // 恢复
    }
}

int main()
{
    cout << "输入排列的元素个数n(求1..n的排列):" << endl;
    cin>>n;
    for(int i=1;i<=n;i++) //初始化
       x[i]=i;
    myarray(1);
    return 0;
}
