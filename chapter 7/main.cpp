#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int main(){
	/*ALGraph G;
	CreateUDG(G);
	Boolean HaveVisited[MAX_VERTEX_NUM];
	DFSTraverse(G, HaveVisited, display);
	printf("\n");
	BFSTraverse(G, HaveVisited, display);
	printf("\n");
	for (int i = 0; i< G.vexnum; i++)
	{
		printf("%d->", i);
		while (G.vertices[i].firstarc != NULL)
		{
			printf("%d->", G.vertices[i].firstarc->adjvex);
			G.vertices[i].firstarc = G.vertices[i].firstarc->nextarc;

		}
		printf("\n");
	}*/

	/*MGraph G;
	char u;
	CreateUDN(G);
	printf("Please input the first vertex u: ");
	scanf("%c", &u);
	MiniSpanTree_PRIM(G, u);*/

	/*ALGraph G;
	CreateDG(G);
	printf("The TopologicalSort for G:\n");
	TopologicalSort(G);*/

	/*ALGraph G;
	CreateDN(G);
	SqStack T;
	int ve[MAX_VERTEX_NUM];
	CriticalPath(G, T, ve); */

	/*MGraph G;
	int v0;
	PathMatrix P;
	ShortPathTable D;
	CreateDN(G);
	printf("Please input v0£º");
	scanf("%d", &v0);
	ShortestPath_DIJ(G, v0, P, D);
	DisplayShortestPath_DIJ(G, v0, P, D);*/
	MGraph G;
	PathMatrix P[MAX_VERTEX_NUM];
	DistanceMatrix D;
	CreateDN(G);
	ShortestPath_FLOYD(G, P, D);
	DisplayShortestPath_FLOYD(G, P, D);
	system("pause");
	return 0;
}