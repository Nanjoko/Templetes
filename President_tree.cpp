#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> id;

const int maxn = 2 * 100000 + 10;
int n, m, a[maxn], node_num;

struct Node {
  int sum;
  Node *lchild, *rchild;

  Node() { sum = 0, lchild = rchild = NULL; }
  ~Node() {};
} node[25 * maxn], *root[maxn];

class Segment_tree {
public:
  void Build(Node *root, int l, int r) {
    root->lchild = &node[++node_num], root->rchild = &node[++node_num];
    if( l == r ) return ;
    int mid = (l + r) >> 1;
    Build(root->lchild, l, mid), Build(root->rchild, mid + 1, r);
  }

  void Insert(Node *root, Node *&new_root, int l, int r, int pos) {
    node[++node_num] = *root, new_root = &node[node_num], ++new_root->sum;
    if( l == r ) return ;
    int mid = (l + r) >> 1;
    if( pos <= mid ) Insert(root->lchild, new_root->lchild, l, mid, pos);
    else Insert(root->rchild, new_root->rchild, mid + 1, r, pos);
  }

  int Querry(Node *root_l, Node *root_r, int l, int r, int pos) {
    if( l == r ) return l;
    int mid = (l + r) >> 1, sum = root_r->lchild->sum - root_l->lchild->sum;
    if( sum >= pos ) return Querry(root_l->lchild, root_r->lchild, l, mid, pos);
    else return Querry(root_l->rchild, root_r->rchild, mid + 1, r, pos - sum);
  }
} tree;

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline int Get_num(int x) {
  return lower_bound(id.begin(), id.end(), x) - id.begin() + 1;
}

int main(int argc, char const *argv[])
{
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) a[i] = read(), id.push_back(a[i]);
  sort(id.begin(), id.end());
  id.erase(unique(id.begin(), id.end()), id.end());
  root[0] = &node[0], tree.Build(root[0], 1, n);
  for(int i = 1; i <= n; ++i) {
    // printf("%s\n", root[i - 1] == 0 ? "true" : "false");
    tree.Insert(root[i - 1], root[i], 1, n, Get_num(a[i]));
  }
  while( m-- ) {
    int l = read(), r = read(), k = read();
    printf("%d\n", id[tree.Querry(root[l - 1], root[r], 1, n, k) - 1]);
  }

  return 0;
}