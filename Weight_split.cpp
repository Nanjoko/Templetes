#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lch (x << 1)
#define rch (x << 1) | 1

const int iinf = 2147483647;
const int maxn = 60000 + 10;
int n, head[maxn], value[maxn], dfn[maxn], idfn[maxn], dfn_num;
int top[maxn], size[maxn], son[maxn], pre[maxn], deep[maxn], edge_num;

struct Edge{ int v, nxt; }edge[maxn << 1];

class Seg_tree{
  private:
    int mas[maxn << 1] = {0}, sum[maxn << 1] = {0};
  public:
    inline void Maintain(int x) {
      sum[x] = sum[lch] + sum[rch];
      mas[x] = max(mas[lch], mas[rch]);
    }

    inline void Build(int x, int l, int r) {
      if( l == r ) { sum[x] = mas[x] = value[idfn[l]];  return ; }
      int mid = (l + r) >> 1;
      Build(lch, l, mid), Build(rch, mid + 1, r);
      Maintain(x);
    }

    inline void Update(int x, int l, int r, int ques, int num) {
      if( l == r ) { sum[x] = mas[x] = num;  return ; }
      int mid = (l + r) >> 1;
      if( ques <= mid ) Update(lch, l, mid, ques, num);
      else Update(rch, mid + 1, r, ques, num);
      Maintain(x);
    }

    inline int Querry_max(int x, int l, int r, int quesl, int quesr) {
      if( l >= quesl && r <= quesr ) { return mas[x]; }
      int mid = (l + r) >> 1, ans1 = -iinf, ans2 = -iinf;
      if( quesl <= mid ) ans1 = Querry_max(lch, l, mid, quesl, quesr);
      if( quesr > mid ) ans2 = Querry_max(rch, mid + 1, r, quesl, quesr);
      return max(ans1, ans2);
    }

    inline int Querry_sum(int x, int l, int r, int quesl, int quesr) {
      if( l >= quesl && r <= quesr ) { return sum[x]; }
      int mid = (l + r) >> 1, ans = 0;
      if( quesl <= mid ) ans += Querry_sum(lch, l, mid, quesl, quesr);
      if( quesr > mid ) ans += Querry_sum(rch, mid + 1, r, quesl, quesr);
      return ans;
    }
}tree;

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline void Add_edge(int u, int v) {
  edge[++edge_num].v = v;
  edge[edge_num].nxt = head[u], head[u] = edge_num;
}

inline int Deepfs_1(int x) {
  int tmp = 0;
  for(int i = head[x]; i; i = edge[i].nxt) {
    if( edge[i].v == pre[x] ) continue;
    pre[edge[i].v] = x, deep[edge[i].v] = deep[x] + 1;
    size[x] += Deepfs_1(edge[i].v);
    if( tmp < size[edge[i].v] ) tmp = size[edge[i].v], son[x] = edge[i].v;
  }
  return head[x] ? ++size[x] : size[x] = 1;
}

inline void Deepfs_2(int x, int t) {
  top[x] = t, dfn[x] = ++dfn_num, idfn[dfn_num] = x;
  if( son[x] ) Deepfs_2(son[x], t);
  for(int i = head[x]; i; i = edge[i].nxt)
    if( edge[i].v != son[x] && edge[i].v != pre[x] )
      Deepfs_2(edge[i].v, edge[i].v);
}

inline int Querry_max(int x, int y) {
  int ans = -iinf;
  while( top[x] != top[y] ) {
    if( deep[top[x]] >= deep[top[y]] ) {
      ans = max(ans, tree.Querry_max(1, 1, n, dfn[top[x]], dfn[x]));
      x = pre[top[x]];
    } else {
      ans = max(ans, tree.Querry_max(1, 1, n, dfn[top[y]], dfn[y]));
      y = pre[top[y]];
    }
  }
  if( dfn[x] > dfn[y] ) swap(x, y);
  return max(ans, tree.Querry_max(1, 1, n, dfn[x], dfn[y]));
}

inline int Querry_sum(int x, int y) {
  int ans = 0;
  while( top[x] != top[y] ) {
    if( deep[top[x]] >= deep[top[y]] ) {
      ans += tree.Querry_sum(1, 1, n, dfn[top[x]], dfn[x]);
      x = pre[top[x]];
    } else {
      ans += tree.Querry_sum(1, 1, n, dfn[top[y]], dfn[y]);
      y = pre[top[y]];
    }
  }
  if( dfn[x] > dfn[y] ) swap(x, y);
  return ans + tree.Querry_sum(1, 1, n, dfn[x], dfn[y]);
}

int main(int argc, char* const argv[])
{
  scanf("%d", &n);
  for(int i = 1; i < n; ++i) {
    int u = read(), v = read();
    Add_edge(u, v), Add_edge(v, u);
  }
  for(int i = 1; i <= n; ++i) value[i] = read();
  size[1] = Deepfs_1(1), Deepfs_2(1, 1), tree.Build(1, 1, n);

  int q = read();  char ques[10];
  for(int i = 1; i <= q; ++i) {
    scanf("%s", ques);
    int u = read(), v = read();
    switch( ques[1] ) {
      case 'S': printf("%d\n", Querry_sum(u, v)); break;
      case 'M': printf("%d\n", Querry_max(u, v)); break;
      case 'H': tree.Update(1, 1, n, dfn[u], v); break;
    }
  }

//   printf("_______________________________________________\n");
//   printf("Process Exited Correctly With A return Value 0.\n");
//   printf("All rights reserved By Kimitsu Nanjo In 2018.\n\n");
  return 0;
}