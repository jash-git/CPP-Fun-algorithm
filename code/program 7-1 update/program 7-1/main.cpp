//program 7-1
#include <iostream>
#include<math.h>
#include<iomanip>
#include<stdio.h>
using namespace std;
float kernel[100][100];  //存储非单纯形表
char  FJL[100]={};      //非基本变量
char  JL[100]={};        //基本变量
int n,m,i,j;

void print()//输出单纯型表
{
    cout<<endl;
    cout<<"----------单纯形表如下：----------"<<endl;
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
    float max1;  //max1用于存放最大的检验数
    float max2;  //max2用于存放最大正检验数对应的基本变量的最大系数
    int e=-1;    //记录入基列
    int k=-1;    //记录离基行
    float min;
    //循环迭代，直到找到问题的解或无解为止
    while(true)
    {
        max1=0;
        min=100000000;
        for(j=1;j<=m;j++)  //找入基列(最大正检验数对应的列)
        {
            if(max1<kernel[0][j])
            {
                max1=kernel[0][j];
                e=j;
            }
        }
        if(max1<=0) //最大值小于等于0，即所有检验数小于等于0，满足获得最优解的条件
        {
           cout<<endl;
           cout<<"获得最优解:"<<kernel[0][0]<< endl;
           print();
           break;
         }
        for(j=1;j<=m;j++)  //判断正检验数对应的列是否都小于等于0，如果是则无界解
        {
            max2=0;
            if(kernel[0][j]>0)
            {
                for(i=1;i<=n;i++) //搜索正检验数对应的列
                  if(max2<kernel[i][j])
                     max2=kernel[i][j];
                if(max2==0)
                {
                   cout<<"解无界"<<endl;
                   return;//退出函数，不能用break，因为它只是退出当前循环
                }
            }
        }
        for(i=1;i<=n;i++) //找离基行(常数列/入基列正比值最小对应的行)
        {
            if(max2<kernel[i][e])
            {
                max2=kernel[i][e];
            }
            float temp=kernel[i][0]/kernel[i][e]; //常数项在前,temp=fabs(temp);
            if(temp>0&&temp<min) //找离基变量
            {
               min=temp;
               k=i;
            }
        }
        cout<<"入基变量："<<"x"<<FJL[e]<<" ";
        cout<<"离基变量："<<"x"<<JL[k]<<endl;
       //换基变换(转轴变换)
        char temp=FJL[e];
        FJL[e]=JL[k];
        JL[k]=temp;
        for(i=0;i<=n;i++) //计算除入基列和出基行的所有位置的元素
        {
            if(i!=k)
            {
                for(j=0;j<=m;j++)
                {
                    if(j!=e)
                    {
                        if(i==0&&j==0) //计算特殊位c0,即目标函数的值
                           kernel[i][j]=kernel[i][j]+kernel[i][e]*kernel[k][j]/kernel[k][e];
                        else   //一般位置
                           kernel[i][j]=kernel[i][j]-kernel[i][e]*kernel[k][j]/kernel[k][e];
                    }
                }
            }
        }
        for(i=0;i<=n;i++) //计算特殊位,入基列的元素
        {
            if(i!=k)
                kernel[i][e]=-kernel[i][e]/kernel[k][e];
        }
        for(j=0;j<=m;j++) //计算特殊位,离基行的元素
        {
            if(j!=e)
              kernel[k][j]=kernel[k][j]/kernel[k][e];
        }
        //计算特殊位,交叉位置
        kernel[k][e]=1/kernel[k][e];
        print();
    }
}

int main()
{
    int i,j;
    cout<<"输入非基本变量个数和非基本变量下标："<< endl;
    cin>>m;
    for(i=1;i<=m;i++)
      cin>>FJL[i] ;
    cout<<"输入基本变量个数和基本变量下标："<<endl;;
    cin>>n ;
    for(i=1;i<=n;i++)
      cin>>JL[i];
    cout<<"输入约束标准型初始单纯形表参数："<<endl;;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=m;j++)
          cin>>kernel[i][j];
    }
    print();
    DCXA();
    return 0;
}
