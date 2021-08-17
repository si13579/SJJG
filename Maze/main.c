#include"maze.h"
int main(int argc, char * argv[]){
    MazeType maze;
    PosType start,end;
    char n,Re = 'Y';
    while (Re == 'Y' || Re == 'y'){
        InitMaze(maze,&start,&end);
        MazePath(maze,start,end);
        printf("重置？（Y/N) : ");
        scanf("%c%c",&Re,&n);
        printf("\n");
    }
    return 0;
}