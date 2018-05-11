/*
*
* Create By ChenXiaodie, TangNi, CKj, PengHaoyun, 2018
*
*/


#pragma once
#define INF 0x3f3f3f3f
#include "basic.h"
#include "SqQueue.h"


/*
*
* Create By ChenXiaodie,2018
*
*/


/*adjacency matrix */

template<typename T> struct VertexType
{
	int no;         //Vertex number
	T info;		//Other information at the vertex
};

//The storage structure of adjacency matrix 
template<typename T> struct MatGraph
{
	int edges[MAX_SIZE][MAX_SIZE];    //adjacency matrix 
	int n, e;                      //Vertex number, edge number 
	VertexType<T> ves[MAX_SIZE];   //Store vertex information 
};


/* adjacency list*/

//Side node storage structure
template <typename T> struct ArcNode
{
	int adjvex;  //Terminal number 
	ArcNode<T> *nextarc;
	T weight; //information
};

//Head node storage structure 
template <typename T> struct VNode
{
	T info;
	ArcNode<T> *firstarc; //Point to the first side node 
};

//use for topological sorting
template <typename T> struct NewVNode
{
	VertexType<T> data;  //information
	int count;   //The degree of entry of the vertex.
	ArcNode<T> *firstarc;
};

//The storage structure of adjacency list
template <typename T> struct AdjGraph
{
	T adjlist[MAX_SIZE];  //The number group of Head node 
	int n, e;
};

//use for Kruskal's algrithm
typedef struct
{
	int u;	//�ߵ���ʼ����
	int v;	//�ߵ���ֹ����
	int w;	//�ߵ�Ȩֵ
}Edge;

//Print adjacency matrix 
template <typename T> void DispMatGraph(MatGraph<T> g)
{
	int i, j;
	for (i = 0; i < g.n; i++) {
		for (j = 0; j < g.n; j++) {
			cout << g.edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//Create adjacency list
template <typename T> void CreateAdj(AdjGraph<T> *&G, int A[MAX_SIZE][MAX_SIZE], int n, int e)
{
	int i, j;
	ArcNode<int> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < n; i++) {
		G->adjlist[i].firstarc = 0;        //������ͷ����ָ�����ó�ֵ
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j >= 0; j--) {      //����ڽӾ����ÿ��Ԫ��
			if (A[i][j] != 0 && A[i][j] != INF) {         //����һ����
				p = new ArcNode<int>;                       //����һ�����P
				p->adjvex = j;                          //����ڽӵ�
				p->weight = A[i][j];                      //���Ȩ
				p->nextarc = G->adjlist[i].firstarc;            //����ͷ�巨������p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n;
	G->e = e;
}

template <typename T> void CreateMatGraph(MatGraph<T> *&G, int A[MAX_SIZE][MAX_SIZE], int n, int e)
{
	G = new MatGraph<T>;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			G->edges[i][j] = A[i][j];
		}
		G->ves[i].no = i;
	}
	G->e = e; G->n = n;
}

//Print adjacency list
template <typename T> void DispAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<int> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		cout << setw(3) << setfill('0') << i << ": ";   //���������
		while (p != 0) {
			cout << setw(3) << setfill('0') << p->adjvex << "[" << p->weight << "] ->";
			if (p->nextarc == 0)
				cout << "��";
			p = p->nextarc;
		}
		cout << endl;
	}
	cout << endl;
}

//Destroy adjacency list
template <typename T> void DestroyAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<int> *p, *pre;
	for (i = 0; i < G->n; i++) {
		pre = G->adjlist[i].firstarc;
		if (pre != 0) {
			p = pre->nextarc;
			while (p != 0) {
				delete pre;
				pre = p; p = p->nextarc;
			}
			delete pre;
		}
	}
	delete G;
}


//p261 ����8.2�� Converting the adjacency matrix into a adjacency list 
template <typename T1, typename T2> void MatToList(MatGraph<T1> g, AdjGraph<T2> *&G)
{
	int i, j;
	ArcNode<T1> *p;
	G = new AdjGraph<T2>;
	for (i = 0; i < g.n; i++) {
		G->adjlist[i].firstarc = 0;
	}
	for (i = 0; i < g.n; i++) {
		for (j = g.n - 1; j >= 0; j--) {      //����ڽӾ����ÿ��Ԫ��
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {         //����һ����
				p = new ArcNode<T1>;                       //����һ�����P
				p->adjvex = j;                          //����ڽӵ�
				p->weight = g.edges[i][j];                      //���Ȩ
				p->nextarc = G->adjlist[i].firstarc;            //����ͷ�巨������p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = g.n; G->e = g.e;
}

//p261 ����8.2�� Converting adjacency tables into adjacency matrices 
template <typename T1, typename T2> void ListToMat(AdjGraph<T2> *&G, MatGraph<T1> &g)
{
	int i;
	ArcNode<T1> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n; g.e = G->e;
}


/*
*
* Create By TangNi,2018
*
*/

//Zero the tag
template<typename T> void Zero(AdjGraph<T> *G, int visited[])
{
	for (int i = 0; i < G->n; i++) {
		visited[i] = 0;
	}
}

//Depth First Search
template<typename T> void DFS(AdjGraph<T> *G, int v, int visited[])
{
	ArcNode<int> *p;
	visited[v] = 1;                //���Է��ʱ��
	cout << v << " ";                     //��������ʶ���ı��
	p = G->adjlist[v].firstarc;    //pָ�򶥵�v�ĵ�һ���ڽӵ�
	while (p != 0) {
		if (visited[p->adjvex] == 0) {
			DFS(G, p->adjvex, visited);     //��p->adjvex����δ�����ʣ��ݹ������
		}
		p = p->nextarc;            //pָ�򶥵�v����һ���ڽӵ�
	}
}

//Breadth First Search
template<typename T> void BFS(AdjGraph<T> *G, int v, int visited[])
{
	int w;
	ArcNode<int> *p;
	SqQueue<int> *qu;          //���廷�ζ���ָ��
	InitQueue(qu);          //��ʼ������
	cout << v << " ";	
	Zero(G, visited);         //�������
	visited[v] = 1;
	enQueue(qu, v);
	while (!QueueEmpty(qu)) {
		deQueue(qu, w);         //����һ������w
		p = G->adjlist[w].firstarc;  //ָ��w�ĵ�һ���ڽӵ�
		while (p != 0) {             //����w�������ڽӵ�
			if (visited[p->adjvex] == 0) {
				cout << p->adjvex << " ";
				visited[p->adjvex] = 1;
				enQueue(qu, p->adjvex); //�ö������
			}
			p = p->nextarc;
		}
	}
}

//Non-connected graph Depth First Search, visited every vertex
template<typename T> void N_Con_DFS(AdjGraph<T> *G)
{
	int i;
	int visited[MAX_SIZE] = { 0 };        //�������
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			DFS(G, i, visited);
		}
	}
}

//Non-connected graph Breadth First Search, visited every vertex
template<typename T> void N_Con_BFS(AdjGraph<T> *G)
{
	int i;
	int visited[MAX_SIZE] = { 0 };         //�������
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			BFS(G, i, visited);
		}
	}
}

// P269����8.3��Determine whether the undirected graph is connected
template<typename T> bool Connect(AdjGraph<T> *G)
{
	int i;
	bool flag = true;
	int visited[MAX_SIZE] = { 0 };         //�������
	DFS(G, 0, visited);        //�Ӷ���0��ʼ������ȱ���
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			flag = false;     //���ж���û�б����ʵ���˵���ǲ���ͨ��
			break;
		}
	}
	return flag;
}


/*Application based on Depth First Search*/


// P269����8.4��Find simple path of u to v
template<typename T> void ExistPath(AdjGraph<T> *G, int u, int v, bool &has, int visited[])
{
	int w;
	ArcNode<int> *p;
	visited[u] = 1;        //���Է��ʱ��
	if (u == v) {
		has = true;
		return;
	}
	p = G->adjlist[u].firstarc;  //pָ�򶥵�u�ĵ�һ���ڽӵ�
	while (p != 0) {
		w = p->adjvex;                //wΪ����u�ĵ�һ���ڽӵ�
		if (visited[w] == 0) {       //��w����Ϊ���ʣ��ݹ������
			ExistPath(G, w, v, has, visited);
		}
		p = p->nextarc;
	}
}

// P270����8.5��Disp simple path of u to v, d is the length of path
template<typename T> void FindaPath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<int> *p;
	visited[u] = 1;
	d++;
	path[d] = u;        //·������d����1������u���뵽·����
	if (u == v) {
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
		return;
	}
	p = G->adjlist[u].firstarc;  //pָ�򶥵�u�ĵ�һ���ڽӵ�
	while (p != 0) {
		w = p->adjvex;                //wΪ����u���ڽӵ�
		if (visited[w] == 0) {       //��w����Ϊ���ʣ��ݹ������
			FindaPath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
}

// P271����8.6��Disp all the simple pathes of u to v.
template<typename T> void FindAllPath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<int> *p;
	d++;
	path[d] = u;
	visited[u] = 1;
	if (u == v && d >= 0) {
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (visited[w] == 0) {
			FindAllPath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;    //�ָ�������ʹ�ö��������ʹ��
}

// P272����8.7��Disp all paths of length l from u to v
template<typename T> void PathLenAll(AdjGraph<T> *G, int u, int v, int l, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<int> *p;
	visited[u] = 1;
	d++;
	path[d] = u;
	if (v == u && d == l) {              //����Ϊlʱ���·��
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
		
	}
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (visited[w] == 0) {
			PathLenAll(G, w, v, l, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;
}

//P274����8.8��Disp all the simple cycle which through k
template<typename T> void FindCyclePath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<int> *p;
	visited[u] = 1;
	d++;
	path[d] = u;
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (w == v && d > 0) {
			for (i = 0; i <= d; i++) {
				cout << path[i] << " ";
			}
			cout << v << endl;
		}
		if (visited[w] == 0) {
			FindCyclePath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;
}


/*Application based on Breadth First Search*/


// P276����8.9��Inverse disp the shortest path from u to v
template<typename T> void ShortPath(AdjGraph<T> *G, int u, int v, int visited[])
{
	ArcNode<int> *p;
	int w, i;
	Quere<T> qu[MAX_SIZE];       //�ǻ��ζ���
	int front = -1, rear = -1;   //���е�ͷָ�롢βָ��
	rear++;
	qu[rear].data = u;           //����u����
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear) {     //�Ӳ���ѭ��
		front++;                //���Ӷ���w
		w = qu[front].data;
		if (w == v) {            //����vʱ�����·�����˳�
			i = front;
			while (qu[i].parent != -1) {    //ͨ�����������·��
				cout << qu[i].data << " ";
				i = qu[i].parent;
			}
			cout << qu[i].data << endl;
			break;
		}
		p = G->adjlist[w].firstarc;     //w�ĵ�һ���ڽӵ�
		while (p != 0) {
			if (visited[p->adjvex] == 0) {  //��wδ���ʹ����ڽӵ����
				rear++;
				qu[rear].data = p->adjvex;
				qu[rear].parent = front;
			}
			p = p->nextarc;        //��w����һ���ڽӵ�
		}
	}
}


// P277����8.10��Find the furthest vertex from v, using SqQueue instead of Qu[]
template<typename T> int Maxdist(AdjGraph<T> *G, int v, int visited[])
{
	ArcNode<int> *p;
	SqQueue<int> *qu;
	InitCycleQueue(qu);
	int i, j, k;
	enCycleQueueF(qu, v);    //����v����
	visited[v] = 1;      //���v�ѷ���
	while (!QueueEmpty(qu)) {
		deCycleQueueR(qu, k);   //����k����
		p = G->adjlist[k].firstarc;     //�ҵ�һ���ڽӵ�
		while (p != 0) {                //����δ�����ʹ����ڽӵ����
			j = p->adjvex;              //�ڽӵ�Ϊ����j
			if (visited[j] == 0) {
				visited[j] = 1;
				enCycleQueueF(qu, j);
			}
			p = p->nextarc;
		}
	}
	return k;
}

/*
*
* Create By PHY,2018
*
*/

//Display the shotest path
template<typename T>void Dispath(MatGraph<T> g, int dist[],int path[], int S[], int v)
{
	int i, j, k;
	int apath[MAX_SIZE], d;   //���һ�����··�������򣩼��䶥�����
	for(i=0;i<g.n;i++)       //ѭ������Ӷ���v��i��·��
		if (S[i] == 1 && i != v)
		{
			cout << "�Ӷ���" << v << "������" << i << "��·������Ϊ��" << dist[i] << '\t' << "·��Ϊ��";
			d = 0;
			apath[d] = i;  //���·���ϵ��յ�
			k = path[i];
			if (k == -1)  //û��·�������
				cout << "��·��" << endl;
			else       //����·��ʱ�����·��
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v;   //���·���ϵ����
				cout << apath[d];   //��������
				for (j = d - 1; j >= 0; j--)   //�������������
					cout << "," << apath[j];
				cout << endl;
			}
		}
}


//Display the shotest path by Dijkstra
template<typename T> void Dijkstra(MatGraph<T> g, int v)
{
	int dist[MAX_SIZE], path[MAX_SIZE];
	int S[MAX_SIZE];     //S[i]=1��ʾ����i��S�У�S[i]=0��ʾ����i��U��
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];    //�����ʼ��
		S[i] = 0;//S[]�ÿ�
		if (g.edges[v][i] < INF)    //·����ʼ��
			path[i] = v;    //����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i] = -1;    //����v������iû��ʱ���ö���i��ǰһ������Ϊ-1
	}
	S[v] = 1;
	path[v] = 0;    //Դ����v����S��
	for (i = 0; i < g.n - 1; i++)   //ѭ��ֱ�����ж�������·�������
	{
		MINdis = INF;   //MINdis����󳤶ȳ�ֵ
		for(j=0;j<g.n;j++)    //ѡȡ����S�У���U�У��Ҿ�����С���·�����ȵĶ���v
			if (S[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;   //����u����S��
		for(j=0;j<g.n;j++)   //�޸Ĳ���S�У���U�У��Ķ�������·��
			if(S[j]==0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v);   //������·��
}


/*
*
* Create By CXD,2018
*
*/

//topological sorting
template <typename T> void TopSort(AdjGraph<T> *G)
{
	int i, j;
	int St[MAX_SIZE];  //��˳��ջ������Ϊ0�Ķ���
	int top = -1;     //ջ��ָ��
	ArcNode<int> *p;
	for (i = 0; i < G->n; i++) {
		G->adjlist[i].count = 0;      //����ó�ֵ0
	}
	for (i = 0; i < G->n; i++) {     //�����ж�������
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			G->adjlist[p->adjvex].count++;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G->n; i++) {      //�����Ϊ0�Ķ�����ջ
		if (G->adjlist[i].count == 0) {
			top++;
			St[top] = i;
		}
	}
	while (top > -1) {   //ջ����ʱѭ��
		i = St[top]; top--;    //��ջһ������
		cout << i;            //����ö���
		p = G->adjlist[i].firstarc;       //�ҵ�һ���ڽӵ�
		while (p != 0) {       //������i�ĳ����ڽӵ����ȼ�1
			j = p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count == 0) {   //�����Ϊ0���ڽӵ��ջ
				top++;
				St[top] = j;
			}
			p = p->nextarc;       //����һ���ڽӵ�
		}
	}
	cout << endl;
}


/*
*
* Create By CKJ,2018
*
*/

template <typename T> void Prim(MatGraph<T> *g, int v)
{
	int lowcost[MAX_SIZE];
	int MIN;
	int closest[MAX_SIZE], i, j, k;
	for (i = 0; i < g->n; i++)		//��lowcost[]��closest[]�ó�ֵ
	{
		lowcost[i] = g->edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < g->n; i++)		//�ҳ�(n-1)�����
	{
		MIN = INF;
		for (j = 0; j < g->n; j++)		//��(V-U)���ҳ���U����Ķ���k
		{
			if (lowcost[j] != 0 && lowcost[j] < MIN)
			{
				MIN = lowcost[j];
				k = j;		//��¼�������ı��
			}
		}
		cout << "�ߣ�" << closest[k] << "," << k << "��ȨΪ��" << MIN << endl;	//�����С��������һ����
		lowcost[k] = 0;		//���k�Ѿ����뵽U
		for (j = 0; j < g->n; j++)		//��(V-U)�еĶ���j���е���
		{
			if (lowcost[j] != 0 && g->edges[k][j] < lowcost[j])
			{
				lowcost[j] = g->edges[k][j];
				closest[j] = k;		//�޸�����lowcost��closest
			}
		}
	}
}

void InserSort(Edge a[], int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (a[j].w > a[j + 1].w) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}

template <typename T> void Kruskal(MatGraph<T> *g)
{
	int i, j, u1, v1, sn1, sn2, k;
	int vset[MAX_SIZE];
	Edge E[MAX_SIZE];		//���ͼ�е����б�
	k = 0;					//e������±��0��ʼ��
	for (i = 0; i < g->n; i++)		//��g�����߼�E�����ظ�ѡȡͬһ����
	{
		for (j = 0; j <= i; j++)
		{
			if (g->edges[i][j] != 0 && g->edges[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g->edges[i][j];
				k++;
			}
		}
	}
	InserSort(E, g->e);		//����ֱ�Ӳ��������E���鰴Ȩֵ��������
	for (i = 0; i < g->e; i++)		//��ʼ����������
	{
		vset[i] = i;
	}
	k = 1;		//k��ʾ��ǰ�����������ĵڼ����ߣ���ֵΪ1
	j = 0;		//E�бߵ��±꣬��ֵΪ0
	while (k < g->n)
	{
		u1 = E[j].u; v1 = E[j].v;		//ȡһ���ߵ���������
		sn1 = vset[u1];
		sn2 = vset[v1];		//�ֱ�õ��������������ļ��ϱ��
		if (sn1 != sn2)		//�����������ڲ�ͬ�ļ��ϣ��ñ�����С��������һ����
		{
			cout << "(" << u1 << "," << v1 << "): " << E[j].w << endl;		//�����С��������һ����
			k++;		//���ɱ�����1
			for (i = 0; i < g->n; i++)		//��������ͳһ���
				if (vset[i] == sn2)			//���ϱ��Ϊsn2�ĸ�Ϊsn1
					vset[i] = sn1;
		}
		j++;		//ɨ����һ����
	}
}


void GraphExample()
{
	AdjGraph<VNode<int>> *G;
	int n = 5, e = 8;
	int A[MAX_SIZE][MAX_SIZE] =  //����ͼ
	{
		{ 0,1,0,1,1 },
		{ 1,0,1,1,0 },
		{ 0,1,0,1,1 },
		{ 1,1,1,0,1 },
		{ 1,0,1,1,0 }
	};
	CreateAdj(G, A, n, e);

	//p261 ����8.2��
	MatGraph<int> g;
	memcpy(g.edges, A, MAX_SIZE * MAX_SIZE * sizeof(int));
	g.n = n; g.e = e;
	MatToList(g, G);
	cout << "ͼG:\n";
	DispAdj(G);

	memset(g.edges, 0, MAX_SIZE * MAX_SIZE * sizeof(int));
	ListToMat(G, g);
	cout << "ͼg:\n";
	DispMatGraph(g);

	int visited[MAX_SIZE] = { 0 };
	cout << "Depth First Search: "; DFS(G, 0, visited);
	cout << endl << "Breadth First Search: "; BFS(G, 0, visited);
	cout << endl << "Non-connected graph Depth First Search: "; N_Con_DFS(G);
	cout << endl << "Non-connected graph Breadth First Search: "; N_Con_BFS(G);
	cout << endl;
	
	// P269����8.3��
	if (Connect(G)) {
		cout << " is connected graph. " << endl;
	}
	cout << endl;

	// P269����8.4�� P270����8.5�� P271����8.6��
	int d = -1, path[MAX_SIZE] = { 0 };
	int u = 1, v = 4;
	bool has = false;
	Zero(G, visited);         //�������
	ExistPath(G, u, v, has,visited);
	if (has) {
		cout << "Can find the simple path of " << u << " to " << v << endl;
		Zero(G, visited);
		cout << "A simple path of " << u << " to " << v << " is: "; 
		FindaPath(G, u, v, path, d, visited);
		Zero(G, visited);  //���ʳ�ʼֵ
		d = -1;
		cout << "All simple path of " << u << " to " << v << " is: "<<endl; 
		FindAllPath(G, u, v, path, d, visited);
	}
	cout << endl;

	// P272����8.7��
	Zero(G, visited);  //���ʳ�ʼֵ
	int Path[MAX_SIZE] = { 0 };
	u = 1, v = 4;
	int l = 3;
	cout << "ͼG:\n";
	DispAdj(G);
	cout << "All " << l << " length simple path of " << u << " to " << v << " is: " << endl;
	PathLenAll(G, u, v, l, Path, -1, visited);
	cout << endl;

	//P274����8.8��
	AdjGraph<VNode<int>>  *G1;
	int A1[MAX_SIZE][MAX_SIZE] =
	{
		{ 0,1,1,0,0 },
		{ 0,0,1,0,0 },
		{ 0,0,0,1,1 },
		{ 0,0,0,0,1 },
		{ 1,0,0,0,0 }
	};
	CreateAdj(G1, A1, 5, 7);
	int k = 1;
	cout << "All the cycle path through "<<k <<" is :" << endl; FindCyclePath(G1, k, k, path, d, visited);

	// P276����8.9��
	Zero(G1, visited);
	cout << "Inverse disp the shortest path from "<<u <<" to " <<v <<" : "; ShortPath(G1, u, v, visited);

	// P277����8.10��
	Zero(G1, visited);
	int ver;
	ver = Maxdist(G1, v, visited);
	cout << "The furthest vertex from " <<v<<" is " << k << endl;

	//P303 ����8.14��
	AdjGraph<NewVNode<int>> *M;
	int C[MAX_SIZE][MAX_SIZE] =
	{
		{ 0,1,INF,INF,INF,INF },
		{ INF,0,1,INF,INF,INF },
		{ INF,INF,0,1,INF,INF },
		{ INF,INF,INF,0,INF,INF },
		{ INF,1,INF,INF,0 ,1 },
		{ INF ,INF ,INF ,1,INF ,0 }
	};
	n = 6; e = 6;
	CreateAdj(M, C, n, e);
	cout << "ͼM:\n"; 
	DispAdj(M);
	cout << "A topological sort of M:";  TopSort(M); 
	DestroyAdj(M);
	cout << endl;

	//P284 Prim arithmatic
	int A2[MAX_SIZE][MAX_SIZE] = {
		{ 0, 28, INF, INF, INF, 10, INF },
		{ 28, 0, 16, INF, INF, INF, 14 },
		{ INF, 16, 0, 12, INF, INF, INF },
		{ INF, INF, 12, 0, 22, INF, 18 },
		{ INF, INF, INF, 22, 0, 25, 24 },
		{ 10, INF, INF, INF, 25, 0, INF },
		{ INF, 14, INF, 18, 24, INF, 0 }
	};
	MatGraph<int> *Q;
	CreateMatGraph(Q, A2, 7, 9);
	Prim(Q, 0);

	//P288 Kruskal algrethm
	Kruskal(Q);

	DestroyAdj(G);
}