//program 4-8
#include<iostream>
#include<cmath>   //求绝对值函数需要引入该头文件
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
	for(int t=1;t<=n;t++)//t为关键字的规模
		//从下标为i开始的关键字到下标为j的关键字
		for(i=1;i<=n-t+1;i++)
		{
			j=i+t-1;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			c[i][j]=c[i][i-1]+c[i+1][j];//初始化
			s[i][j]=i;//初始化
			//选取i+1到j之间的某个下标的关键字作为从i到j的根，如果组成的树的期望值当前最小，则k为从i到j的根节点
			for(k=i+1;k<=j;k++)
			{
				double temp=c[i][k-1]+c[k+1][j];
                if(temp<c[i][j]&&fabs(temp-c[i][j])>1E-6)//C++中浮点数因为精度问题不可以直接比较
				{
					c[i][j]=temp;
					s[i][j]=k;//k即为从下标i到j的根节点
				}
			}
			c[i][j]+=w[i][j];
		}
}
void Construct_Optimal_BST(int i,int j,bool flag)
{
	if(flag==0)
	{
		cout<<"S"<<s[i][j]<<" 是根"<<endl;
		flag=1;
	}
	int k=s[i][j];
	//如果左子树是叶子
	if(k-1<i)
	{
		cout<<"e"<<k-1<<" is the left child of "<<"S"<<k<<endl;
	}
	//如果左子树不是叶子
	else
	{
		cout<<"S"<<s[i][k-1]<<" is the left child of "<<"S"<<k<<endl;
		Construct_Optimal_BST(i,k-1,1);
	}
	//如果右子树是叶子
	if(k>=j)
	{
		cout<<"e"<<j<<" is the right child of "<<"S"<<k<<endl;
	}
	//如果右子树不是叶子
	else
	{
		cout<<"S"<<s[k+1][j]<<" is the right child of "<<"S"<<k<<endl;
		Construct_Optimal_BST(k+1,j,1);
	}
}
int main()
{
	cout << "请输入关键字的个数 n:";
    cin >> n;
    cout<<"请依次输入每个关键字的搜索概率:";
    for (i=1; i<=n; i++ )
        cin>>p[i];
    cout << "请依次输入每个虚结点的搜索概率:";
    for (i=0; i<=n; i++)
        cin>>q[i];
	Optimal_BST();
	// /*用于测试
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
    // */用于测试
	cout<<"最小的搜索成本为:"<<c[1][n]<<endl;
    cout<<"最优二叉搜索树为:";
	Construct_Optimal_BST(1,n,0);
	return 0;
}
