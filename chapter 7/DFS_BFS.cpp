#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Boolean HaveVisited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);

void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// 对图G作深度优先遍历
	int v;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;				// 访问标志数组初始化
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v])
			DFS(G, v, visited, Visit);	// 对未访问的数组调用DFS
	}
}// DFSTraverse

void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// 从第v个顶点出发递归地深度优先遍历图G
	int w;
	visited[v] = TRUE;				// 访问第v个结点
	Visit(G, v);
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]) DFS(G, w, visited, Visit);	// 对v的尚未访问的邻接顶点w递归调用DFS
	}
}// DFS

void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// 按广度优先非递归遍历图G，使用辅助队列Q和访问标志数组visited
	int v, w;
	QElemType u;
	LinkQueue Q;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	InitQueue(Q);					// 置空的辅助队列Q
	for (v = 0; v < G.vexnum; v++){
		if (!visited[v]){			// v尚未访问
			visited[v] = TRUE;
			Visit(G, v);
			EnQueue(Q, v);			// v入队列
			while (!QueueEmpty(Q)){
				DeQueue(Q, u);		// 队头元素出队并置为u
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
					if (!visited[w]){	// w为u的尚未访问的邻接顶点
						visited[w] = TRUE;
						Visit(G, w);
						EnQueue(Q, w);
					} // if
				} // for
			} // while
		} // if
	} // for
}// BFSTraverse

void DFSForest(ALGraph G, CSTree &T, Boolean visited[]){
	// 建立无向图G的深度优先生成森林的（最左）孩子（右）兄弟链表T
	int v;
	CSTree p, q;
	q = NULL;
	T = NULL;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v]){						// 第v顶点为新的生成树的根结点
			p = (CSTree)malloc(sizeof(CSNode));	// 分配根结点
			*p = { GetVex(G, v), NULL, NULL };	// 给该结点赋值
			if (!T){							// 是第一棵生成树的根（T的根）
				T = p;
			} else{
				q->nextsibling = p;			// 是其他生成树的根（前一棵的根的“兄弟”）
			}
			q = p;								// q指示当前生成树的根
			DFSTree(G, v, p, visited);			// 建立以p为根的生成树
		}
	}
}// DFSForest

void DFSTree(ALGraph G, int v, CSTree &T, Boolean visited[]){
	// 从第v个顶点出发深度优先遍历图G，建立以T为根的生成树
	int w;
	bool first;
	CSTree p, q;
	q = NULL;
	visited[v] = TRUE;
	first = TRUE;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]){
			p = (CSTree)malloc(sizeof(CSNode));	// 分配孩子结点
			*p = { GetVex(G, w), NULL, NULL };
			if (first){							// w是v的第一个未被访问的邻接顶点
				T->lchild = p;					// 是根的左孩子
				first = FALSE;
			} else{								// w是v的其他未被访问的邻接顶点
				q->nextsibling = p;				// 是上一邻接顶点的右兄弟结点
			}
			q = p;
			DFSTree(G, w, q, visited);	// 从第w个顶点出发深度优先遍历图G，建立子生成树q
		} // if
	} // for
}// DFSTree

Status display(ALGraph G, int v){
	// 打印图G的第v个顶点
	if (v >= G.vexnum)
		return ERROR;
	printf("%c ", G.vertices[v].data);
	return OK;
}// display
