/**
* @Name: RoutinePlanning
* @Version: 1.0
* @Auther: Wang Yaoyong
* @Date&Time: 2021-1-1
* @TODO: ����·��,�ж�·�߿�����,���¹滮·��,����¹滮�Ŀ���·��
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

/* ���ڸ���ϰ��,��Դ��������ӽ� C ����,������ýṹ����Ƕ��� */

struct Po  //��,�洢·����ÿһ����ĺ�������
{
    int x;  //������,�� 0 ��ʼ
    int y;  //������,�� 0 ��ʼ
};

struct MAP  //��ͼ,���ڴ洢��ͼ������Ϣ���������
{
    int m,n;  //��ͼ��СΪ m*n,�±�� 0 ��ʼ

    int x1,y1,x2,y2;  //����յ�����

    int abstacleNum;  //�ϰ�������

    int Map[1000][1000];  //��ά����洢��ͼ������Ϣ

    void setSize(void)  //�����ͼ��С
    {
        int t1,t2;
        scanf("%dx%d",&t1,&t2);  //�����ʽΪ mxn ,m��n֮������ĸx����
        fflush(stdin);          //��ջ�����
        m = t1;
        n = t2;
    }

    void setBE(void)  //��������յ�����
    {
        int t1,t2,t3,t4;
        scanf("[%d,%d]",&t1,&t2);
        fflush(stdin);  //��ջ�����
        scanf("[%d,%d]",&t3,&t4);
        fflush(stdin);  //��ջ�����
        x1 = t1;
        y1 = t2;
        x2 = t3;
        y2 = t4;
    }

    void initMap(void)  //��ʼ����ͼ��Ϣ,ȫ���� 0
    {
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                Map[i][j] = 0;  //��·��Ϊ 0
    }

    void setAbstacle(void)  //�����ϰ�����
    {
        abstacleNum = 0;
        while(1)
        {
            int t1,t2;
            char t[20];
            scanf("%s",t);
            fflush(stdin);
            if(strcmp(t,"$") == 0) //���ַ� $ ����
                break;
            sscanf(t,"[%d,%d]",&t1,&t2);
            Map[t1][t2] = -1;  // �ϰ����Ϊ -1
            ++abstacleNum;
        }
    }

    void print(void)  //��ӡ��ͼ
    {
        printf("  ");
        for(int i = 0; i < n; ++i)
            printf("%d ",i);  //��ӡ�����ͷ����
        printf("\n");
        for(int i = 0; i < m; ++i)
        {
            printf("%d ",i);  //��ӡ�����ͷ����
            for(int j = 0; j < n; ++j)
            {
                if(i == x1 && j == y1)  //�������
                {
                    printf("I ");
                    continue;
                }
                if(i == x2 && j == y2)  //�յ�����
                {
                    printf("G ");
                    continue;
                }
                if(Map[i][j] == 0)  //��·�ʹ�ӡ�ո�
                    printf("  ");
                else if(Map[i][j] == 1)  //·�߾ʹ�ӡ *
                    printf("* ");
                else
                    printf("# ");  //�ϰ��ʹ�ӡ #
            }
            printf("\n");
        }
    }
}myMap;

struct Route  //·��
{
    int n;  //�洢·�߳���
    struct Po li[2000];  //�洢·����ÿ����,�� 1 ��ʼ

    void initRoute()  //����·��
    {
        n=0;
        //��ʼ����·��
        char t[20];
        while(1)
        {
            //������һ���ַ���
            scanf("%s",t);
            fflush(stdin);
            //�ж������һ�а�����������
            int tt = 0;
            for(int i = 0; i < strlen(t); ++i)
                if(t[i] == '[')  //�����ַ� '[' �����ж��������
                    ++tt;
            if(tt == 1)  //ֻ��һ����������
            {
                int t1,t2;
                sscanf(t,"[%d,%d]",&t1,&t2);
                li[++n].x = t1;
                li[n].y = t2;
                break; //ֻ��һ������,˵������϶�������
            }
            //��������������
            int t1,t2,t3,t4;
            sscanf(t,"[%d,%d]->[%d,%d]->",&t1,&t2,&t3,&t4);
            //��ÿ���������������������·��
            li[++n].x = t1;
            li[n].y = t2;
            li[++n].x = t3;
            li[n].y = t4;
            //������յ�,�ͽ�������
            if(t3 == myMap.x2 && t4 == myMap.y2)
                break;
        }
    }

    void initRouteinMap()  //��·����Ϣ�����ͼ��
    {
        for(int i = 1; i < n+1; ++i)
        {
            int x = li[i].x;
            int y = li[i].y;
            if(myMap.Map[x][y] == 0)
                myMap.Map[x][y] = 1;
        }
    }

    bool judgeInit(void)  //�ж�����Ƿ���ȷ
    {
        if(li[1].x != myMap.x1 || li[1].y != myMap.y1)
            return true;
        return false;
    }

    bool judgeGoal(void)  //�ж��յ��Ƿ���ȷ
    {
        if(li[n].x != myMap.x2 || li[n].y != myMap.y2)
            return true;
        return false;
    }

    bool judgeFuckinMove(void)  //�ж��Ƿ��зǷ��ƶ�
    {
        for(int i = 1; i < n; ++i)
        {
            int d = abs(li[i].x - li[i+1].x) + abs(li[i].y - li[i+1].y);
            if(d != 1)
                return true;
        }
        return false;
    }

    bool judgeAbstacle(void)  //�ж�·���Ƿ񾭹��ϰ���
    {
        for(int i= 1; i < n+1; ++i)
            if(myMap.Map[li[i].x][li[i].y] == -1)
                return true;
        return false;
    }
}route;


void Stage0(void)  //��ӡ�� 0 �׶�����
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

//������������㷨Ѱ·
bool flag = false;  //�����ж��Ƿ�������ѵݹ�
bool b[1000][1000];  //���߲�ͨ�ĵ���

void dfs(int n,int x,int y,int x0,int y0) //�ֱ��ʾ:Ѱ·�����š���ǰ��������ꡢ�յ��������
{
    if(flag)
        return;

    if(!b[x][y])
        return;

    route.li[n].x = x;
    route.li[n].y = y;
    b[x][y] = false;

    //����ߵ��յ���,����Ѱ·
    if(x == x0 && y == y0)
    {
        flag = true;
        return;
    }

    //������
    if(myMap.Map[x+1][y] != -1 && x+1 < myMap.m && b[x+1][y])
    {
        //cout<<n<<"\tDown in\n";
        dfs(n+1,x+1,y,x0,y0);
        //cout<<n<<"\tDown out\n";
        if(flag)
            return;
    }
    //������
    if(myMap.Map[x][y-1] != -1 && y-1 >= 0 && b[x][y-1])
    {
        //cout<<n<<"\tLeft in\n";
        dfs(n+1,x,y-1,x0,y0);
        //cout<<n<<"\tLeft out\n";
        if(flag)
            return;
    }
    //������
    if(myMap.Map[x][y+1] != -1 && y+1 < myMap.n && b[x][y+1])
    {
        //cout<<n<<"\tRight in\n";
        dfs(n+1,x,y+1,x0,y0);
        //cout<<n<<"\tRight out\n";
        if(flag)
            return;
    }
    //������
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

void Corection(void)  //�޸�·��
{
    //ȷ��Ѱ·�����յ�
    int beg;
    int beg_x,beg_y;
    //ԭ�����յ�ΪѰ·�յ�
    int end_x = myMap.x2, end_y = myMap.y2;
    for(int i= 1; i < route.n+1; ++i)
    {
        int x = route.li[i].x;
        int y = route.li[i].y;
        if(myMap.Map[x-1][y] == -1 || myMap.Map[x+1][y] == -1
           || myMap.Map[x][y-1] == -1 || myMap.Map[x][y+1] == -1)  //��һ������·�ߵ��ǰһ����ΪѰ·���
        {
            beg = i;  //Ѱ·�������
            beg_x = route.li[i].x;
            beg_y = route.li[i].y;
            break;
        }
    }
    //Ѱ·Ԥ����
    for(int i = beg; i < 2000; ++i)//Ѱ·����Ѱ·�յ�֮���ԭ���ĵ�ȫ������
    {
        route.li[i].x = -1;
        route.li[i].y = -1;
    }
    //Ĭ�����еĵ㶼����
    for(int i = 0; i < myMap.m; ++i)
        for(int j = 0; j < myMap.n; ++j)
            b[i][j] = true;
    //�Ѿ��߹���·����ԭ·����
    for(int i = 1; i < beg; ++i)
        b[route.li[i].x][route.li[i].y]=false;
    //��ʼѰ·
    dfs(beg,beg_x,beg_y,end_x,end_y);
    //����ȷ��·�߳���
    int sum=0;
    for(int i = 1;; ++i)
    {
        if(route.li[i].x == -1 || route.li[i].y == -1)
            break;
        ++sum;
    }
    route.n = sum;
}

void Stage1(void)  //��ӡ�� 1 �׶�����
{
    printf("\n");
    printf("==STAGE 1=======================================\n\n");
    myMap.print();
    if(!route.judgeAbstacle())
        return;
    printf("\n------------------------------------------------\n\n");
    Corection();  //�޸�·��
    //�����·��
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
    myMap.setSize();  //�����ͼ��С
    myMap.initMap();  //��ʼ����ͼ��Ϣ
    myMap.setBE();  //���������յ�
    myMap.setAbstacle();  //�����ϰ���
    route.initRoute();  //�����ʼ·��
    route.initRouteinMap();  //�ѳ�ʼ·������Ϣ�����ͼ
    Stage0();  //�� 0 �׶����
    Stage1();  //�� 1 �׶����
    //�������
    system("pause");
    return 0;
}
