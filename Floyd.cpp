#include "StdAfx.h"
#include "Floyd.h"

//¸¥ÂåÒÁµÂËã·¨
void Floyd(int nsize, float **dist ,int ** prev)
{
	for(int i=0;i<nsize;++i)
	{
		for(int j=0;j<nsize;++j)
		{
			for(int k=0;k<nsize;++k)
			{
				if(dist[i][k]+dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j]; 
					prev[i][j] = k;
				}
			}
		}
	}
}