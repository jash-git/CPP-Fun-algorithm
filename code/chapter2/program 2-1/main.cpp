//program 2-1
#include <iostream>
#include <algorithm>
const int N=1000005;
using namespace std;

double w[N]; //�Ŷ�����������
int main()
{
    double c;
    int n;
    cout<<"������������c���Ŷ�����n��"<<endl;
    cin>>c>>n;
    cout<<"������ÿ���Ŷ����������ÿո�ֿ��� "<<endl;
    for(int i=0;i<n;i++)
    {
      cin>>w[i]; //����ÿ����Ʒ����
    }
    sort(w,w+n); //���Ŷ�������������
    double tmp=0.0;
    int ans=0; // tmpΪ��װ�ص����ϵĹŶ�������ansΪ��װ�صĹŶ�����
    for(int i=0;i<n;i++)
{
      tmp+=w[i];
     if(tmp<=c)
     ans++;
      else
        break;
}
    cout<<"��װ��ĹŶ��������ΪAns=";
    cout<<ans<<endl;
    return 0;
}

//��������Ŷ����
/**
struct antique{
    int id; //�Ŷ��ı��
    double w; //�Ŷ�������
}s[N];
bool cmp(antique a, antique b)//�ȽϺ���
{
    return a.w < b.w; //ָ�����չŶ�������������
}
int main()
{
    double c;
    int n;
    cout<<"������������c���Ŷ�����n��"<<endl;
    cin>>c>>n;
    cout<<"������ÿ���Ŷ����������ÿո�ֿ��� "<<endl;
    for(int i=0;i<n;i++)
    {
      s[i].id=i+1;
      cin>>s[i].w; //����ÿ���Ŷ�����,�ÿո����
    }
    sort(s,s+n,cmp);
    double tmp=0.0;
    int ans =0;  //ans��¼�Ѿ�װ�صĹŶ�������tmp����װ�ص����ϵĹŶ�������
    for(int i=0;i<n;i++)
    {
     tmp += s[i].w;
     if(tmp<=c)
       ans ++;
    else
       break;
     }
    cout<<"��װ��ĹŶ��������ΪAns = ";
    cout<<ans<<endl;
    cout<<"װ��ĹŶ����Ϊ";
    for(int i=0;i<ans;i++)
    {
      cout<<s[i].id<<" ";
    }
    return 0;
}
**/
