//program 2-2
#include<iostream>
#include<algorithm>
using namespace std;
const int M=1000005;
struct three{
    double w;//ÿ�����������
    double v;//ÿ������ļ�ֵ
    double p;//�Լ۱�
}s[M];
bool cmp(three a,three b)
{
    return a.p>b.p;//���ݱ���ĵ�λ��ֵ�Ӵ�С����
}
int main()
{
    int n;//n ��ʾ��n������
    double m ;//m ��ʾë¿�ĳ�������
    cout<<"�����뱦������n��ë¿�ĳ�������m ��"<<endl;
    cin>>n>>m;
    cout<<"������ÿ������������ͼ�ֵ���ÿո�ֿ��� "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>s[i].w>>s[i].v;
        s[i].p=s[i].v/s[i].w;//ÿ�����ﵥλ��ֵ
    }
    sort(s,s+n,cmp);
    double sum=0.0;// sum ��ʾ̰�ļ�¼���߱���ļ�ֵ֮��
    for(int i=0;i<n;i++)//�����źõ�˳��̰��
    {
        if( m>s[i].w )//������������С��ë¿ʣ�µĳ�������
        {
            m-=s[i].w;
            sum+=s[i].v;
        }
        else//����������������ë¿ʣ�µĳ�������
        {
            sum+=m*s[i].p;//����װ��
            break;
        }
    }
    cout<<"װ�뱦�������ֵMaximum value="<<sum<<endl;//���װ�뱦�������ֵ
    return 0;
}

