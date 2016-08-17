#pragma once

//A*算法与Dijkstra有相似点也有区别，对于Dijkstra，最主要的应用在于对于图这类数据结构的路径寻找
//对于一个平面地图来说，实际上我们可以将其看作栅格数据而不是矢量数据
//在此情况下使用Dijkstra算法算法比较复杂，且内存开销太大，并不太适用

//首先定义一些常量
#define blocked -1		//不可通过节点
#define unblocked 0		//可通过节点

#define movestraight 1	//水平或竖直移动
#define movetilt 1.414	//斜向移动

typedef struct IPOINT
{
	int x;
	int y;
}A_Point;

//A*算法 其中pntSt为起始目标点 pntDst为终止目标点
//xsize ,ysize 为图的大小
//dist为选择到的点到初始点的距离
//prev为当前点的父节点
//graph为图结构
void A_Star(A_Point pntSt,A_Point pntDst,int xsize,int ysize,float** dist,int **prev,int **graph);

void PathRecall(A_Point pntSt,A_Point pntDst,int xsize,int ysize,int **prev);