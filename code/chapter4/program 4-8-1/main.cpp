//program 4-8-1
#include<iostream>
#include<cmath>   //�����ֵ������Ҫ�����ͷ�ļ�
using namespace std;
const int M=1000+5;
double c[M][M],w[M][M],p[M],q[M];
int s[M][M];
int n,i,j,k;
void Optimal_BST()
{
	for(i=1;i<=n+1;i++)
	{
		c[i][i-1]=0.0;
		w[i][i-1]=q[i-1];
	}
	for(int t=1;t<=n;t++)//tΪ�ؼ��ֵĹ�ģ
		//���±�Ϊi��ʼ�Ĺؼ��ֵ��±�Ϊj�Ĺؼ���
		for(i=1;i<=n-t+1;i++)
		{
			j=i+t-1;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			int i1=s[i][j-1]>i?s[i][j-1]:i;
            int j1=s[i+1][j]<j?s[i+1][j]:j;
			c[i][j]=c[i][i1-1]+c[i1+1][j];//��ʼ��
			s[i][j]=i1;//��ʼ��
			//ѡȡi1+1��j1֮���ĳ���±�Ĺؼ�����Ϊ��i��j�ĸ��������ɵ���������ֵ��ǰ��С����kΪ��i��j�ĸ��ڵ�
			for(k=i1+1;k<=j1;k++)
			{
				double temp=c[i][k-1]+c[k+1][j];
                if(temp<c[i][j]&&fabs(temp-c[i][j])>1E-6)//C++�и�������Ϊ�������ⲻ����ֱ�ӱȽ�
				{
					c[i][j]=temp;
					s[i][j]=k;//k��Ϊ���±�i��j�ĸ��ڵ�
				}
			}
			c[i][j]+=w[i][j];
		}
}
void Construct_Optimal_BST(int i,int j,bool flag)
{
	if(flag==0)
	{
		cout<<"S"<<s[i][j]<<" �Ǹ�"<<endl;
		flag=1;
	}
	int k=s[i][j];
	//�����������Ҷ��
	if(k-1<i)
	{
		cout<<"e"<<k-1<<" is the left child of "<<"S"<<k<<endl;
	}
	//�������������Ҷ��
	else
	{
		cout<<"S"<<s[i][k-1]<<" is the left child of "<<"S"<<k<<endl;
		Construct_Optimal_BST(i,k-1,1);
	}
	//�����������Ҷ��
	if(k>=j)
	{
		cout<<"e"<<j<<" is the right child of "<<"S"<<k<<endl;
	}
	//�������������Ҷ��
	else
	{
		cout<<"S"<<s[k+1][j]<<" is the right child of "<<"S"<<k<<endl;
		Construct_Optimal_BST(k+1,j,1);
	}
}
int main()
{
	cout << "������ؼ��ֵĸ��� n:";
    cin >> n;
    cout<<"����������ÿ���ؼ��ֵ���������:";
    for (i=1; i<=n; i++ )
        cin>>p[i];
    cout << "����������ÿ���������������:";
    for (i=0; i<=n; i++)
        cin>>q[i];
	Optimal_BST();
	// /*���ڲ���
	for(i=1; i<=n+1;i++)
    {
          for (j=1; j<i;j++)
            cout <<"\t" ;
          for(j=i-1;j<=n;j++)
            cout << w[i][j]<<"\t" ;
          cout << endl;
    }
     for(i=1; i<=n+1;i++)
    {
          for (j=1; j<i;j++)
            cout <<"\t" ;
          for(j=i-1; j<=n;j++)
            cout << c[i][j]<<"\t" ;
          cout << endl;
    }
    for(i=1; i<=n;i++)
    {
          for (j=1; j<i;j++)
            cout << "\t" ;
          for(j=i-1; j<=n;j++)
            cout << s[i][j]<<"\t" ;
          cout << endl;
    }
    cout << endl;
    // */���ڲ���
	cout<<"��С�������ɱ�Ϊ:"<<c[1][n]<<endl;
    cout<<"���Ŷ���������Ϊ:";
	Construct_Optimal_BST(1,n,0);
	return 0;
}
