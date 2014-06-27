#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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