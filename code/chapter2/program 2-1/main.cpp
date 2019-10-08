//program 2-1
#include <iostream>
#include <algorithm>
const int N=1000005;
using namespace std;

double w[N]; //古董的重量数组
int main()
{
    double c;
    int n;
    cout<<"请输入载重量c及古董个数n："<<endl;
    cin>>c>>n;
    cout<<"请输入每个古董的重量，用空格分开： "<<endl;
    for(int i=0;i<n;i++)
    {
      cin>>w[i]; //输入每个物品重量
    }
    sort(w,w+n); //按古董重量升序排序
    double tmp=0.0;
    int ans=0; // tmp为已装载到船上的古董重量，ans为已装载的古董个数
    for(int i=0;i<n;i++)
{
      tmp+=w[i];
     if(tmp<=c)
     ans++;
      else
        break;
}
    cout<<"能装入的古董最大数量为Ans=";
    cout<<ans<<endl;
    return 0;
}

//可以输出古董编号
/**
struct antique{
    int id; //古董的编号
    double w; //古董的重量
}s[N];
bool cmp(antique a, antique b)//比较函数
{
    return a.w < b.w; //指明按照古董重量升序排列
}
int main()
{
    double c;
    int n;
    cout<<"请输入载重量c及古董个数n："<<endl;
    cin>>c>>n;
    cout<<"请输入每个古董的重量，用空格分开： "<<endl;
    for(int i=0;i<n;i++)
    {
      s[i].id=i+1;
      cin>>s[i].w; //输入每个古董重量,用空格隔开
    }
    sort(s,s+n,cmp);
    double tmp=0.0;
    int ans =0;  //ans记录已经装载的古董个数，tmp代表装载到船上的古董的重量
    for(int i=0;i<n;i++)
    {
     tmp += s[i].w;
     if(tmp<=c)
       ans ++;
    else
       break;
     }
    cout<<"能装入的古董最大数量为Ans = ";
    cout<<ans<<endl;
    cout<<"装入的古董编号为";
    for(int i=0;i<ans;i++)
    {
      cout<<s[i].id<<" ";
    }
    return 0;
}
**/
