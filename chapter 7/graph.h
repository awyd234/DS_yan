#ifndef _GRAPH_H_
#define _GRAPH_H_

#define INIFINITY INT_MAX		// ���ֵ
#define MAX_VERTEX_NUM 20		// ��󶥵����
typedef enum { DG, DN, UDG, UDN } GraphKind;		// {����ͼ��������������ͼ��������}
typedef char VRType;			// �����ϵ����
typedef char VertexType;	// ��������
typedef char InfoType;		// �������Ϣ��ָ��

typedef VertexType QElemType;
typedef VertexType TElemType;

//----- ͼ�����飨�ڽӾ��󣩴洢��ʾ -----
typedef struct ArcCell{
	VRType		adj;	// VRType�Ƕ����ϵ���͡�����Ȩͼ����1��0��ʾ���ڷ�
						// �Դ�Ȩͼ����ΪȨֵ����
	InfoType	*info;	// �û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	VertexType	vexs[MAX_VERTEX_NUM];	// ��������
	AdjMatrix	arcs;					// �ڽӾ���
	int			vexnum, arcnum;			// ͼ�ĵ�ǰ�������뻡��
	GraphKind	kind;					// ͼ�������־
}MGraph;

Status CreateDN(MGraph &G);
Status CreateUDN(MGraph &G);
int LocateVex(MGraph G, VertexType v);
void Input(InfoType* &info);

//----- ͼ���ڽӱ�洢��ʾ -----
typedef struct ArcNode{
	int				adjvex;		// �û�ָ��Ķ����λ��
	struct ArcNode	*nextarc;	// ָ����һ������ָ��
	InfoType		*info;		// �û������Ϣ��ָ��
}ArcNode;

typedef struct VNode{
	VertexType		data;		// ������Ϣ
	ArcNode			*firstarc;	// ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList			vertices;
	int				vexnum, arcnum;		// ͼ�ĵ�ǰ�������뻡��
	int				kind;				// ͼ�������־
}ALGraph;

int LocateVex(ALGraph G, VertexType v);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int v, int w);
int GetVex(ALGraph G, int v);
Status CreateDN(ALGraph &G);
Status CreateUDG(ALGraph &G);
Status CreateDG(ALGraph &G);

//----- ����ͼ��ʮ������洢��ʾ -----
typedef struct ArcBox{
	int				tailvex, headvex;	// �û���β��ͷ�����λ��
	struct ArcBox	*hlink, *tlink;		// �ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType		*info;				// �û������Ϣ��ָ��
}ArcBox;

typedef struct VexNode{
	VertexType		data;
	ArcBox			*firstin, *firstout;// �ֱ�ָ��ö����һ���뻡���һ������
}VexNode;

typedef struct{
	VexNode			xlist[MAX_VERTEX_NUM];	// ��ͷ����
	int				vexnum, arcnum;			// ���򻡵ĵ�ǰ�������뻡��
}OLGraph;

int LocateVex(OLGraph G, VertexType v);
Status CreateDG(OLGraph &G);

//----- ����ͼ���ڽӶ��ر�洢��ʾ
typedef enum { unvisited, visited } VisitIf;

typedef struct EBox{
	VisitIf			mark;				// ���ʱ��
	int				ivex, jvex;			// �ñ����������������λ��
	struct EBox		*ilink, *jlink;		// �ֱ�ָ�������������������һ����
	InfoType		*info;				// �ñ���Ϣָ��
}EBox;

typedef struct VexBox{
	VertexType		data;
	EBox			*firstedge;			// ָ���һ�������ö���ı�
}VerBox;

typedef struct{
	VerBox			adjmulist[MAX_VERTEX_NUM];
	int				vexnum, arcnum;		// ����ͼ�ĵ�ǰ�����������
}AMLGraph;

#endif