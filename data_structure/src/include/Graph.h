#pragma once
#define INF 0x3f3f3f3f
#include "basic.h"


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

//The storage structure of adjacency list
template <typename T> struct AdjGraph
{
	VNode<T> adjlist[MAX_SIZE];  //The number group of Head node 
	int n, e;
};


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
	ArcNode<T> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < n; i++) {
		G->adjlist[i].firstarc = 0;        //������ͷ����ָ�����ó�ֵ
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j >= 0; j--) {      //����ڽӾ����ÿ��Ԫ��
			if (A[i][j] != 0 && A[i][j] != INF) {         //����һ����
				p = new ArcNode<T>;                       //����һ�����P
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

//Print adjacency list
template <typename T> void DispAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<T> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		cout << setw(3) << setfill('0') << i << ": ";   //���������
		while (p != 0) {
			cout << setw(3) << setfill('0') << p->adjvex << "[" << p->weight << "]->";
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
	ArcNode<T> *p, *pre;
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
template <typename T> void MatToList(MatGraph<T> g, AdjGraph<T> *&G)
{
	int i, j;
	ArcNode<T> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < g.n; i++) {
		G->adjlist[i].firstarc = 0;
	}
	for (i = 0; i < g.n; i++) {
		for (j = g.n - 1; j >= 0; j--) {      //����ڽӾ����ÿ��Ԫ��
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {         //����һ����
				p = new ArcNode<T>;                       //����һ�����P
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
template <typename T> void ListToMat(AdjGraph<T> *&G, MatGraph<T> &g)
{
	int i;
	ArcNode<T> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n; g.e = G->e;
}

//Depth First Search
template<typename T> void DFS(AdjGraph<T> *G, int v, int visited[])
{
	ArcNode<T> *p;
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
	int w, i;
	ArcNode<T> *p;
	SqQueue<T> *qu;          //���廷�ζ���ָ��
	InitQueue(qu);          //��ʼ������
	cout << v << " ";
	for (i = 0; i < G->n; i++) {
		visited[i] = 0;
	}
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
template<typename T> void N_Con_DFS(AdjGraph<T> *G, int visited[])
{
	int i;
	for (i = 0; i < G->n; i++) {   //�������
		visited[i] = 0;
	}
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			DFS(G, i, visited);
		}
	}
}

//Non-connected graph Breadth First Search, visited every vertex
template<typename T> void N_Con_BFS(AdjGraph<T> *G, int visited[])
{
	int i;
	for (i = 0; i < G->n; i++) {   //�������
		visited[i] = 0;
	}
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			BFS(G, i, visited);
		}
	}
}


//Display the shotest path
template<typename T>void Dispath(MatGraph<T> g, int dist[],int path[], int S[], int v)
{
	int i, j, k;
	int apath[MAX_SIZE], d;//���һ�����··�������򣩼��䶥�����
	for(i=0;i<g.n;i++)//ѭ������Ӷ���v��i��·��
		if (S[i] == 1 && i != v)
		{
			cout << "�Ӷ���" << v << "������" << i << "��·������Ϊ��" << dist[i] << '\t' << "·��Ϊ��";
			d = 0;
			apath[d] = i;//���·���ϵ��յ�
			k = path[i];
			if (k == -1)//û��·�������
				cout << "��·��" << endl;
			else//����·��ʱ�����·��
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v;//���·���ϵ����
				cout << apath[d];//��������
				for (j = d - 1; j >= 0; j--)//�������������
					cout << "," << apath[j];
				cout << endl;
			}
		}
}


//Display the shotest path by Dijkstra
template<typename T> void Dijkstra(MatGraph<T> g, int v)
{
	int dist[MAX_SIZE], path[MAX_SIZE];
	int S[MAX_SIZE];//S[i]=1��ʾ����i��S�У�S[i]=0��ʾ����i��U��
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];//�����ʼ��
		S[i] = 0;//S[]�ÿ�
		if (g.edges[v][i] < INF)//·����ʼ��
			path[i] = v;//����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i] = -1;//����v������iû��ʱ���ö���i��ǰһ������Ϊ-1
	}
	S[v] = 1;
	path[v] = 0;//Դ����v����S��
	for (i = 0; i < g.n - 1; i++)//ѭ��ֱ�����ж�������·�������
	{
		MINdis = INF;//MINdis����󳤶ȳ�ֵ
		for(j=0;j<g.n;j++)//ѡȡ����S�У���U�У��Ҿ�����С���·�����ȵĶ���v
			if (S[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;//����u����S��
		for(j=0;j<g.n;j++)//�޸Ĳ���S�У���U�У��Ķ�������·��
			if(S[j]==0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v);//������·��
}



void GraphExample()
{
	AdjGraph<int> *G;
	int n = 5, e = 7;
	int A[MAX_SIZE][MAX_SIZE] =  //����ͼ
	{
		{ 0,1,0,1,1 },
		{ 1,0,1,1,0 },
		{ 0,1,0,1,1 },
		{ 1,1,1,0,1 },
		{ 1,0,1,1,0 }
	};
	CreateAdj(G, A, n, e);
	DispAdj(G);

	//p261 ����8.2��
	MatGraph<int> g;
	memcpy(g.edges, A, MAX_SIZE * MAX_SIZE * sizeof(int));
	g.n = n; g.e = e;
	MatToList(g, G);
	DispAdj(G);

	memset(g.edges, 0, MAX_SIZE * MAX_SIZE * sizeof(int));
	ListToMat(G, g);
	DispMatGraph(g);

	int visited[MAX_SIZE] = { 0 };
	cout << "Depth First Search: "; DFS(G, 0, visited);
	cout << endl << "Breadth First Search: "; BFS(G, 0, visited);
	cout << endl << "Non-connected graph Depth First Search: "; N_Con_DFS(G, visited);
	cout << endl << "Non-connected graph Breadth First Search: "; N_Con_BFS(G, visited);

	cout << endl << "Shortest path"<<endl; Dijkstra(g, 0);
	
}