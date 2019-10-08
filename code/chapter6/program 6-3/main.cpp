//program 6-3
#include <iostream>
#include<queue>
#include <iomanip>//I/O������ͷ�ļ�,����C����ĸ�ʽ�����һ��
using namespace std;

typedef struct
{
    int x;
    int y;
} Position;//λ��
int grid[100][100];//��ͼ
bool findpath(Position s,Position e,Position *&path,int &PathLen)
{
    if((s.x==e.x)&&(s.y==e.y))//�ж���ʼλ���Ƿ����Ŀ��λ��
    {
        PathLen=0;
        return true;
    }
    Position DIR[4],here,next;//���巽������DIR[4]����ǰ��here,��һ��next;
    DIR[0].x=0;
    DIR[0].y=1;
    DIR[1].x=1;
    DIR[1].y=0;
    DIR[2].x=0;
    DIR[2].y=-1;
    DIR[3].x=-1;
    DIR[3].y=0;
    here=s;
    grid[s.x][s.y]=0;//��ǳ�ʼΪ0,δ����-1,ǽ��-2
    queue<Position>Q;
    for(;;)
    {
        for(int i=0; i<4; i++)//�ĸ������ǰ��,��������
        {
            next.x=here.x+DIR[i].x;
            next.y=here.y+DIR[i].y;
            if(grid[next.x][next.y]==-1)//��δ����
            {
                grid[next.x][next.y]=grid[here.x][here.y]+1;
                Q.push(next);
            }
            if((next.x==e.x)&&(next.y==e.y))break;//�ҵ�Ŀ��
        }
        if((next.x==e.x)&&(next.y==e.y))break;//�ҵ�Ŀ��
        if(Q.empty()) return false;
        else
        {
            here=Q.front();
            Q.pop();
        }
    }
    PathLen=grid[e.x][e.y];//�����һ���̲��߷���
    path=new Position[PathLen];
    here=e;
    for(int j=PathLen-1; j>=0; j--)
    {
        path[j]=here;
        for(int i=0; i<4; i++)//���ĸ�����Ѱ��,��������
        {
            next.x=here.x+DIR[i].x;
            next.y=here.y+DIR[i].y;
            if(grid[next.x][next.y]==j)break;//�ҵ���ͬ����
        }
        here=next;
    }
    return true;
}

void init(int m,int n)//��Ǵ���0��ʾ�Ѳ���,δ����-1,ǽ��-2
{
    for(int i=1; i<=m; i++)  //�������г�ʼ��Ϊ-1
        for(int j=1; j<=n; j++)
            grid[i][j]=-1;
    for(int i=0; i<=n+1; i++) //������������Χǽ
        grid[0][i]=grid[m+1][i]=-2;
    for(int i=0; i<=m+1; i++) //������������Χǽ
        grid[i][0]=grid[i][n+1]=-2;
}
int main()
{
    Position a,b,*way;
    int Len,m,n;
    cout<<"�����뷽���СM��N"<<endl;
    cin>>m>>n;
    init(m,n);
    while(!(m==0&&n==0))
    {
        cout<<"�������ϰ�������x,y(����0 0����)"<<endl;
        cin>>m>>n;
        grid[m][n]=-2;
    }
    cout<<"�������������:"<<endl;
    cin>>a.x>>a.y;
    cout<<"�������յ�����:"<<endl;
    cin>>b.x>>b.y;
    if(findpath(a,b,way,Len))
    {
        cout<<"�������·���ĳ��ȵ�Ϊ"<<Len<<endl;
        cout<<"���·������Ϊ��"<<endl;
        for(int i=0;i<Len;i++)
            cout<<setw(2)<<way[i].x<<setw(2)<<way[i].y<<endl;//setw(n) �����Ϊn���ַ�
    }
    else cout<<"�����޷����"<<endl;

}
