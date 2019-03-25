#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2000 + 10;
const int maxm = 6000 + 10;
int t, n, m, a, b, c, edge_num;
int pre[maxn], dis[maxn], vis[maxn], cnt[maxn];
int q[4*maxn*maxn], head, tail;

struct Edge { int u, v, w, nxt; }edge[maxm];

inline bool Breadth_FS() {
    head = 1, tail = 0;
    q[++tail] = cnt[1] = vis[1] = 1;
    while( tail-head+1 ) {
        int x = q[head]; ++head, vis[x] = 0;
        for(int i = pre[x]; i; i = edge[i].nxt)
            if( dis[edge[i].v] > dis[x] + edge[i].w ) {
                if( ++cnt[edge[i].v] >= n )  return 1;
                dis[edge[i].v] = dis[x] + edge[i].w;
                if( !vis[edge[i].v] ) 
                    q[++tail] = edge[i].v, vis[edge[i].v] = 1;
            }
    }
    return 0;
}

inline void Add_Edge(int u, int v, int w) {
    edge[++edge_num].u = u, edge[edge_num].v = v;
    edge[edge_num].nxt = pre[u], pre[u] = edge_num;
    edge[edge_num].w = w;
}

inline void read(int &x) {
    register char ch = 0;  register int w = 0;  x = 0;
    while( !isdigit(ch) )  w |= ch=='-', ch = getchar();
    while( isdigit(ch) )  x = (x*10) + (ch^48), ch = getchar();
    if( w )  x = -x;
}

int main() {
    scanf("%d", &t);
    while( t-- ) {
        memset(vis, 0, sizeof vis);
        memset(pre, 0, sizeof pre);
        memset(cnt, 0, sizeof cnt);
        memset(dis, 0x3f, sizeof dis);
        dis[1] = edge_num = 0;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i) {
            read(a), read(b), read(c);
            Add_Edge(a, b, c);
            if( c >= 0 ) Add_Edge(b, a, c);
        }
        if( Breadth_FS() )  printf("YE5\n");
        else  printf("N0\n");
    }
    return 0;
}
