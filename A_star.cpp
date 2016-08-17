#include"stdafx.h"
#include"A_star.h"

#include<string>
#include<vector>
#include <float.h> 
#include <limits.h> 


//辅助函数
int   PointToInt(int x,int y,int xsize,int ysize)
{
	return y*xsize+x;
}
void  IntToPoint(int pnt,int xsize,int ysize,int &x,int &y)
{
	x = pnt%xsize;
	y = pnt/xsize;
}
float CalculateF(int cur,int src,int dst,float** dist,int xsize,int ysize)
{
	int curx,cury;
	int dstx,dsty;
	int srcx,srcy;
	
	IntToPoint(cur,xsize,ysize,curx,cury);
	IntToPoint(dst,xsize,ysize,dstx,dsty);
	IntToPoint(src,xsize,ysize,srcx,srcy);

	float G = dist[curx][cury];
	float H = sqrt(float(dstx-curx)*float(dstx-curx)+float(dsty-cury)*float(dsty-cury));
	return G + H;
}

void A_Star(A_Point pntSt,A_Point pntDst,int xsize,int ysize,float** dist,int **prev,int **graph)
{
	bool *s = new bool[xsize*ysize];
	memset(s,0,sizeof(bool)*xsize*ysize);
	for(int i=0;i<xsize;++i)
	{
		for(int j=0;j<ysize;++j)
		{
			dist[i][j] = -1;
			prev[i][j] = -1;
		}
	}

	//采用最简单的做法，不停的遍历吧，实际上如果通过堆的数据结构是不是会更好一些，小根堆
	std::vector<int> wlist;
	wlist.push_back(PointToInt(pntSt.x,pntSt.y,xsize,ysize));
	dist[pntSt.x][pntSt.y] = 0;
	int dst = PointToInt(pntSt.x,pntSt.y,xsize,ysize);
	int src = PointToInt(pntDst.x,pntDst.y,xsize,ysize);
	bool isToDstination = false;
	while(!wlist.empty())
	{
		//找出最小值删除
		std::vector<int>::iterator iter; 
		float min_value = FLT_MAX;
		int index = 0,minindex=0;
		for(iter = wlist.begin();iter!=wlist.end();++iter,++index)
		{
			float cur_value = CalculateF(*iter,src,dst,dist,xsize,ysize);
			if(min_value<cur_value)
			{
				min_value = cur_value;
				minindex = index;
			}
		}

		//四周八个方向寻找
		int x, y;
		s[wlist[minindex]] = true;   
		IntToPoint(wlist[minindex],xsize,ysize,x,y);
		wlist.erase(wlist.begin()+minindex);

		//判断当前点是不是终点如果是则直接退出
		if(wlist[minindex]==dst)
			break;
		if(x-1 >= 0&&y -1 >= 0&&graph[x-1][y-1] != blocked )
		{
			//第一个判断是判断是否该点已经在等待列表中，如果已经存在则不需要再次进入栈空间中
			if(s[PointToInt(x-1,y-1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x-1,y-1,xsize,ysize));
				s[PointToInt(x-1,y-1,xsize,ysize)] = true;
			}

			//第二个判断是判断当前点的父节点应该为哪一个，同时对父节点进行修正
			//dist中存的是当前点到源节点的最小距离
			if(dist[x-1][y-1]==-1||dist[x-1][y-1]>movetilt + dist[x][y])
			{
				dist[x-1][y-1] = movetilt + dist[x][y];
				prev[x-1][y-1] = PointToInt(x-1,y-1,xsize,ysize);
			}
		}
		if(x >= 0&&y -1 >= 0&&graph[x][y-1] != blocked)
		{
			if(s[PointToInt(x,y-1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x,y-1,xsize,ysize));
				s[PointToInt(x,y-1,xsize,ysize)] = true;
			}

			if(dist[x][y-1]==-1||dist[x][y-1]<movestraight + dist[x][y])
			{
				dist[x][y-1] = movestraight + dist[x][y];
				prev[x][y-1] = PointToInt(x,y-1,xsize,ysize);
			}

		}
		if(x+1 < xsize &&y -1 >= 0&&graph[x+1][y-1] != blocked)
		{
			if(s[PointToInt(x+1,y-1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x+1,y-1,xsize,ysize));
				s[PointToInt(x+1,y-1,xsize,ysize)] = true;
			}
			if(dist[x+1][y-1]==-1||dist[x+1][y-1]>movetilt + dist[x][y])
			{
				dist[x+1][y-1] = movetilt + dist[x][y];
				prev[x+1][y-1] = PointToInt(x+1,y-1,xsize,ysize);
			}
		}
		if(x-1 >= 0&&y >= 0&&graph[x-1][y] != blocked)
		{
			if(s[PointToInt(x-1,y,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x-1,y,xsize,ysize));
				s[PointToInt(x-1,y,xsize,ysize)] = true;
			}
			if(dist[x-1][y] ==-1||dist[x-1][y] >movetilt + dist[x][y])
			{
				dist[x-1][y] = movestraight + dist[x][y];
				prev[x-1][y] = PointToInt(x-1,y,xsize,ysize);
			}
		}
		if(x+1 < xsize&&y  >= 0&&graph[x+1][y] != blocked)
		{
			if(s[PointToInt(x+1,y,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x+1,y,xsize,ysize));
				s[PointToInt(x+1,y,xsize,ysize)] = true;
			}
			if(dist[x+1][y] ==-1||dist[x+1][y] >movetilt + dist[x][y])
			{
				dist[x+1][y] = movestraight + dist[x][y];
				prev[x+1][y] = PointToInt(x+1,y,xsize,ysize);
			}
		}
		if(x-1 >= 0&&y +1 < ysize&&graph[x-1][y+1] != blocked)
		{
			if(s[PointToInt(x-1,y+1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x-1,y+1,xsize,ysize));
				s[PointToInt(x-1,y+1,xsize,ysize)] = true;
			}
			if(dist[x-1][y-1] ==-1||dist[x-1][y-1] >movetilt + dist[x][y])
			{
				dist[x-1][y-1] = movestraight + dist[x][y];
				prev[x-1][y-1] = PointToInt(x-1,y-1,xsize,ysize);
			}
		}
		if(x >= 0&&y +1 < ysize&&graph[x][y+1] != blocked)
		{
			if(s[PointToInt(x,y+1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x,y+1,xsize,ysize));
				s[PointToInt(x,y+1,xsize,ysize)] = true;
			}
			if(dist[x][y+1] ==-1||dist[x][y+1] >movetilt + dist[x][y])
			{
				dist[x][y+1] = movestraight + dist[x][y];
				prev[x][y+1] = PointToInt(x,y+1,xsize,ysize);
			}
		}
		if(x+1 < xsize&&y+1 < ysize&&graph[x+1][y+1] != blocked)
		{
			if(s[PointToInt(x+1,y+1,xsize,ysize)] == false)
			{
				wlist.push_back(PointToInt(x+1,y+1,xsize,ysize));
				s[PointToInt(x+1,y+1,xsize,ysize)] = true;
			}
			if(dist[x+1][y+1] ==-1||dist[x+1][y+1] >movetilt + dist[x][y])
			{
				dist[x+1][y+1] = movestraight + dist[x][y];
				prev[x+1][y+1] = PointToInt(x,y+1,xsize,ysize);
			}
		}
	}//遍历整个栈的循环
	delete[]s;
}