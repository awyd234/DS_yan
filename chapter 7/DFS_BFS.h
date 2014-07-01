#ifndef _DFS_BFS_H_
#define _DFS_BFS_H_

typedef struct{						// Prim算法的辅助数组
	VertexType	adjvex;
	VRType		lowcost;
}lowedge[MAX_VERTEX_NUM];

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void DFSForest(ALGraph G, CSTree &T);
void DFSTree(ALGraph G, int v, CSTree &T, Boolean visited[]);
void MiniSpanTree_PRIM(MGraph G, VertexType u);
int minimum(lowedge closedge, int len);
Status TopologicalSort(ALGraph G);
void FindInDregree(ALGraph G, int indegree[]);
Status TopologicalOrder(ALGraph G, SqStack &T, int ve[]);
Status CriticalPath(ALGraph G, SqStack &T, int ve[]);
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D);
void CopyPath(PathMatrix &P, int w, int v);
void DisplayShortestPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D);
void ShortestPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D);
void DisplayShortestPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D);
Status display(ALGraph G, int v);

#endif