//program 2-6
#include <iostream>
using namespace std;

const int INF = 0x3fffffff;
const int N = 100;
bool s[N];
int closest[N];
int lowcost[N];
void Prim(int n, int u0, int c[N][N])
{    //�������n����ʼ����u0����Ȩ�ڽӾ���C[n][n]
    //���s[i]=true,˵������i�Ѽ�����С������
    //�Ķ��㼯��U�����򶥵�i���ڼ���V-U
    //��������ص���СȨֵ���ݵ�����lowcost
    s[u0]=true; //��ʼʱ��������Uֻ��һ��Ԫ�أ�������u0
    int i;
    int j;
    for(i=1; i<=n; i++)
    {
        if(i!=u0)
        {
            lowcost[i]=c[u0][i];
            closest[i]=u0;
            s[i]=false;
        }
        else
            lowcost[i]=0;
    }

    for(i=1; i<=n;i++) //�ڼ�����V-u��Ѱ�Ҿ��뼯��U����Ķ���t
    {
        int temp=INF;
        int t=u0;
        for(j=1;j<=n;j++)
        {
            if((!s[j])&&(lowcost[j]<temp))
            {
                t=j;
                temp=lowcost[j];
            }
        }
        if(t==u0)
            break;       //�Ҳ���t������ѭ��

        s[t]=true;     //���򣬽�t���뼯��U
        for(j=1; j<=n;j++) //����lowcost��closest
        {
            if((!s[j])&&(c[t][j]<lowcost[j]))
            {
                lowcost[j]=c[t][j];
                closest[j]=t;
            }
        }
    }
}

int main()
{

        int n, c[N][N], m, u, v, w;
        int u0;
        cout<<"��������n�ͱ���m:"<<endl;
        cin>>n>>m;
        int sumcost=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                c[i][j]=INF;
        cout <<"��������u,v�ͱ�ֵw:"<<endl;
        for(int i=1; i<=m; i++)
        {
            cin>>u>>v>>w;
            c[u][v]=c[v][u]=w;
        }
        cout <<"������һ���u0:"<<endl;
        cin >> u0 ;
        //��������lowcos���ܺͣ���Ϊ���Ҫ�����С�ķ���֮��
        Prim(n, u0, c);
        cout <<"����lowcost������Ϊ"<<endl;
        for(int i = 1; i <= n; i++)
            cout << lowcost[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; i++)
           sumcost += lowcost[i];
        cout << "��С�Ļ����ǣ�"<<sumcost<<endl;
    return 0;
}
