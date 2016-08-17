#pragma once
#include <limits.h> 

//Dijkstra算法，用一个二维数组表示一个有向图结构，任意两个顶点之间边的权重为数组的值，若两边不可到达，则值为0
//v为起始节点，graphsize为节点个数
//dist为点v到各个目标点的最小距离
//prev为各个目标点到点v的回溯过程
//graph为有向图矩阵
void Dijkstra(int v, int graphsize, float *dist ,int *prev ,float **graph);

//最短路径回溯
//v为初始点，u为目标点
void PathRecall(int *prev,int v,int u,int graphsize);
