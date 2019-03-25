#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long u64;
const u64 inf = 1e16 + 10;
const int maxn = 100 + 10;
const int maxm = 5000 + 10;
int n, m, s, t, head[maxn], dis[maxn], cur[maxn], edge_num;

struct Edge { int u, v, nxt; u64 c; }edge[maxm << 1];

u64 Deep_FS(int x, u64 flow) {  //x是当前节点，flow是继承来的能够从这个点分配的最大流量
    if( x==t )  return flow;  //到达汇点，返回从这条增广路上走过的流
    for(int &i = cur[x]; i; i = edge[i].nxt) {  //当前弧优化
        if( dis[edge[i].v] == dis[x] + 1 && edge[i].c ) {  //经过残量不为零的边向下一层推进
            u64 f = Deep_FS(edge[i].v, min(flow, edge[i].c));
            if( f ) {  //统计流过这个点的流量
                if( i & 1 ) edge[i].c -= f, edge[i + 1].c += f;
                else edge[i].c -= f, edge[i - 1].c += f;
                return f;  //斜对称性增减并返回流量
            }
        }
    }
    return 0;
}

inline bool Breadth_FS() {
    queue<int> q;
    while( !q.empty() )  q.pop();
    memset(dis, 0, sizeof dis);
    dis[s] = 1, q.push(s);  //初始化dis[]
    while( !q.empty() ) {  //简单的Breadth_Find_search
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = edge[i].nxt)
            if( edge[i].c && !dis[edge[i].v] ) {
                dis[edge[i].v] = dis[x] + 1, q.push(edge[i].v);
            }
    }
    if( dis[t] )  return 1;
    else return 0;  //若仍存在增广路，返回true，否则false
}

inline u64 Max_Flow() {
    u64 flow, ans = 0;
    while( Breadth_FS() ) {  //若存在增广路
        for(int i = 1; i <= n; ++i)  cur[i] = head[i];  //当前弧初始化为第一条边
        while( flow = Deep_FS(s, inf) )  ans += flow;  //每一条路的流量
    }
    return ans;
}

inline void Add_Edge(int u, int v, u64 c) {  //加边
    edge[++edge_num].u = u, edge[edge_num].v = v;
    edge[edge_num].nxt = head[u], head[u] = edge_num;
    edge[edge_num].c = c;
}

inline void read(int &x) {  //快读
    register char ch = 0;  x = 0;
    while( !isdigit(ch) ) ch = getchar();
    while( isdigit(ch) ) x = (x*10) + (ch^48), ch = getchar();
}

int main(int argc, char const *argv[])
{
    int a, b; u64 c;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i=1; i<=m; ++i) {
        read(a), read(b), scanf("%lld", &c);
        Add_Edge(a, b, c), Add_Edge(b, a, 0);
    }   printf("%lld\n", Max_Flow());
    return 0;
}
