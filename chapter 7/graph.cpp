#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status CreateDN(MGraph &G){
	// 采用数组（邻接矩阵）表示法，构造有向网G
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	int w;
	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfo为0，则该弧不含其他信息
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vexs[i]);			// 构造顶点向量
		getchar();
	}
	for (i = 0; i < G.vexnum; i++){			// 初始化邻接矩阵
		for (j = 0; j < G.vexnum; j++){
			G.arcs[i][j] = { INIFINITY, NULL };		// {adj, info}
		}
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){			// 构造邻接矩阵
		printf("Please input the vertex related to the %d th arc and its w:\n", k + 1);
		scanf("%c %c %d", &v1, &v2, &w);	// 输入一条边依附的顶点与权值
		getchar();
		i = LocateVex(G, v1);				// 确定v1,v2在G中位置
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;				// 弧<v1,v2>的权值
		if (IncInfo) Input(G.arcs[i][j].info);	// 若弧含有相关信息，则输入
	}
	return OK;
}// CreateUDN

Status CreateUDN(MGraph &G){
	// 采用数组（邻接矩阵）表示法，构造无向网G
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	int w;
	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfo为0，则该弧不含其他信息
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vexs[i]);			// 构造顶点向量
		getchar();
	}	
	for (i = 0; i < G.vexnum; i++){			// 初始化邻接矩阵
		for (j = 0; j < G.vexnum; j++){
			G.arcs[i][j] = { INIFINITY, NULL };		// {adj, info}
		}
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){			// 构造邻接矩阵
		printf("Please input the vertex related to the %d th arc and its w:\n", k+1);
		scanf("%c %c %d", &v1, &v2, &w);	// 输入一条边依附的顶点与权值
		getchar();
		i = LocateVex(G, v1);				// 确定v1,v2在G中位置
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;				// 弧<v1,v2>的权值
		if (IncInfo) Input(G.arcs[i][j].info);	// 若弧含有相关信息，则输入
		G.arcs[j][i] = G.arcs[i][j];		// 置<v1,v2>的对称弧<v2,v1>
	}
	return OK;
}// CreateUDN

int LocateVex(MGraph G, VertexType v){
	// 若顶点v在图G中存在，返回其位置，否则返回ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (v == G.vexs[i])
			return i;
	}
	return ERROR;
}// LocateVex

void Input(InfoType* &info){
	// 输入弧的相关信息
	info = (InfoType *)malloc(sizeof(InfoType) * 50);
	printf("Please Input the Information of the arc: ");
	gets(info);
}// Input

int LocateVex(ALGraph G, VertexType v){
	// 若顶点v在图G中存在，返回其位置，否则返回ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (G.vertices[i].data == v)
			return i;
	}
	return ERROR;
}// LocateVex

int LocateVex(OLGraph G, VertexType v){
	// 若顶点v在图G中存在，返回其位置，否则返回ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (G.xlist[i].data == v)
			return i;
	}
	return ERROR;
}// LocateVex

Status CreateDG(OLGraph &G){
	// 采用十字链表存储表示，构造有向图G(G.kind = DG)。
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	ArcBox *p;

	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfo为0，则该弧不含其他信息
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.xlist[i].data);			// 构造顶点向量
		getchar();
		G.xlist[i].firstin = NULL;				// 初始化指针
		G.xlist[i].firstout = NULL;
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){				// 输入各弧并构造十字链表
		printf("Please input the vertex related to the %d th arc:\n", k + 1);
		scanf("%c %c", &v1, &v2);				// 输入一条弧的始点和终点
		getchar();
		i = LocateVex(G, v1);					// 确定v1,v2在G中位置
		j = LocateVex(G, v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));	// 假定有足够空间
		*p = { i, j, G.xlist[j].firstin, G.xlist[j].firstout, NULL };	// 对弧顶点赋值
			//{tailvex, headvex, hlink, thlink, info}
		G.xlist[j].firstin = G.xlist[i].firstout = p;	// 完成在入弧和出弧链头的插入
		if (IncInfo)							// 若弧含相关信息，则输入
			Input((*p).info);
	}
	return OK;
}// CreateDG