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
	ALGraph G;
	CreateDN(G);
	SqStack T;
	int ve[MAX_VERTEX_NUM];
	CriticalPath(G, T, ve); 
	system("pause");
	return 0;
}