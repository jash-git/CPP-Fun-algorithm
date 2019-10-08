//program 2-3
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct Meet
{
    int beg;   //����Ŀ�ʼʱ��
    int end;   //����Ľ���ʱ��
    int num;   //��¼����ı��
}meet[1000];   //�����������Ϊ1000

class setMeet{
  public:
    void init();
    void solve();
  private:
    int n,ans; // n:�������� ans: ���İ��Ż�������
};

//��������
void setMeet::init()
{
    int s,e;
    cout <<"�������������"<<endl;
    cin >> n;
    int i;
    cout <<"�������Ŀ�ʼʱ��ͽ���ʱ�䣬�Կո�ֿ�:"<<endl;
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
    sort(meet,meet+n,cmp);    //�Ի��鰴����ʱ������
    cout <<"������Ļ���ʱ������:"<<endl;
    int i;
    cout <<"�����ţ�"<<"  ��ʼʱ�� "<<" ����ʱ��"<<endl;
    for(i=0; i<n;i++)
    {
      cout<< "   " << meet[i].num<<"\t\t"<<meet[i].beg <<"\t"<< meet[i].end << endl;
    }
    cout <<"-------------------------------------------------"<<endl;
    cout << "ѡ��Ļ���Ĺ���:" <<endl;
    cout <<"  ѡ���"<< meet[0].num<<"������" << endl;//ѡ���˵�һ������
    ans=1;
    int last = meet[0].end;  //��¼�ոձ�ѡ�л���Ľ���ʱ��
    for( i = 1;i < n;++i)
    {
        if(meet[i].beg>=last)
        {            //�������i��ʼʱ����ڵ������һ��ѡ�еĻ���Ľ���ʱ��
           ans++;
           last = meet[i].end;
           cout <<"  ѡ���"<<meet[i].num<<"������"<<endl;
         }
    }
    cout <<"�����԰���" <<ans << "������"<<endl;
}

int main()
{
  setMeet sm;
  sm.init();//��������
  sm.solve();//̰���㷨���
  return 0;
}
