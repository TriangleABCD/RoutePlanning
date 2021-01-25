/**
* @Name: RoutinePlanning
* @Version: 1.0
* @Auther: TriangleABCD
* @Date&Time: 2021-1-1
* @TODO: 输入路线,判断路线可行性,重新规划路线,输出新规划的可行路线
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

struct Po  //点,存储路线上每一个点的横纵坐标
{
    int x;  //横坐标,从 0 开始
    int y;  //纵坐标,从 0 开始
};

struct MAP  //地图,用于存储地图基本信息和最终输出
{
    int m,n;  //地图大小为 m*n,下标从 0 开始

    int x1,y1,x2,y2;  //起点终点坐标

    int abstacleNum;  //障碍块数量

    int Map[1000][1000];  //二维数组存储地图基本信息

    void setSize(void)  //读入地图大小
    {
        int t1,t2;
        scanf("%dx%d",&t1,&t2);  //输入格式为 mxn ,m和n之间用字母x连接
        fflush(stdin);          //清空缓冲区
        m = t1;
        n = t2;
    }

    void setBE(void)  //读入起点终点坐标
    {
        int t1,t2,t3,t4;
        scanf("[%d,%d]",&t1,&t2);
        fflush(stdin);  //清空缓冲区
        scanf("[%d,%d]",&t3,&t4);
        fflush(stdin);  //清空缓冲区
        x1 = t1;
        y1 = t2;
        x2 = t3;
        y2 = t4;
    }

    void initMap(void)  //初始化地图信息,全部归 0
    {
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                Map[i][j] = 0;  //道路记为 0
    }

    void setAbstacle(void)  //读入障碍坐标
    {
        abstacleNum = 0;
        while(1)
        {
            int t1,t2;
            char t[20];
            scanf("%s",t);
            fflush(stdin);
            if(strcmp(t,"$") == 0) //以字符 $ 结束
                break;
            sscanf(t,"[%d,%d]",&t1,&t2);
            Map[t1][t2] = -1;  // 障碍物记为 -1
            ++abstacleNum;
        }
    }

    void print(void)  //打印地图
    {
        printf("  ");
        for(int i = 0; i < n; ++i)
            printf("%d ",i);  //打印横向表头数字
        printf("\n");
        for(int i = 0; i < m; ++i)
        {
            printf("%d ",i);  //打印纵向表头数字
            for(int j = 0; j < n; ++j)
            {
                if(i == x1 && j == y1)  //起点特判
                {
                    printf("I ");
                    continue;
                }
                if(i == x2 && j == y2)  //终点特判
                {
                    printf("G ");
                    continue;
                }
                if(Map[i][j] == 0)  //道路就打印空格
                    printf("  ");
                else if(Map[i][j] == 1)  //路线就打印 *
                    printf("* ");
                else
                    printf("# ");  //障碍就打印 #
            }
            printf("\n");
        }
    }
}myMap;

struct Route  //路线
{
    int n;  //存储路线长度
    struct Po li[2000];  //存储路线上每个点,从 1 开始

    void initRoute()  //输入路线
    {
        n=0;
        //开始输入路线
        char t[20];
        while(1)
        {
            //先输入一个字符串
            scanf("%s",t);
            fflush(stdin);
            //判断输入的一行包含几个坐标
            int tt = 0;
            for(int i = 0; i < strlen(t); ++i)
                if(t[i] == '[')  //根据字符 '[' 数量判断坐标个数
                    ++tt;
            if(tt == 1)  //只有一个坐标的情况
            {
                int t1,t2;
                sscanf(t,"[%d,%d]",&t1,&t2);
                li[++n].x = t1;
                li[n].y = t2;
                break; //只有一个坐标,说明输入肯定结束了
            }
            //有两个坐标的情况
            int t1,t2,t3,t4;
            sscanf(t,"[%d,%d]->[%d,%d]->",&t1,&t2,&t3,&t4);
            //把每行输入的两个点的坐标存入路线
            li[++n].x = t1;
            li[n].y = t2;
            li[++n].x = t3;
            li[n].y = t4;
            //如果是终点,就结束输入
            if(t3 == myMap.x2 && t4 == myMap.y2)
                break;
        }
    }

    void initRouteinMap()  //把路线信息存入地图类
    {
        for(int i = 1; i < n+1; ++i)
        {
            int x = li[i].x;
            int y = li[i].y;
            if(myMap.Map[x][y] == 0)
                myMap.Map[x][y] = 1;
        }
    }

    bool judgeInit(void)  //判断起点是否正确
    {
        if(li[1].x != myMap.x1 || li[1].y != myMap.y1)
            return true;
        return false;
    }

    bool judgeGoal(void)  //判断终点是否正确
    {
        if(li[n].x != myMap.x2 || li[n].y != myMap.y2)
            return true;
        return false;
    }

    bool judgeFuckinMove(void)  //判断是否有非法移动
    {
        for(int i = 1; i < n; ++i)
        {
            int d = abs(li[i].x - li[i+1].x) + abs(li[i].y - li[i+1].y);
            if(d != 1)
                return true;
        }
        return false;
    }

    bool judgeAbstacle(void)  //判断路线是否经过障碍块
    {
        for(int i= 1; i < n+1; ++i)
            if(myMap.Map[li[i].x][li[i].y] == -1)
                return true;
        return false;
    }
}route;


void Stage0(void)  //打印第 0 阶段内容
{
    printf("\n");
    printf("==STAGE 0=======================================\n");
    printf("The grid has %d rows and %d columns.\n",myMap.m,myMap.n);
    printf("the grid has %d block(s).\n",myMap.abstacleNum);
    printf("The initial cell in the grid is [%d,%d].\n",myMap.x1,myMap.y1);
    printf("The goal cell in the grid is [%d,%d].\n",myMap.x2,myMap.y2);
    printf("The proposed route in the grid is:\n");
    for(int i = 1; i < route.n + 1; ++i)
    {
        if( i == route.n)
        {
            printf("[%d,%d].",route.li[i].x,route.li[i].y);
            break;
        }
        printf("[%d,%d]->",route.li[i].x,route.li[i].y);
        if(i % 5 == 0)
            printf("\n");
    }
    printf("\n");

    bool flag = true;
    if(route.judgeInit())
    {
        flag = false;
        printf("Initial cell in the route is wrong!\n");
        return;
    }
    if(route.judgeGoal())
    {
        flag = false;
        printf("Goal cell in the route is wrong!\n");
        return;
    }
    if(route.judgeFuckinMove())
    {
        flag = false;
        printf("There is an illegal move in this route!\n");
        return;
    }
    if(route.judgeAbstacle())
    {
        flag = false;
        printf("There is a block on this route!\n");
        return;
    }
    if(flag)
        printf("The route is valid!\n");
}

//深度优先搜索算法寻路
bool flag = false;  //用于判断是否结束深搜递归
bool b[1000][1000];  //将走不通的点标记

void dfs(int n,int x,int y,int x0,int y0) //分别表示:寻路起点序号、当前点横纵坐标、终点横纵坐标
{
    if(flag)
        return;

    if(!b[x][y])
        return;

    route.li[n].x = x;
    route.li[n].y = y;
    b[x][y] = false;

    //如果走到终点了,结束寻路
    if(x == x0 && y == y0)
    {
        flag = true;
        return;
    }

    //向下走
    if(myMap.Map[x+1][y] != -1 && x+1 < myMap.m && b[x+1][y])
    {
        //cout<<n<<"\tDown in\n";
        dfs(n+1,x+1,y,x0,y0);
        //cout<<n<<"\tDown out\n";
        if(flag)
            return;
    }
    //向左走
    if(myMap.Map[x][y-1] != -1 && y-1 >= 0 && b[x][y-1])
    {
        //cout<<n<<"\tLeft in\n";
        dfs(n+1,x,y-1,x0,y0);
        //cout<<n<<"\tLeft out\n";
        if(flag)
            return;
    }
    //向右走
    if(myMap.Map[x][y+1] != -1 && y+1 < myMap.n && b[x][y+1])
    {
        //cout<<n<<"\tRight in\n";
        dfs(n+1,x,y+1,x0,y0);
        //cout<<n<<"\tRight out\n";
        if(flag)
            return;
    }
    //向上走
    if(myMap.Map[x-1][y] != -1 && x-1 >= 0 && b[x-1][y])
    {
        //cout<<n<<"\tUp in\n";
        dfs(n+1,x-1,y,x0,y0);
        //cout<<n<<"\tUp out\n";
        if(flag)
            return;
    }
    route.li[n].x = -1;
    route.li[n].y = -1;
    b[x][y] = false;
    return;
}

void Corection(void)  //修复路线
{
    //确定寻路起点和终点
    int beg;
    int beg_x,beg_y;
    //原来的终点为寻路终点
    int end_x = myMap.x2, end_y = myMap.y2;
    for(int i= 1; i < route.n+1; ++i)
    {
        int x = route.li[i].x;
        int y = route.li[i].y;
        if(myMap.Map[x-1][y] == -1 || myMap.Map[x+1][y] == -1
           || myMap.Map[x][y-1] == -1 || myMap.Map[x][y+1] == -1)  //第一个遇障路线点的前一个点为寻路起点
        {
            beg = i;  //寻路起点的序号
            beg_x = route.li[i].x;
            beg_y = route.li[i].y;
            break;
        }
    }
    //寻路预处理
    for(int i = beg; i < 2000; ++i)//寻路起点和寻路终点之间的原本的点全部作废
    {
        route.li[i].x = -1;
        route.li[i].y = -1;
    }
    //默认所有的点都可走
    for(int i = 0; i < myMap.m; ++i)
        for(int j = 0; j < myMap.n; ++j)
            b[i][j] = true;
    //已经走过的路不可原路返回
    for(int i = 1; i < beg; ++i)
        b[route.li[i].x][route.li[i].y]=false;
    //开始寻路
    dfs(beg,beg_x,beg_y,end_x,end_y);
    //重新确认路线长度
    int sum=0;
    for(int i = 1;; ++i)
    {
        if(route.li[i].x == -1 || route.li[i].y == -1)
            break;
        ++sum;
    }
    route.n = sum;
}

void Stage1(void)  //打印第 1 阶段内容
{
    printf("\n");
    printf("==STAGE 1=======================================\n\n");
    myMap.print();
    if(!route.judgeAbstacle())
        return;
    printf("\n------------------------------------------------\n\n");
    Corection();  //修复路线
    //输出新路线
    for(int i = 0; i < myMap.m; ++i)
        for(int j = 0; j <myMap.n; ++j)
            if(myMap.Map[i][j] == 1)
                myMap.Map[i][j] = 0;
    route.initRouteinMap();
    myMap.print();
}

int main()
{
    system("color 4e");
    myMap.setSize();  //输入地图大小
    myMap.initMap();  //初始化地图信息
    myMap.setBE();  //输入起点和终点
    myMap.setAbstacle();  //输入障碍块
    route.initRoute();  //输入初始路径
    route.initRouteinMap();  //把初始路径的信息存入地图
    Stage0();  //第 0 阶段输出
    Stage1();  //第 1 阶段输出
    //程序结束
    system("pause");
    return 0;
}
