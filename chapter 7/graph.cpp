#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MyHeader.h"

Status CreateDN(MGraph &G){
	// �������飨�ڽӾ��󣩱�ʾ��������������G
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	int w;
	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfoΪ0����û�����������Ϣ
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vexs[i]);			// ���춥������
		getchar();
	}
	for (i = 0; i < G.vexnum; i++){			// ��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++){
			G.arcs[i][j] = { INIFINITY, NULL };		// {adj, info}
		}
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){			// �����ڽӾ���
		printf("Please input the vertex related to the %d th arc and its w:\n", k + 1);
		scanf("%c %c %d", &v1, &v2, &w);	// ����һ���������Ķ�����Ȩֵ
		getchar();
		i = LocateVex(G, v1);				// ȷ��v1,v2��G��λ��
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;				// ��<v1,v2>��Ȩֵ
		if (IncInfo) Input(G.arcs[i][j].info);	// �������������Ϣ��������
	}
	return OK;
}// CreateUDN

Status CreateUDN(MGraph &G){
	// �������飨�ڽӾ��󣩱�ʾ��������������G
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	int w;
	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfoΪ0����û�����������Ϣ
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vexs[i]);			// ���춥������
		getchar();
	}	
	for (i = 0; i < G.vexnum; i++){			// ��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++){
			G.arcs[i][j] = { INIFINITY, NULL };		// {adj, info}
		}
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){			// �����ڽӾ���
		printf("Please input the vertex related to the %d th arc and its w:\n", k+1);
		scanf("%c %c %d", &v1, &v2, &w);	// ����һ���������Ķ�����Ȩֵ
		getchar();
		i = LocateVex(G, v1);				// ȷ��v1,v2��G��λ��
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;				// ��<v1,v2>��Ȩֵ
		if (IncInfo) Input(G.arcs[i][j].info);	// �������������Ϣ��������
		G.arcs[j][i] = G.arcs[i][j];		// ��<v1,v2>�ĶԳƻ�<v2,v1>
	}
	return OK;
}// CreateUDN

int LocateVex(MGraph G, VertexType v){
	// ������v��ͼG�д��ڣ�������λ�ã����򷵻�ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (v == G.vexs[i])
			return i;
	}
	return ERROR;
}// LocateVex

void Input(InfoType* &info){
	// ���뻡�������Ϣ
	info = (InfoType *)malloc(sizeof(InfoType) * 50);
	printf("Please Input the Information of the arc: ");
	gets(info);
}// Input

int LocateVex(ALGraph G, VertexType v){
	// ������v��ͼG�д��ڣ�������λ�ã����򷵻�ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (G.vertices[i].data == v)
			return i;
	}
	return ERROR;
}// LocateVex

int FirstAdjVex(ALGraph G, int v){
	// ͼG���ڣ�v��G��ĳ������
	// ����v�ĵ�һ���ڽӶ��㣬��û���򷵻ء��ա�
	if (G.vertices[v].firstarc != NULL)
		return G.vertices[v].firstarc->adjvex;
	return -1;
}// FirstAdjVex

int NextAdjVex(ALGraph G, int v, int w){
	// G���ڣ�v��G��ĳ���㣬w��v���ڽӶ���
	// ����v�ģ������w����һ���ڽӶ��㡣��w��v�����һ���ڽӶ��㣬�򷵻ء��ա�
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
	// ͼG���ڣ�vΪG��ĳ������
	// ����v��ֵ
	return G.vertices[v].data;
}// GetVex

Status CreateDN(ALGraph &G){
	// �����ڽӱ��ʾ��������������G
	int i, j, k;
	char value[10];
	ArcNode *p;
	VertexType v1, v2;
	G.kind = DN;
	printf("Please input vexnum arcnum (DN): ");
	scanf("%d %d", &G.vexnum, &G.arcnum);	
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (DN): \n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc and its weight, separated by space��\n", k+1);
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
	// �����ڽӱ��ʾ������������ͼG
	int i, j, k;
	int IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = UDG;
	printf("Please input vexnum arcnum IncInfo(0/1) (UDG): ");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (UDG): ", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc, separated by space��\n", k + 1);
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
	// �����ڽӱ��ʾ������������ͼG
	int i, j, k;
	int IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = DG;
	printf("Please input vexnum arcnum IncInfo(0/1) (DG): ");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("Please input %d arc (DG): ", G.arcnum);
	for (k = 0; k < G.arcnum; k++){
		printf("Please input %d arc, separated by space��\n", k + 1);
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
	// ������v��ͼG�д��ڣ�������λ�ã����򷵻�ERROR
	int i;
	for (i = 0; i < G.vexnum; i++){
		if (G.xlist[i].data == v)
			return i;
	}
	return ERROR;
}// LocateVex

Status CreateDG(OLGraph &G){
	// ����ʮ������洢��ʾ����������ͼG(G.kind = DG)��
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	ArcBox *p;

	printf("Please input vexnum arcnum IncInfo(0/1):\n");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	// IncInfoΪ0����û�����������Ϣ
	getchar();											// �������Ļ��з�
	printf("Please input %d vertex: ", G.vexnum);
	for (i = 0; i < G.vexnum; i++){
		scanf("%c", &G.xlist[i].data);			// ���춥������
		getchar();
		G.xlist[i].firstin = NULL;				// ��ʼ��ָ��
		G.xlist[i].firstout = NULL;
	}
	printf("\nPlease input %d arcs:\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++){				// �������������ʮ������
		printf("Please input the vertex related to the %d th arc:\n", k + 1);
		scanf("%c %c", &v1, &v2);				// ����һ������ʼ����յ�
		getchar();
		i = LocateVex(G, v1);					// ȷ��v1,v2��G��λ��
		j = LocateVex(G, v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));	// �ٶ����㹻�ռ�
		*p = { i, j, G.xlist[j].firstin, G.xlist[j].firstout, NULL };	// �Ի����㸳ֵ
			//{tailvex, headvex, hlink, thlink, info}
		G.xlist[j].firstin = G.xlist[i].firstout = p;	// ������뻡�ͳ�����ͷ�Ĳ���
		if (IncInfo)							// �����������Ϣ��������
			Input((*p).info);
	}
	return OK;
}// CreateDG