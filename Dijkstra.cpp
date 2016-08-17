#include"stdafx.h"
#include"Dijkstra.h"
#include <float.h>  
#include<iostream>

//Dijkstra最短路径算法实现
void Dijkstra(int v, int graphsize, float *dist ,int *prev ,float **graph)
{
	//这里的逻辑过程很有意思
	bool *s=new bool[graphsize];//判断是否将该点存入到s集合中
	int narray=graphsize-1,varray=v-1;	//转换为数组的编号是从0开始
	for(int i = 0;i <= narray;++i)
	{
		dist[i]=graph[v][i];
		s[i] = false;

		//所有能够由初始点直接到达的点都标号
		if(dist[i] == FLT_MAX)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = true;
 
    // 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
    // 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
	for(int i=1;i<=narray;++i)
	{
		float tmp = FLT_MAX;
		int u = v; //v到下一个点的最小值
		
		//取最小的dist
		for(int j=0;j < narray; ++j)
		{
			if(!s[j]&&dist[j]<tmp)
			{
				u = j;
				tmp = dist[j];
			}
		}
		s[u] = true;

		//更新dist
		for(int j=0;j<=narray;++j)
		{
			if(!s[j] && graph[u][j] < FLT_MAX)
			{
				float newdist = dist[u] + graph[u][j];
				if(newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
		}
	}
}

//路径回溯过程
void PathRecall(int *prev,int v,int u,int graphsize)
{
	int *que=new int[graphsize+1];
	int tot = 0;
	int tmp = prev[u];
	while(tmp != v&&tot<graphsize)
	{
		que[tot] = tmp;
		tot++;
		tmp = prev[tmp];
	}
	que[tot] = v;
	for(int i=tot; i>=0; --i)
        if(i != 1)
           std::cout << que[i] << " -> ";
        else
           std::cout << que[i] << std::endl;
}