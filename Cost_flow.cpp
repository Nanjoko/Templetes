#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> pairs;

const int maxn = 5000 + 10;
const int maxm = 50000 + 10;
const int iinf = 0x3f3f3f3f;
int n, m, s, t, head[maxn], edge_num;
int dis[maxn], vis[maxn], pre[maxn], rec[maxn];

struct Edge{ int v, f, c, nxt; }edge[maxm << 1];

inline int read() {
  register char ch = 0; register int x = 0;
  while( !isdigit(ch) ) ch = getchar();
  while( isdigit(ch) ) x = (x * 10) +  (ch ^ 48), ch = getchar();
  return x;
}

inline void Add_edge(int u, int v, int f, int c) {
  edge[++edge_num].v = v, edge[edge_num].f = f, edge[edge_num].c = c;
  edge[edge_num].nxt = head[u], head[u] = edge_num;
}

inline bool SPFA(int s, int t) {
  queue<int> q;
  memset(vis, 0, sizeof vis);
  memset(dis, 0x3f, sizeof dis);
  dis[s] = 0, vis[s] = 1, q.push(s);
  while( !q.empty() ) {
    int x = q.front();  q.pop();
    vis[x] = 0;
    for(int i = head[x]; i; i = edge[i].nxt)
      if( dis[edge[i].v] > dis[x] + edge[i].c && edge[i].f ) {
        dis[edge[i].v] = dis[x] + edge[i].c;
        pre[edge[i].v] = x, rec[edge[i].v] = i;
        if( !vis[edge[i].v] ) vis[edge[i].v] = 1, q.push(edge[i].v);
      }
  }
  if( dis[t] == iinf ) return false;
  else return true;
}

inline pairs Edmond_Karp(int s, int t) {
  int k, min_flow, min_cost = 0, max_flow = 0;
  while( SPFA(s, t) ) {
    k = t, min_flow = iinf;
    while( k != s ) min_flow = min(min_flow, edge[rec[k]].f), k = pre[k];
    k = t, max_flow += min_flow;
    while( k != s ) {
      min_cost += min_flow * edge[rec[k]].c;
      if( rec[k] & 1 ) {
        edge[rec[k]].f -= min_flow, edge[rec[k] + 1].f += min_flow;
      } else edge[rec[k]].f -= min_flow, edge[rec[k] - 1].f += min_flow;
      k = pre[k];
    }
  }
  return make_pair(max_flow, min_cost);
}

int main(int argc, char* const argv[])
{
  freopen("testdata.in", "r", stdin);
  
  scanf("%d%d%d%d", &n, &m, &s, &t);
  for(int i = 1; i <= m; ++i) {
    int u = read(), v = read(), f = read(), c = read();
    Add_edge(u, v, f, c), Add_edge(v, u, 0, -c);
  }
  pairs ans = Edmond_Karp(s, t);
  printf("%d %d\n", ans.first, ans.second);

  printf("_______________________________________________\n");
  printf("Process Exited Correctly With A Return Value 0.\n");
  printf("All Rights Reserved By Kimitsu Nanjo In 2018.\n\n");
  return 0;
}