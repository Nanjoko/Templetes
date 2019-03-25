#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
char str[maxn];
int n, las, cnt[maxn << 1], id[maxn << 1], size[maxn << 1], node_num;

struct Node {
  int child[26], parent, length;
  Node() { parent = length = 0, memset(child, 0, sizeof child); }
  ~Node() {};
} node[maxn << 1];

inline int Insert(int x, int last) {
  int new_node = ++node_num;
  node[new_node].length = node[last].length + 1;
  for( ; !node[last].child[x] && last; last = node[last].parent) node[last].child[x] = new_node;
  if( !last ) node[new_node].parent = 1;
  else {
    int tmp = node[last].child[x];
    if ( node[last].length + 1 == node[tmp].length ) node[new_node].parent = tmp;
    else {
      node[++node_num] = node[tmp], node[node_num].length = node[last].length + 1;
      node[tmp].parent = node[new_node].parent = node_num;
      for( ; last && node[last].child[x] == tmp; last = node[last].parent) node[last].child[x] = node_num;
    }
  }
  size[new_node] = 1;
  return new_node;
}

int main(int argc, char const *argv[])
{
  scanf("%s", str + 1), n = strlen(str + 1), node_num = las = 1;
  for(int i = 1; i <= n; ++i) las = Insert(str[i] - 'a', las);
  for(int i = 1; i <= node_num; ++i) ++cnt[node[i].length];
  for(int i = 1; i <= n; ++i) cnt[i] = cnt[i] + cnt[i - 1];
  for(int i = 1; i <= node_num; ++i) id[cnt[node[i].length]] = i, --cnt[node[i].length];
  long long ans = 0ll;
  for (int i = node_num, p = 0; i; --i) {
   p = id[i], size[node[p].parent] = size[node[p].parent] + size[p];
   if( size[p] > 1 ) ans = max(ans, 1ll * size[p] * node[p].length);
  }
  printf("%lld\n", ans);

  return 0;
}