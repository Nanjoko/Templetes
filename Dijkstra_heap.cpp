#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1e5 + 1e1;
const int maxm = 2e5 + 2e1;
const int inf = 1e9 + 2;
typedef pair<int,int> pairs;
priority_queue<pairs, vector<pairs>, greater<pairs> > q;
int n, m, pb, e1, e2, p1, p2, di, edge_num;
int dis[maxn], vis[maxn], head[maxn], a, b, c;

struct Edge{
	int u, v, w, next;
	Edge(int from, int to, int dist, int nxt): u(from), v(to), w(dist), next(nxt){};
	Edge() {};
}edge[maxm];

void Add(int from, int to, int dist) {
	
	edge[++edge_num] = Edge(from, to, dist, head[from]);
	head[from] = edge_num;
}

void Dijkstra(int s) {
	for(int i=1; i<=n; ++i) { dis[i] = inf; }
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push(make_pair(dis[s], s));
	while( !q.empty() ) {
		pairs p = q.top();
		q.pop();
		int x = p.second;
		if( vis[x] ) continue;
		vis[x] = 1;
		for(int i=head[x]; i; i=edge[i].next)
			if( dis[edge[i].v]>dis[x]+edge[i].w ) {
				dis[edge[i].v] = dis[x] + edge[i].w;
				q.push(make_pair(dis[edge[i].v], edge[i].v));
			}
	}
	if( s==pb ) { a = dis[e1]; b = dis[e2]; }
	else if( s==e1 )	{ c = dis[e2]; }
}

int main() {
	scanf("%d%d%d%d%d", &m, &n, &pb, &e1, &e2);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d%d", &p1, &p2, &di);
		Add(p1, p2, di), Add(p2, p1, di);
	}
	Dijkstra(pb), Dijkstra(e1);
	int tmp = min(a, b);
	printf("%d", tmp+c);
	return 0;
}
