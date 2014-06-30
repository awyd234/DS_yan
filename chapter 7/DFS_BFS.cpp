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

void MiniSpanTree_PRIM(MGraph G, VertexType u){
	// 用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
	// 记录从顶点集 U 到 V-U 的代价最小的边的辅助数组定义
	int i, j, k;
	lowedge closedge;
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; ++j){
		if (j != k){						// 辅助数组初始化
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;				// 初始，U = {u}
	for (i = 1; i < G.vexnum; ++i){			// 选择其余G.vexnum - 1 个顶点
		k = minimum(closedge, G.vexnum);	// 求出T的下一个结点：第k顶点
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);		// 生成树的两边
		closedge[k].lowcost = 0;			// 第k顶点并入U集
		for (j = 0; j < G.vexnum; ++j){
			if (G.arcs[k][j].adj < closedge[j].lowcost){	// 新顶点并入U后重新选择最小边
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}// MiniSpanTree_PRIM

int minimum(lowedge closedge, int len){
	int i, min;
	min = -1;
	for (i = 0; i < len; i++){
		if (closedge[i].lowcost){
			min = i;
			break;
		}
	}
	for (; i < len; i++){
		if (closedge[i].lowcost && closedge[i].lowcost < closedge[min].lowcost){
			min = i;
		}
	}
	return min;
}// minimum

Status TopologicalSort(ALGraph G){
	// 有向图G采用邻接表存储结构
	// 若G无回路，则输出G的顶点的一个拓扑序列并返回OK，否则ERROR
	int i, count, k;
	int indegree[MAX_VERTEX_NUM];
	ArcNode *p;
	SqStack S;
	FindInDregree(G, indegree);			// 对各顶点求入度
	InitStack(S);
	for (i = 0; i < G.vexnum; i++){		// 建零入度顶点湛S
		if (!indegree[i])
			Push(S, i);					// 入度为0者进栈
	}
	count = 0;							// 对输出顶点计数
	while (!StackEmpty(S)){
		Pop(S, i);						// 输出i号顶点并计数
		printf("%d %c\n", i, G.vertices[i].data);
		++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc){
			k = p->adjvex;				// 对i号顶点的每个邻接点的入度减1
			if (!(--indegree[k]))
				Push(S, k);				// 若入度减为0则入栈
		}// for
	}// while
	if (count < G.vexnum){				// 该有向图有回路
		return ERROR;
	} else{
		return OK;
	}
}// TopologicalSort

void FindInDregree(ALGraph G, int indegree[]){
	// 对各顶点求入度
	int i;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++){
		indegree[i] = 0;
	}
	for (i = 0; i < G.vexnum; i++){
		for (p = G.vertices[i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]++;
		}
	}
}//  FindInDregree

Status TopologicalOrder(ALGraph G, SqStack &T, int ve[]){
	// 有向图G采用邻接表存储结构, 求各顶点事件的最早发生时间ve
	// T为拓扑序列顶点栈，S为零入度顶点栈
	// 若G无回路，则用栈T返回G的一个拓扑序列，且函数值为OK，否则ERROR
	int i, count, k;
	int arctime;
	int indegree[MAX_VERTEX_NUM];
	ArcNode *p;
	SqStack S;
	FindInDregree(G, indegree);			// 对各顶点求入度
	InitStack(S);
	for (i = 0; i < G.vexnum; i++){		// 建零入度顶点栈S
		if (!indegree[i])
			Push(S, i);					// 入度为0者进栈
		ve[i] = 0;						// 初始化
	}
	InitStack(T);
	count = 0;							// 对输出顶点计数
	while (!StackEmpty(S)){
		Pop(S, i);						// i号顶点入T栈并计数
		Push(T, i);
		++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc){
			k = p->adjvex;				// 对i号顶点的每个邻接点的入度减1
			if (!(--indegree[k]))
				Push(S, k);				// 若入度减为0则入栈
			arctime = atoi(p->info);	// 把活动时间由字符转为整数
			if (ve[i] + arctime > ve[k]){
				ve[k] = ve[i] + arctime;
			}
		}// for   *(p->info) = dut(<j,k>)
	}// while
	if (count < G.vexnum){				// 该有向网有回路
		return ERROR;
	} else{
		return OK;
	}
}// TopologicalOrder

Status CriticalPath(ALGraph G, SqStack &T, int ve[]){
	// G为有向网，输出G的各项关键活动
	int i, j, k, dut, ee, el;
	char tag;
	int vl[MAX_VERTEX_NUM];
	ArcNode *p;
	if (!TopologicalOrder(G, T, ve)){
		return ERROR;
	}
	for (i = 0; i < G.vexnum; i++){
		vl[i] = ve[G.vexnum - 1];		// 初始化顶点事件的最迟发生时间
	}
	while (!StackEmpty(T)){				// 按拓扑逆序求各定点的vl值
		for (Pop(T, j), p = G.vertices[j].firstarc; p; p = p->nextarc){
			k = p->adjvex;
			dut = atoi(p->info);
			if (vl[k] - dut < vl[j]){
				vl[j] = vl[k] - dut;
			}
		}// for
	}// while
	for (j = 0; j < G.vexnum; j++){		// 求ee,el和关键活动
		for (p = G.vertices[j].firstarc; p; p = p->nextarc){
			k = p->adjvex;
			dut = atoi(p->info);
			ee = ve[j];
			el = vl[k] - dut;
			tag = (ee == el) ? '*' : ' ';
			if (ee == el)
				printf("%c->%c ", G.vertices[j].data, G.vertices[k].data);
			//printf("%d %d %d %d %d%c\n", j, k, dut, ee, el, tag);	// 输出关键活动
		}
	}
	return OK;
}// CriticalPath

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){
	// 用dijkstra算法求有向网G的顶点v0到其余顶点v的最短路径P[v]及其带权长度D[v]
	// 若P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的最短路径
	// final[v]为TRUE，当且仅当v∈S，即已经求得从v0到v的最短路径
	int i, v, w, min;
	bool flag;
	bool final[MAX_VERTEX_NUM];
	for (v = 0; v < G.vexnum; v++){
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; w++)			// 设空路径
			P[v][w] = FALSE;
		if (D[v] < INIFINITY){
			P[v][v0] = TRUE;
			P[v][v] = TRUE;
		}// if
	}// for
	D[v0] = 0;									// 初始化，v0顶点属于S集
	final[v0] = TRUE;
	// 开始主循环，每次求得v0到某个v顶点的最短路径，并将v加到S集
	for (i = 0; i < G.vexnum; i++){				// 其余G.vexnum-1各顶点
		min = INIFINITY;						// 当前所知离v0最近距离
		flag = FALSE;
		for (w = 0; w > G.vexnum; w++){
			if (!final[w]){						// w顶点在 V - S 中
				if (D[w] < min){				// w顶点离v0顶点更近
					flag = TRUE;
					v = w;
					min = D[w];
				}
			}
		}
		if (!flag)
			break;
		final[v] = TRUE;						// 离v0顶点最近的v加入S集
		for (w = 0; w < G.vexnum; w++){			// 更新当前最短路径及距离
			if (!final[w] && (min + G.arcs[v][w].adj < D[w]) && G.arcs[v][w].adj != INIFINITY){	// 修改D[w]和P[w]，w∈V-S
				D[w] = min + G.arcs[v][w].adj;
				CopyPath(P, w, v);				// P[w] = P[v] + P[w]
				P[w][w] = TRUE;
			} // if
		}
	}// for
}// ShortestPath_DIJ

void CopyPath(PathMatrix &P, int w, int v){
	// 复制最短路径顶点v的路径到顶点w
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++){
		P[w][i] = P[v][i];
	}
}// CopyPath

void DisplayShortestPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D){
	// 打印Dijkstra算法求得的v0到其余各顶点的最短路径P及路径长度D
	int i, j;
	printf("The following is the shortest path from %c to other vex：\n", G.vexs[v0]);
	for (i = 0; i < G.vexnum; i++){
		if (i != v0){
			if (D[i] == INIFINITY){
				printf("Vertex %c cannot be reached!", G.vexs[i]);
			} else{
				printf("Vertex %c (the distance is %d)：", G.vexs[i], D[i]);
				for (j = 0; j < G.vexnum; j++){
					if (P[i][j]){
						printf("%c ", G.vexs[j]);
					}
				}
			}
			printf("\n");
		}
	}
}// DisplayShortestPath_DIJ

Status display(ALGraph G, int v){
	// 打印图G的第v个顶点
	if (v >= G.vexnum)
		return ERROR;
	printf("%c ", G.vertices[v].data);
	return OK;
}// display
