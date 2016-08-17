#pragma once

//弗洛伊德算法, 此算法的主要目的是，计算所有点到所有点的之间的最小距离
//nsize : 节点个数
//dist  : 最短路径
//prev  : 路径
void Floyd(int nsize, float **dist ,int ** prev);
