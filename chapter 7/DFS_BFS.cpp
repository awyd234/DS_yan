#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Boolean HaveVisited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);


void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// ��ͼG��������ȱ���
	int v;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;				// ���ʱ�־�����ʼ��
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v])
			DFS(G, v, visited, Visit);	// ��δ���ʵ��������DFS
	}
}// DFSTraverse

void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// �ӵ�v����������ݹ��������ȱ���ͼG
	int w;
	visited[v] = TRUE;				// ���ʵ�v�����
	Visit(G, v);
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]) DFS(G, w, visited, Visit);	// ��v����δ���ʵ��ڽӶ���w�ݹ����DFS
	}
}// DFS

void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// ��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
	int v, w;
	QElemType u;
	LinkQueue Q;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	InitQueue(Q);					// �ÿյĸ�������Q
	for (v = 0; v < G.vexnum; v++){
		if (!visited[v]){			// v��δ����
			visited[v] = TRUE;
			Visit(G, v);
			EnQueue(Q, v);			// v�����
			while (!QueueEmpty(Q)){
				DeQueue(Q, u);		// ��ͷԪ�س��Ӳ���Ϊu
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
					if (!visited[w]){	// wΪu����δ���ʵ��ڽӶ���
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
	// ��������ͼG�������������ɭ�ֵģ����󣩺��ӣ��ң��ֵ�����T
	int v;
	CSTree p, q;
	q = NULL;
	T = NULL;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v]){						// ��v����Ϊ�µ��������ĸ����
			p = (CSTree)malloc(sizeof(CSNode));	// ��������
			*p = { GetVex(G, v), NULL, NULL };	// ���ý�㸳ֵ
			if (!T){							// �ǵ�һ���������ĸ���T�ĸ���
				T = p;
			} else{
				q->nextsibling = p;			// �������������ĸ���ǰһ�õĸ��ġ��ֵܡ���
			}
			q = p;								// qָʾ��ǰ�������ĸ�
			DFSTree(G, v, p, visited);			// ������pΪ����������
		}
	}
}// DFSForest

void DFSTree(ALGraph G, int v, CSTree &T, Boolean visited[]){
	// �ӵ�v���������������ȱ���ͼG��������TΪ����������
	int w;
	bool first;
	CSTree p, q;
	q = NULL;
	visited[v] = TRUE;
	first = TRUE;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]){
			p = (CSTree)malloc(sizeof(CSNode));	// ���亢�ӽ��
			*p = { GetVex(G, w), NULL, NULL };
			if (first){							// w��v�ĵ�һ��δ�����ʵ��ڽӶ���
				T->lchild = p;					// �Ǹ�������
				first = FALSE;
			} else{								// w��v������δ�����ʵ��ڽӶ���
				q->nextsibling = p;				// ����һ�ڽӶ�������ֵܽ��
			}
			q = p;
			DFSTree(G, w, q, visited);	// �ӵ�w���������������ȱ���ͼG��������������q
		} // if
	} // for
}// DFSTree

void MiniSpanTree_PRIM(MGraph G, VertexType u){
	// ������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
	// ��¼�Ӷ��㼯 U �� V-U �Ĵ�����С�ıߵĸ������鶨��
	int i, j, k;
	lowedge closedge;
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; ++j){
		if (j != k){						// ���������ʼ��
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;				// ��ʼ��U = {u}
	for (i = 1; i < G.vexnum; ++i){			// ѡ������G.vexnum - 1 ������
		k = minimum(closedge, G.vexnum);	// ���T����һ����㣺��k����
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);		// ������������
		closedge[k].lowcost = 0;			// ��k���㲢��U��
		for (j = 0; j < G.vexnum; ++j){
			if (G.arcs[k][j].adj < closedge[j].lowcost){	// �¶��㲢��U������ѡ����С��
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
	// ����ͼG�����ڽӱ�洢�ṹ
	// ��G�޻�·�������G�Ķ����һ���������в�����OK������ERROR
	int i, count, k;
	int indegree[MAX_VERTEX_NUM];
	ArcNode *p;
	SqStack S;
	FindInDregree(G, indegree);			// �Ը����������
	InitStack(S);
	for (i = 0; i < G.vexnum; i++){		// ������ȶ���տS
		if (!indegree[i])
			Push(S, i);					// ���Ϊ0�߽�ջ
	}
	count = 0;							// ������������
	while (!StackEmpty(S)){
		Pop(S, i);						// ���i�Ŷ��㲢����
		printf("%d %c\n", i, G.vertices[i].data);
		++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc){
			k = p->adjvex;				// ��i�Ŷ����ÿ���ڽӵ����ȼ�1
			if (!(--indegree[k]))
				Push(S, k);				// ����ȼ�Ϊ0����ջ
		}// for
	}// while
	if (count < G.vexnum){				// ������ͼ�л�·
		return ERROR;
	} else{
		return OK;
	}
}// TopologicalSort

void FindInDregree(ALGraph G, int indegree[]){
	// �Ը����������
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
	// ����ͼG�����ڽӱ�洢�ṹ, ��������¼������緢��ʱ��ve
	// TΪ�������ж���ջ��SΪ����ȶ���ջ
	// ��G�޻�·������ջT����G��һ���������У��Һ���ֵΪOK������ERROR
	int i, count, k;
	int arctime;
	int indegree[MAX_VERTEX_NUM];
	ArcNode *p;
	SqStack S;
	FindInDregree(G, indegree);			// �Ը����������
	InitStack(S);
	for (i = 0; i < G.vexnum; i++){		// ������ȶ���ջS
		if (!indegree[i])
			Push(S, i);					// ���Ϊ0�߽�ջ
		ve[i] = 0;						// ��ʼ��
	}
	InitStack(T);
	count = 0;							// ������������
	while (!StackEmpty(S)){
		Pop(S, i);						// i�Ŷ�����Tջ������
		Push(T, i);
		++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc){
			k = p->adjvex;				// ��i�Ŷ����ÿ���ڽӵ����ȼ�1
			if (!(--indegree[k]))
				Push(S, k);				// ����ȼ�Ϊ0����ջ
			arctime = atoi(p->info);	// �ѻʱ�����ַ�תΪ����
			if (ve[i] + arctime > ve[k]){
				ve[k] = ve[i] + arctime;
			}
		}// for   *(p->info) = dut(<j,k>)
	}// while
	if (count < G.vexnum){				// ���������л�·
		return ERROR;
	} else{
		return OK;
	}
}// TopologicalOrder

Status CriticalPath(ALGraph G, SqStack &T, int ve[]){
	// GΪ�����������G�ĸ���ؼ��
	int i, j, k, dut, ee, el;
	char tag;
	int vl[MAX_VERTEX_NUM];
	ArcNode *p;
	if (!TopologicalOrder(G, T, ve)){
		return ERROR;
	}
	for (i = 0; i < G.vexnum; i++){
		vl[i] = ve[G.vexnum - 1];		// ��ʼ�������¼�����ٷ���ʱ��
	}
	while (!StackEmpty(T)){				// ������������������vlֵ
		for (Pop(T, j), p = G.vertices[j].firstarc; p; p = p->nextarc){
			k = p->adjvex;
			dut = atoi(p->info);
			if (vl[k] - dut < vl[j]){
				vl[j] = vl[k] - dut;
			}
		}// for
	}// while
	for (j = 0; j < G.vexnum; j++){		// ��ee,el�͹ؼ��
		for (p = G.vertices[j].firstarc; p; p = p->nextarc){
			k = p->adjvex;
			dut = atoi(p->info);
			ee = ve[j];
			el = vl[k] - dut;
			tag = (ee == el) ? '*' : ' ';
			if (ee == el)
				printf("%c->%c ", G.vertices[j].data, G.vertices[k].data);
			//printf("%d %d %d %d %d%c\n", j, k, dut, ee, el, tag);	// ����ؼ��
		}
	}
	return OK;
}// CriticalPath

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){
	// ��dijkstra�㷨��������G�Ķ���v0�����ඥ��v�����·��P[v]�����Ȩ����D[v]
	// ��P[v][w]ΪTRUE����w�Ǵ�v0��v��ǰ������·���ϵ����·��
	// final[v]ΪTRUE�����ҽ���v��S�����Ѿ���ô�v0��v�����·��
	int i, v, w, min;
	bool flag;
	bool final[MAX_VERTEX_NUM];
	for (v = 0; v < G.vexnum; v++){
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; w++)			// ���·��
			P[v][w] = FALSE;
		if (D[v] < INIFINITY){
			P[v][v0] = TRUE;
			P[v][v] = TRUE;
		}// if
	}// for
	D[v0] = 0;									// ��ʼ����v0��������S��
	final[v0] = TRUE;
	// ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v�ӵ�S��
	for (i = 0; i < G.vexnum; i++){				// ����G.vexnum-1������
		min = INIFINITY;						// ��ǰ��֪��v0�������
		flag = FALSE;
		for (w = 0; w > G.vexnum; w++){
			if (!final[w]){						// w������ V - S ��
				if (D[w] < min){				// w������v0�������
					flag = TRUE;
					v = w;
					min = D[w];
				}
			}
		}
		if (!flag)
			break;
		final[v] = TRUE;						// ��v0���������v����S��
		for (w = 0; w < G.vexnum; w++){			// ���µ�ǰ���·��������
			if (!final[w] && (min + G.arcs[v][w].adj < D[w]) && G.arcs[v][w].adj != INIFINITY){	// �޸�D[w]��P[w]��w��V-S
				D[w] = min + G.arcs[v][w].adj;
				CopyPath(P, w, v);				// P[w] = P[v] + P[w]
				P[w][w] = TRUE;
			} // if
		}
	}// for
}// ShortestPath_DIJ

void CopyPath(PathMatrix &P, int w, int v){
	// �������·������v��·��������w
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++){
		P[w][i] = P[v][i];
	}
}// CopyPath

void DisplayShortestPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D){
	// ��ӡDijkstra�㷨��õ�v0���������������·��P��·������D
	int i, j;
	printf("The following is the shortest path from %c to other vex��\n", G.vexs[v0]);
	for (i = 0; i < G.vexnum; i++){
		if (i != v0){
			if (D[i] == INIFINITY){
				printf("Vertex %c cannot be reached!", G.vexs[i]);
			} else{
				printf("Vertex %c (the distance is %d)��", G.vexs[i], D[i]);
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
	// ��ӡͼG�ĵ�v������
	if (v >= G.vexnum)
		return ERROR;
	printf("%c ", G.vertices[v].data);
	return OK;
}// display
