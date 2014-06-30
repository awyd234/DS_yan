#ifndef _DFS_BFS_H_
#define _DFS_BFS_H_

typedef struct{						// Prim算法的辅助数组
	VertexType	adjvex;
	VRType		lowcost;
}lowedge[MAX_VERTEX_NUM];

void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void DFSForest(ALGraph G, CSTree &T);
void DFSTree(ALGraph G, int v, CSTree &T, Boolean visited[]);
void MiniSpanTree_PRIM(MGraph G, VertexType u);
int minimum(lowedge closedge, int len);
Status display(ALGraph G, int v);

#endif