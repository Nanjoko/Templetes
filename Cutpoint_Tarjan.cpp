#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;

const int maxn = 200000 + 10;
int dfn[maxn], low[maxn], col[maxn], cnt[maxn], head[maxn];
int ans[maxn], cut[maxn], p, top, dfn_num, col_num, edge_num;

struct Edge{ int u, v, nxt; }edge[maxn << 1];

inline int read() {
  register char ch = 0; register int x = 0;
  while( !isdigit(ch) ) ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return x;
}

void Tarjan(int s) {
  int root = 0;
  dfn[s] = low[s] = ++dfn_num;
  for(int i = head[s]; i; i = edge[i].nxt) {
    int v = edge[i].v;
    if( !dfn[v] ) {
      Tarjan(v), low[s] = min(low[s], low[v]);
      if( low[v] >= dfn[s] && s != p ) cut[s] = 1;
      if( s == p ) ++in_deg;
    }
    low[s] = min(low[s], dfn[v]);
    if( s == p && in_deg >= 2 ) cut[s] = 1;
  }
}

int main(int argc, char const *argv[]) {
  int n = read(), m = read(), t = 0;
  for(int i = 1; i <= m; ++i) {
    int x = read(), y = read();
    edge[++edge_num].u = x, edge[edge_num].v = y;
    edge[edge_num].nxt = head[x], head[x] = edge_num;
    edge[++edge_num].u = y, edge[edge_num].v = x;
    edge[edge_num].nxt = head[y], head[y] = edge_num;
  }
  for(int i = 1; i <= n; ++i) if( !dfn[i] )  p = i, Tarjan(i);
  for(int i = 1; i <= n; ++i) if( cut[i] ) ans[++t] = i;
  printf("%d\n", t);
  for(int i = 1; i <= t; ++i) printf("%d ", ans[i]);
  
  return 0;
}