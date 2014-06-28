#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int main(){
	ALGraph G;
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
	}
	system("pause");
	return 0;
}