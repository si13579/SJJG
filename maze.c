#include "maze.h"
//#include<sys/types.h>
//#include<sys/wait.h>
/*
迷宫寻路
使用穷举法，找到一条可行通道即返回
*/
Status MazePath(MazeType maze, PosType start, PosType end)
{
    SqStack S;
    SElemType e;
    PosType curPos;
    int curStep;

    InitStack(&S);

    curPos = start;
    curStep = 1;

    do
    {
        if (Pass(maze, curPos))
        {
            FootPrint(maze, curPos);
            e = Construct(curStep, curPos, East);
            Push(&S, e);
            //printf("%d %d\n",curPos.x,curPos.y);
            if (Equals(e.seat, end) == TRUE)
            {
                printf("\n寻路成功！！\n\n");
                return TRUE;
            }

            curPos = NextPos(curPos, East);
            curStep++;
        }
        else
        {
            if (!StackEmpty(S))
            {
                Pop(&S, &e);
                while (e.di == North && !StackEmpty(S))
                {
                    MarkPrint(maze, e.seat, Impasse);
                    Pop(&S, &e);
                }

                if (e.di < North)
                {
                    ++e.di;
                    MarkPrint(maze, e.seat, e.di);
                    Push(&S, e);
                    curPos = NextPos(e.seat, e.di);
                }
            }
        }
    } while (!StackEmpty(S));
    printf("\n寻路失败！！\n\n");

    return FALSE;
}
/*
初始化一个规模为M*N的迷宫
start和end分别为迷宫的入口坐标和出口坐标
*/
void InitMaze(MazeType maze, PosType *start, PosType *end)
{
    int i, j, tmp;
    srand((unsigned)time(0));

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
            {
                maze[i][j] = Wall;
            }
            else
            {
                tmp = rand() % X;
                if (!tmp)
                    maze[i][j] = Obstacle;
                else
                    maze[i][j] = Way;
            }
        }
    }
    start->x = 1;
    start->y = 1;

    end->x = M - 2;
    end->y = N - 2;

    maze[1][1] = maze[M - 2][N - 2] = Way;
    //maze[1][2] = maze[M - 2][N - 2] = Way;
    PaintMaze(maze);
}

/*
判断当前位置是否可通过：要求该位置是从未曾探索的通道块
可理解为判断当前位置是否为首次探索
*/
Status Pass(MazeType maze, PosType seat)
{
    int x = seat.x;
    int y = seat.y;

    if (x < 0 || y < 0 || x > M - 1 || y > N - 1)
        return FALSE;
    if (maze[x][y] != Way)
        return FALSE;
    return TRUE;
}

/*
获取下一个应当探索的位置
di指示当前所处位置的探索方向，包括East，South，West，North
*/
PosType NextPos(PosType seat, int di)
{
    PosType tmp = seat;
    /*
    switch (di)
    {
    case East:
        tmp.x++;
        break;
    case South:
        tmp.y--;
        break;
    case West:
        tmp.x--;
        break;
    case North:
        tmp.y++;
        break;
    }
    */
   switch(di) {
        case East:
            tmp.y++;            //向东
            break;
        case South:
            tmp.x++;            //向南
            break;
        case West:
            tmp.y--;            //向西
            break;
        case North:
            tmp.x--;            //向北
            break;
    }
    return tmp;
}

/*
留下初始访问足迹
初始访问足迹即向东访问
*/
void FootPrint(MazeType maze, PosType seat)
{
    MarkPrint(maze, seat, East);
}

/*
在迷宫的seat位置处留下mark标记
*/
void MarkPrint(MazeType maze, PosType seat, int mark)
{
    int x = seat.x;
    int y = seat.y;

    maze[x][y] = mark;

    PaintMaze(maze);
}

/*
构造一个通道块信息并返回
*/
SElemType Construct(int ord, PosType seat, int di)
{
    SElemType e;
    e.ord = ord;
    e.seat = seat;
    e.di = di;

    return e;
}

/*
判断两个坐标是否相等
*/
Status Equals(PosType a, PosType b)
{
    if (a.x == b.x && a.y == b.y)
        return TRUE;
    else
        return ERROR;
}
/*
 * 函数暂停一段时间。
 *
 * time不代表具体的时间，只是代表一段时间间隔，
 * 通过调节time的大小，可以使程序暂停适当的时间后继续运行。
 */
void Wait(long time) {
    double i;
    
    if(time<0) {
        time = -time;
    }
    
    for(i = 0.01; i <= 100000.0 * time; i += 0.01) {
        // 空循环
    }
}
/*
绘制迷宫
以图形的方式呈现迷宫当前的状态
*/
void PaintMaze(MazeType maze)
{
    int i, j;

    Wait(SleepTime); // 暂停一下

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (maze[i][j] == Wall)
            { // 外墙
                printf("*");
            }
            else if (maze[i][j] == Obstacle)
            { // 迷宫内部的障碍
                printf("●");
            }
            else if (maze[i][j] == East)
            { // 正在朝东探索
                printf("▷");
            }
            else if (maze[i][j] == South)
            { // 正在朝南探索
                printf("▽");
            }
            else if (maze[i][j] == West)
            { // 正在朝西探索
                printf("◁");
            }
            else if (maze[i][j] == North)
            { // 正在朝北探索
                printf("△");
            }
            else if (maze[i][j] == Impasse)
            { // 死胡同，即四个方向都探索过，但无法通过的位置
                printf("x");
            }
            else
            { // 还未探索过的路径结点
                printf(" ");
            }

            if (j != 0 && j % (N - 1) == 0)
            { // 每隔N个结点换行
                printf("\n");
            }
        }
    }

    printf("\n");
}