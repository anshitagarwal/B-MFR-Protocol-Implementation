#include "graphics.h"
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define RADI 125

int points[100][2];
int dist[25][25];
int k;
int path[25];

int distance(int x1,int y1,int x2,int y2)
{
      return (int)sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}


void printscreen()
{
     char str[5];
     //cleardevice();
     for(int i=0; i<25; i++)
    {
             circle(points[i][0],points[i][1],3);
             itoa(i+1,str,10);
             outtextxy(points[i][0]+3,points[i][1]+3,str);
    }     
}
void drawgraphics(int x1,int y1,int x2,int y2, int rad)
{
     int x=RADI;
     while(x!=rad)
     {
                  //printscreen();
                  setcolor(15);                  
                  circle(x1,y1,x);
                  printscreen();
                  delay(15);
                  setcolor(0);    
                  setfillstyle(EMPTY_FILL ,0);              
                  circle(x1,y1,x);
                  x--;
     }
           setcolor(15);
           printscreen();                  
           line(x1,y1,x2,y2);
           //circle(x1,y1,rad);
           delay(100);
}
void getpath(int start,int end,int rad)
{
     int flag,current=start,min,prev;
     path[0]=start+1;
     k=1;
     while (current!=end)
     {
           rad=RADI;
           flag=1;
           prev=current;
           while (flag)
           {
                 min=1000;
                 for (int i=0;i<25;i++)
                 {
                     if (rad==dist[current][i]&&dist[current][end]>dist[i][end])
                     {
                        flag=0;
                    
                        if (min>dist[i][end])
                        {
                           min=dist[i][end];
                           current=i;
                        }
                     }
                 }
                 rad--;
                 if(rad<0)
                 {
                          printf("\nNo Node found in Radius.\n");
                          return;
                 }
           }
           path[k]=current+1;
           drawgraphics(points[prev][0],points[prev][1],points[current][0],points[current][1],rad+1);
           k++;
     }
}
int main()
{   
    initwindow(640,480,"B-MFR Routing Protocol");
    srand (time(NULL));
    
    for(int i=0; i<25; i++)
    {
             points[i][0]= rand() % 550 + 50;
             points[i][1]= rand() % 400 + 50;
    }
    printscreen();
    
    for(int i=0; i<25; i++)
    {
            for(int j=0; j<25; j++)
            {
                    dist[i][j]=distance(points[i][0],points[i][1],points[j][0],points[j][1]);
            }
    }
    
    int start,end;
    printf("Enter start:");
    scanf("%d",&start);
    printf("Enter end:");
    scanf("%d",&end);
    start--;
    end--;
    
    getpath(start,end,RADI);
    printf("\n");
    printf("%d ",path[0]);
    for(int i=1;i<k;i++)
    {
            printf("%d ",path[i]);
            line(points[path[i-1]-1][0],points[path[i-1]-1][1],points[path[i]-1][0],points[path[i]-1][1]);
    }
    getche();
}

