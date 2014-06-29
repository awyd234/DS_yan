#ifndef _GRAPH_H_
#define _GRAPH_H_

#define INIFINITY INT_MAX		// 最大值
#define MAX_VERTEX_NUM 20		// 最大顶点个数
typedef enum { DG, DN, UDG, UDN } GraphKind;		// {有向图，有向网，无向图，无向网}
typedef char VRType;			// 顶点关系类型
typedef char VertexType;	// 顶点向量
typedef char InfoType;		// 弧相关信息的指针

typedef VertexType QElemType;
typedef VertexType TElemType;

//----- 图的数组（邻接矩阵）存储表示 -----
typedef struct ArcCell{
	VRType		adj;	// VRType是顶点关系类型。对无权图，用1或0表示相邻否；
						// 对带权图，则为权值类型
	InfoType	*info;	// 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	VertexType	vexs[MAX_VERTEX_NUM];	// 顶点向量
	AdjMatrix	arcs;					// 邻接矩阵
	int			vexnum, arcnum;			// 图的当前定点数与弧数
	GraphKind	kind;					// 图的种类标志
}MGraph;

Status CreateDN(MGraph &G);
Status CreateUDN(MGraph &G);
int LocateVex(MGraph G, VertexType v);
void Input(InfoType* &info);

//----- 图的邻接表存储表示 -----
typedef struct ArcNode{
	int				adjvex;		// 该弧指向的顶点的位置
	struct ArcNode	*nextarc;	// 指向下一条弧的指针
	InfoType		*info;		// 该弧相关信息的指针
}ArcNode;

typedef struct VNode{
	VertexType		data;		// 顶点信息
	ArcNode			*firstarc;	// 指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList			vertices;
	int				vexnum, arcnum;		// 图的当前顶点数与弧数
	int				kind;				// 图的种类标志
}ALGraph;

int LocateVex(ALGraph G, VertexType v);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int v, int w);
int GetVex(ALGraph G, int v);
Status CreateDN(ALGraph &G);
Status CreateUDG(ALGraph &G);
Status CreateDG(ALGraph &G);

//----- 有向图的十字链表存储表示 -----
typedef struct ArcBox{
	int				tailvex, headvex;	// 该弧的尾和头顶点的位置
	struct ArcBox	*hlink, *tlink;		// 分别为弧头相同和弧尾相同的弧的邻域
	InfoType		*info;				// 该弧相关信息的指针
}ArcBox;

typedef struct VexNode{
	VertexType		data;
	ArcBox			*firstin, *firstout;// 分别指向该顶点第一条入弧与第一条出弧
}VexNode;

typedef struct{
	VexNode			xlist[MAX_VERTEX_NUM];	// 表头向量
	int				vexnum, arcnum;			// 有向弧的当前顶点数与弧数
}OLGraph;

int LocateVex(OLGraph G, VertexType v);
Status CreateDG(OLGraph &G);

//----- 无向图的邻接多重表存储表示
typedef enum { unvisited, visited } VisitIf;

typedef struct EBox{
	VisitIf			mark;				// 访问标记
	int				ivex, jvex;			// 该边依附的两个顶点的位置
	struct EBox		*ilink, *jlink;		// 分别指向依附这两个顶点的下一条边
	InfoType		*info;				// 该边信息指针
}EBox;

typedef struct VexBox{
	VertexType		data;
	EBox			*firstedge;			// 指向第一条依附该顶点的边
}VerBox;

typedef struct{
	VerBox			adjmulist[MAX_VERTEX_NUM];
	int				vexnum, arcnum;		// 无向图的当前顶点数与边数
}AMLGraph;

#endif