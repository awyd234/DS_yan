#ifndef _DFS_BFS_H_
#define _DFS_BFS_H_

void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v));
void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v));
Status display(ALGraph G, int v);

#endif