//program 7-1
#include <iostream>
#include<math.h>
#include<iomanip>
#include<stdio.h>
using namespace std;
float kernel[100][100];  //�洢�ǵ����α�
char  FJL[100]={};          //�ǻ�������
char  JL[100]={};           //��������
int n,m,i,j;

void print()//��������ͱ�
{
    cout<<endl;
    cout<<"----------�����α����£�----------"<<endl;
    cout<<"  ";
    cout<<setw(7)<<"b ";
    for(i=1;i<=m;i++)
       cout<<setw(7)<<"x"<<FJL[i];
    cout<<endl;
    cout<<"c ";
    for(i=0;i<=n;i++)
    {
        if(i>=1)
            cout<<"x"<<JL[i];
        for(j=0;j<=m;j++)
           cout<<setw(7)<<kernel[i][j]<<" ";
        cout<<endl;
    }
}

void DCXA()
{
    float max1;  //max1���ڴ�����ļ�����
    float max2;  //max2���ڴ���������������Ӧ�Ļ������������ϵ��
    int e=-1;    //��¼�����
    int k=-1;    //��¼�����
    float min;
    //ѭ��������ֱ���ҵ�����Ľ���޽�Ϊֹ
    while(true)
    {
        max1=0;
        max2=0;
        min=100000000;
        for(j=1;j<=m;j++)  //�������(�������������Ӧ����)
        {
            if(max1<kernel[0][j])
            {
                max1=kernel[0][j];
                e=j;
            }
        }
        if(max1<=0) //���ֵС�ڵ���0�������м�����С�ڵ���0�����������Ž������
        {
           cout<<endl;
           cout<<"������Ž�:"<<kernel[0][0]<< endl;
           print();
           break;
         }
        for(i=1;i<=n;i++) //�������(������/���������ֵ��С��Ӧ����)
        {
            if(max2<kernel[i][e])
            {
                max2=kernel[i][e];
            }
            float temp=kernel[i][0]/kernel[i][e]; //��������ǰ,temp=fabs(temp);
            if(temp>0&&temp<min) //���������
            {
               min=temp;
               k=i;
            }
        }
        cout<<"���б�����"<<"x"<<FJL[e]<<" ";
        cout<<"���������"<<"x"<<JL[k]<<endl;
       if(max2==0)
        {
            cout<<"���޽�"<<endl;
            break;
        }
       //�����任(ת��任)
        char temp=FJL[e];
        FJL[e]=JL[k];
        JL[k]=temp;
        for(i=0;i<=n;i++) //���������кͳ����е�����λ�õ�Ԫ��
        {
            if(i!=k)
            {
                for(j=0;j<=m;j++)
                {
                    if(j!=e)
                    {
                        if(i==0&&j==0) //��������λc0,��Ŀ�꺯����ֵ
                           kernel[i][j]=kernel[i][j]+kernel[i][e]*kernel[k][j]/kernel[k][e];
                        else   //һ��λ��
                           kernel[i][j]=kernel[i][j]-kernel[i][e]*kernel[k][j]/kernel[k][e];
                    }
                }
            }
        }
        for(i=0;i<=n;i++) //��������λ,����е�Ԫ��
        {
            if(i!=k)
                kernel[i][e]=-kernel[i][e]/kernel[k][e];
        }
        for(j=0;j<=m;j++) //��������λ,����е�Ԫ��
        {
            if(j!=e)
              kernel[k][j]=kernel[k][j]/kernel[k][e];
        }
        //��������λ,����λ��
        kernel[k][e]=1/kernel[k][e];
        print();
    }
}

int main()
{
    int i,j;
    cout<<"����ǻ������������ͷǻ��������±꣺"<< endl;
    cin>>m;
    for(i=1;i<=m;i++)
      cin>>FJL[i] ;
    cout<<"����������������ͻ��������±꣺"<<endl;;
    cin>>n ;
    for(i=1;i<=n;i++)
      cin>>JL[i];
    cout<<"����Լ����׼�ͳ�ʼ�����α������"<<endl;;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=m;j++)
          cin>>kernel[i][j];
    }
    print();
    DCXA();
    return 0;
}
