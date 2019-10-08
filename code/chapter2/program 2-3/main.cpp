//program 2-3
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct Meet
{
    int beg;   //会议的开始时间
    int end;   //会议的结束时间
    int num;   //记录会议的编号
}meet[1000];   //会议的最大个数为1000

class setMeet{
  public:
    void init();
    void solve();
  private:
    int n,ans; // n:会议总数 ans: 最大的安排会议总数
};

//读入数据
void setMeet::init()
{
    int s,e;
    cout <<"输入会议总数："<<endl;
    cin >> n;
    int i;
    cout <<"输入会议的开始时间和结束时间，以空格分开:"<<endl;
    for(i=0;i<n;++i)
    {
        cin>>s>>e;
        meet[i].beg=s;
        meet[i].end=e;
        meet[i].num=i+1;
    }
}

bool cmp(Meet x,Meet y)
{
    if (x.end == y.end)
        return x.beg > y.beg;
    return x.end < y.end;
}

void setMeet::solve()
{
    sort(meet,meet+n,cmp);    //对会议按结束时间排序
    cout <<"排完序的会议时间如下:"<<endl;
    int i;
    cout <<"会议编号："<<"  开始时间 "<<" 结束时间"<<endl;
    for(i=0; i<n;i++)
    {
      cout<< "   " << meet[i].num<<"\t\t"<<meet[i].beg <<"\t"<< meet[i].end << endl;
    }
    cout <<"-------------------------------------------------"<<endl;
    cout << "选择的会议的过程:" <<endl;
    cout <<"  选择第"<< meet[0].num<<"个会议" << endl;//选中了第一个会议
    ans=1;
    int last = meet[0].end;  //记录刚刚被选中会议的结束时间
    for( i = 1;i < n;++i)
    {
        if(meet[i].beg>=last)
        {            //如果会议i开始时间大于等于最后一个选中的会议的结束时间
           ans++;
           last = meet[i].end;
           cout <<"  选择第"<<meet[i].num<<"个会议"<<endl;
         }
    }
    cout <<"最多可以安排" <<ans << "个会议"<<endl;
}

int main()
{
  setMeet sm;
  sm.init();//读入数据
  sm.solve();//贪心算法求解
  return 0;
}
