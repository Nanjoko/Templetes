#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define lch child[0]
#define rch child[1]

const int maxn = 100000 + 10;
int n, node_num;

struct Node {
  int val, cnt, siz;
  Node *child[2], *pre;
  Node() { val = 0, siz = cnt = 1, pre = child[0] = child[1] = NULL; }
  ~Node() {};
} node[maxn], *p_root;

class Splay {
public:
  inline void Maintain(Node *root) {
    root->siz = root->cnt;
    if( root->lch ) root->siz = root->siz + root->lch->siz;
    if( root->rch ) root->siz = root->siz + root->rch->siz;
  }

  inline bool Choosech(Node *root) { return root->pre->rch == root; }

  inline void Rotate(Node *root) {
    Node *p = root->pre;
    bool pos = Choosech(root);
    p->child[pos] = root->child[!pos];
    if( root->child[!pos] ) root->child[!pos]->pre = p;
    if( root->pre = p->pre ) root->pre->child[Choosech(p)] = root;
    p->pre = root, root->child[!pos] = p;
    Maintain(p), Maintain(root);
    if( root->pre == NULL ) p_root = root;
  }

  inline void Spaly(Node *root) {
    Node *p = root->pre;
    while( (p = root->pre) != NULL ) {
      if( p->pre != NULL ) Rotate(Choosech(root) == Choosech(p) ? p : root);
      Rotate(root);
    }
  }

  inline Node* Findnode(int key) {
    Node* root = p_root;
    while( root != NULL && root->val != key ) root=root->child[key > root->val];
    if( root != NULL ) Spaly(root);
    return root;
  }

  inline Node* Preposi(int key) {
    Node* root = Findnode(key);
    bool flag = false;
    if( root == NULL ) Insert(key), root = p_root, flag = true;
    if( root->lch == NULL ) { if( flag ) Delete(key); return NULL; }
    root = root->lch;
    while( root->rch ) root = root->rch;
    if( flag ) Delete(key);
    return root;
  }

  inline void Insert(int key){
    if( !p_root ) {
      p_root = &node[++node_num], p_root->val = key;
      return ;
    }
    Node *root = p_root, *p;
    while( true ) {
      if( root == NULL ) {
        root = &node[++node_num], root->pre = p, root->val = key;
        p->child[key > p->val] = root;
        return Spaly(root);
      }
      if( root->val == key ) { ++root->cnt, Spaly(root); return ; }
      p = root, root = root->child[key > root->val];
    }
  }

  inline void Delete(int key) {
    Node* root = Findnode(key);
    if( root == NULL ) return ;
    if( root->cnt > 1 ) { --root->cnt, --root->siz; return ; }
    if( root->lch == NULL && root->rch == NULL ) { p_root = NULL; return ; }
    if( root->lch == NULL ) { p_root = root->rch, root->rch->pre = NULL; return ; }
    if( root->rch == NULL ) { p_root = root->lch, root->lch->pre = NULL; return ; }
    Node *tmp_pre = Preposi(root->val), *tmp = p_root;
    Spaly(tmp_pre), p_root->rch = tmp->rch, tmp->rch->pre = p_root;
    Maintain(p_root);
  }

  inline int Querry_kth(int key){
    int tmp = 0;
    Node *root = p_root;
    while( true ) {
      if( root->lch && key <= root->lch->siz ) { root = root->lch; continue; }
      tmp = (root->lch ? root->lch->siz : 0) + root->cnt;
      if( key <= tmp ) return root->val;
      key -= tmp, root = root->rch;
    }
  }

  inline int Querry_rnk(int key) {
    Node *root = Findnode(key);
    bool flag = false;
    if( root == NULL ) Insert(key), flag = true;
    int ans = p_root->siz;
    if( p_root->rch ) ans = ans - p_root->rch->siz;
    ans = ans - p_root->cnt + 1;
    if( flag ) Delete(key);
    return ans;
  }

  inline int Querry_pre(int key){
    Node *root = Findnode(key);
    bool flag = false;
    if( root == NULL ) Insert(key), root = p_root, flag = true;
    if( root->lch == NULL ) { if( flag ) Delete(key); return -1; }
    root = root->lch;
    while( root->rch ) root = root->rch;
    if( flag ) Delete(key);
    return root->val;
  }

  inline int Querry_nxt(int key) {
    Node *root = Findnode(key);
    bool flag = false;
    if( root == NULL ) Insert(key), root = p_root, flag = true;
    if( root->rch == NULL ) { if( flag ) Delete(key); return -1; }
    root = root->rch;
    while( root->lch ) root = root->lch;
    if( flag ) Delete(key);
    return root->val;
  }
} splay;

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

int main(int argc, const char *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    int ques = read(), x = read();
    switch( ques ) {
      case 1: splay.Insert(x); break;
      case 2: splay.Delete(x); break;
      case 3: printf("%d\n", splay.Querry_rnk(x)); break;
      case 4: printf("%d\n", splay.Querry_kth(x)); break;
      case 5: printf("%d\n", splay.Querry_pre(x)); break;
      case 6: printf("%d\n", splay.Querry_nxt(x)); break;
    }
  }

  fclose(stdin), fclose(stdout);
  return 0;
}