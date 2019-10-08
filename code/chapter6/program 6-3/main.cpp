//program 6-3
#include <iostream>
#include<queue>
#include <iomanip>//I/O流控制头文件,就像C里面的格式化输出一样
using namespace std;

typedef struct
{
    int x;
    int y;
} Position;//位置
int grid[100][100];//地图
bool findpath(Position s,Position e,Position *&path,int &PathLen)
{
    if((s.x==e.x)&&(s.y==e.y))//判定开始位置是否就是目标位置
    {
        PathLen=0;
        return true;
    }
    Position DIR[4],here,next;//定义方向数组DIR[4]，当前格here,下一格next;
    DIR[0].x=0;
    DIR[0].y=1;
    DIR[1].x=1;
    DIR[1].y=0;
    DIR[2].x=0;
    DIR[2].y=-1;
    DIR[3].x=-1;
    DIR[3].y=0;
    here=s;
    grid[s.x][s.y]=0;//标记初始为0,未布线-1,墙壁-2
    queue<Position>Q;
    for(;;)
    {
        for(int i=0; i<4; i++)//四个方向的前进,右下左上
        {
            next.x=here.x+DIR[i].x;
            next.y=here.y+DIR[i].y;
            if(grid[next.x][next.y]==-1)//尚未布线
            {
                grid[next.x][next.y]=grid[here.x][here.y]+1;
                Q.push(next);
            }
            if((next.x==e.x)&&(next.y==e.y))break;//找到目标
        }
        if((next.x==e.x)&&(next.y==e.y))break;//找到目标
        if(Q.empty()) return false;
        else
        {
            here=Q.front();
            Q.pop();
        }
    }
    PathLen=grid[e.x][e.y];//逆向找回最短布线方案
    path=new Position[PathLen];
    here=e;
    for(int j=PathLen-1; j>=0; j--)
    {
        path[j]=here;
        for(int i=0; i<4; i++)//沿四个方向寻找,右下左上
        {
            next.x=here.x+DIR[i].x;
            next.y=here.y+DIR[i].y;
            if(grid[next.x][next.y]==j)break;//找到相同数字
        }
        here=next;
    }
    return true;
}

void init(int m,int n)//标记大于0表示已布线,未布线-1,墙壁-2
{
    for(int i=1; i<=m; i++)  //方格阵列初始化为-1
        for(int j=1; j<=n; j++)
            grid[i][j]=-1;
    for(int i=0; i<=n+1; i++) //方格阵列上下围墙
        grid[0][i]=grid[m+1][i]=-2;
    for(int i=0; i<=m+1; i++) //方格阵列左右围墙
        grid[i][0]=grid[i][n+1]=-2;
}
int main()
{
    Position a,b,*way;
    int Len,m,n;
    cout<<"请输入方阵大小M，N"<<endl;
    cin>>m>>n;
    init(m,n);
    while(!(m==0&&n==0))
    {
        cout<<"请输入障碍物坐标x,y(输入0 0结束)"<<endl;
        cin>>m>>n;
        grid[m][n]=-2;
    }
    cout<<"请输入起点坐标:"<<endl;
    cin>>a.x>>a.y;
    cout<<"请输入终点坐标:"<<endl;
    cin>>b.x>>b.y;
    if(findpath(a,b,way,Len))
    {
        cout<<"该条最短路径的长度的为"<<Len<<endl;
        cout<<"最佳路径坐标为："<<endl;
        for(int i=0;i<Len;i++)
            cout<<setw(2)<<way[i].x<<setw(2)<<way[i].y<<endl;//setw(n) 设域宽为n个字符
    }
    else cout<<"任务无法达成"<<endl;

}
