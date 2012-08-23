/* 最小费用流
 * 邻接表 + SPFA + Dinic
 * 时间复杂度：O(V*E*f)
 * */
#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 50005;
const int INF = INT_MAX / 2;

struct Edge {
	int to;
	int c, w;
	int next;
	Edge(int tto=0, int tc=0, int tw=0, int tn=-1) : to(tto), c(tc), w(tw), next(tn) {}
};
Edge E[MAXN * 4];
int nE, V[MAXN]; // nE 边数，V[]顶点的边链表头，顶点初始化为-1, nE初始化为0

int pre[MAXN];
int path[MAXN];
int sp[MAXN]; // 源点到各个点的费用
int que[MAXN]; 
bool inq[MAXN];

void initNetwork(int n = MAXN) {
	memset(V, -1, sizeof(V[0]) * n);
	nE = 0;
}

void addEdge(int u, int v, int c, int w, int rc = 0) { // rc是反向弧的容量
	E[nE] = Edge(v, c, w, V[u]);
	V[u] = nE++;
	E[nE] = Edge(u, rc, -w, V[v]);
	V[v] = nE++;
}

/* SPFA，根据需要使用cnt[]数组统计顶点入队次数，入队次数>=n则表示存在负权环，
 * 也可以使用dfs深搜，如果遇到已经出现的点说明存在负权环
 * 实际中SPFA算法的效率不稳定，可以使用更加稳定的Dijkstra算法
 * */
bool SPFA(int n, int source, int sink) {
	int *fr = que, *ta = que;
	for (int i = 0; i < n; ++i) sp[i] = INF, inq[i] = false;
	pre[source] = -1;
	sp[source] = 0;
	*ta++ = source;
	inq[source] = true;
	while (fr != ta) {
		if (fr == que + MAXN) fr = que;
		int u = *fr++;
		// 未添加该优化：LLL, Large Label Last 队首的距离比队列的平均距离大的则移到队尾，否则取出, 50%的速度提高
		inq[u] = false;
		for (int i = V[u], v; i != -1; i = E[i].next) {
			v = E[i].to;
			if (E[i].c > 0 && sp[v] > sp[u] + E[i].w) {
				sp[v] = sp[u] + E[i].w;
				pre[v] = u;
				path[v] = i;
				if (false == inq[v]) {
					/* SLF Smal Label First 距离更短的顶点在队列前，此优化效果非常明显，推荐使用
					 * 也可以使用 LLL, Large Label Last 进行优化
					 * */
					if (fr != ta && sp[*fr] > sp[v]) {
						fr--;
						if (fr < que) fr = que + MAXN - 1;
						*fr = v;
					} else {
						if (ta == que + MAXN) ta = que;
						*ta++ = v;
					}
					inq[v] = true;
				}
			}
		}
	}
	return sp[sink] < INF;
}

int argument(int n, int source, int sink) {
	int delta = INF;
	for (int i = sink, e; pre[i] != -1; i = pre[i]) {
		e = path[i];
		if (delta > E[e].c) delta = E[e].c;
	}
	for (int i = sink, e; pre[i] != -1; i = pre[i]) {
		e = path[i];
		E[e].c -= delta;
		E[e^1].c += delta;
	}
	return delta;
}
// 最小费用最大流
// 返回最大流的最小费用
int mincost_maxflow(int n, int source, int sink) {
	int cost = 0; // 费用流 = 费用x流
	while ( SPFA(n, source, sink) ) {
		int delta = argument(n, source, sink);
		cost += delta * sp[sink];
	}
	return cost;
}

int main()
{
	int n, k, nn, source, sink;
	while (EOF != scanf("%d%d", &n, &k)) {
		nn = n * n;
		source = 2 * nn;
		sink = 2 * nn + 1;
		initNetwork();
		for (int i = 0; i < n; ++i) {
			for (int j = 0, d, u, v; j < n; ++j) {
				scanf("%d", &d);
				u = i * n + j;
				addEdge(u, nn + u, 1, -d);
				if (i+1 < n) {
					v = (i + 1) * n + j;
					addEdge(u, v, INF, 0);
					addEdge(nn+u, v, INF, 0);
					addEdge(nn+u, nn+v, INF, 0);
				}
				if (j+1 < n) {
					v = i * n + j + 1;
					addEdge(u, v, INF, 0);
					addEdge(nn+u, v, INF, 0);
					addEdge(nn+u, nn+v, INF, 0);
				}
			}
		}
		addEdge(source, 0, k,  0);
		addEdge(2*nn - 1, sink, k,  0);
		printf("%d\n", -mincost_maxflow(2*nn + 2, source, sink));
	}
	return 0;
}
