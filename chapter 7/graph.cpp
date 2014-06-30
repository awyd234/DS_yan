#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int FirstAdjVex(ALGraph G, int v){
	// 图G存在，v是G中某个顶点
	// 返回v的第一个邻接顶点，若没有则返回“空”
	if (G.vertices[v].firstarc != NULL)
		return G.vertices[v].firstarc->adjvex;
	return -1;
}// FirstAdjVex

int NextAdjVex(ALGraph G, int v, int w){
	// G存在，v是G中某顶点，w是v的邻接顶点
	// 返回v的（相对于w）下一个邻接顶点。若w是v的最后一个邻接顶点，则返回“空”
	ArcNode *p;
	p = G.vertices[v].firstarc;
	while (p){
		if (p->adjvex == w){
			p = p->nextarc;
			if (p != NULL){
				return p->adjvex;
			} else{
				return -1;
			}
		} else{
			p = p->nextarc;
		}
	}
	return -1;
}// NextAdjVex

int GetVex(ALGraph G, int v){
	// 图G存在，v为G的某个顶点
	// 返回v的值
	return G.vertices[v].data;
}// GetVex

Status CreateDN(ALGraph &G){
	// 采用邻接表表示法，构造有向网G
	int i, j, k;
	char value[10];
	ArcNode *p;
	VertexType v1, v2;
	G.kind = DN;
	printf("Please input vexnum arcnum (DN): ");
	scanf("%d %d", &G.vexnum, &G.arcnum);	
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (DN): \n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc and its weight, separated by space：\n", k+1);
		scanf("%c %c %s", &v1, &v2, value);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (!(p = (ArcNode *)malloc(sizeof(ArcNode))))
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		G.vertices[i].firstarc->info = (char *)malloc(50 * sizeof(char));
		strcpy(G.vertices[i].firstarc->info, value);
	}
	return OK;
}//  CreateDN

Status CreateUDG(ALGraph &G){
	// 采用邻接表表示法，构造无向图G
	int i, j, k;
	int IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = UDG;
	printf("Please input vexnum arcnum IncInfo(0/1) (UDG): ");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (UDG): ", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc, separated by space：\n", k + 1);
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (!(p = (ArcNode *)malloc(sizeof(ArcNode))))
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		if (!(p = (ArcNode *)malloc(sizeof(ArcNode))))
			return ERROR;
		p->nextarc = G.vertices[j].firstarc;
		p->adjvex = i;
		G.vertices[j].firstarc = p;
		if (IncInfo){
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}
	return OK;
}// CreateUDG

Status CreateDG(ALGraph &G){
	// 采用邻接表表示法，构造有向图G
	int i, j, k;
	int IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = DG;
	printf("Please input vexnum arcnum IncInfo(0/1) (DG): ");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();											// 接收最后的换行符
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (DG): ", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc, separated by space：\n", k + 1);
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (!(p = (ArcNode *)malloc(sizeof(ArcNode))))
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		if (IncInfo){
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}
	return OK;
}// CreateDG

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