#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;


const int maxn = 100000 + 10;
const int uinf = 100000000 + 7;
int n, opt, ans, node_num;

inline int rand() {
  static int seed = 712;
  seed = int((seed ^ 998244353 + 19260817ll) * 19890604ll % uinf);
  return seed;
}

struct Node {
  int key, weigh, size, times;
  Node *left, *right;

  Node() {
    left = NULL, right = NULL;
    size = 1, times = 1, key = 0, weigh = rand();
  }
  ~Node() {};
} node[maxn], *root;

class Treap {
public:
  inline void Maintain(Node* &p) {
    if( p == NULL ) return ;
    p->size = p->times;
    if( p->left != NULL ) p->size += p->left->size;
    if( p->right != NULL ) p->size += p->right->size;
  }

  inline void Left_Turn(Node* &p) {
    Node *t = p->right, p->right = t->left, t->left = p;
    Maintain(p), Maintain(t), p = t;
  }

  inline void Right_Turn(Node* &p) {
    Node *t = p->left, p->left = t->right, t->right = p;
    Maintain(p), Maintain(t), p = t;
  }

  inline void Insert_Node(Node* &p, int x) {
    if( p == NULL ) { p = &node[++node_num], p->key = x; return ; }
    if( p->key > x ) {
      Insert_Node(p->left, x);
      p->left->weigh > p->weigh ? Right_Turn(p) : Maintain(p);
      return ;
    }
    if( p->key < x ) {
      Insert_Node(p->right, x);
      p->right->weigh > p->weigh ? Left_Turn(p) : Maintain(p);
      return ;
    }
    ++p->times, Maintain(p); return ;
  }

  inline void Delete_Node(Node* &p, int x) {
    if( p == NULL ) return ;
    if( p->key > x ) { Delete_Node(p->left, x), Maintain(p); return ; }
    if( p->key < x ) { Delete_Node(p->right, x), Maintain(p); return ; }
    if( p->times > 1 ) p->times--, Maintain(p);
    else {
      if( p->left == NULL && p->right == NULL ) p = NULL;
      else if( p->left == NULL ) p = p->right;
      else if( p->right == NULL ) p = p->left;
      else {
        if( p->left->weigh > p->right->weigh )
          Right_Turn(p), Delete_Node(p->right, x);
        else Left_Turn(p), Delete_Node(p->left, x);
      }
      if( p != NULL ) Maintain(p);
    }
    return ;
  }

  inline int Querry_Rnk(Node *p, int x) {
    if( p == NULL ) return 0;
    int tmp = 0;
    if( p->left != NULL ) tmp = p->left->size;
    if( p->key == x ) return tmp + 1;
    if( p->key > x ) return Querry_Rnk(p->left, x);
    return tmp + p->times + Querry_Rnk(p->right, x);
  }

  inline int Querry_Num(Node *p, int x) {
    if( x <= 0 || x > p->size || p == NULL ) return 0;
    int tmp = 0;
    if( p->left != NULL ) tmp = p->left->size;
    if( tmp >= x ) return Querry_Num(p->left, x);
    if( tmp + p->times >= x ) return p->key;
    return Querry_Num(p->right, x - p->times - tmp);
  }

  inline void Querry_Pre(Node *p, int x, int &ans) {
    if( p == NULL ) return ;
    if( p->key >= x ) Querry_Pre(p->left, x, ans);
    else {
      if( p->key > ans ) ans = p->key;
      if( p->right != NULL ) Querry_Pre(p->right, x, ans);
    }
  }

  inline void Querry_Sub(Node *p, int x, int &ans) {
    if( p == NULL ) return ;
    if( p->key <= x ) Querry_Sub(p->right, x, ans);
    else {
      if( p->key < ans ) ans = p->key;
      if( p->left != NULL ) Querry_Sub(p->left, x, ans);
    }
  }
} treap;

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'),ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

int main(int argc, char const *argv[])
{
  scanf("%d", &n), root = &node[0];
  for(int i = 1; i <= n; ++i) {
    int opt = read(), x = read();
    switch( opt ) {
      case 1: treap.Insert_Node(root, x); break;
      case 2: treap.Delete_Node(root, x); break;
      case 3: ans = treap.Querry_Rnk(root, x), printf("%d\n", ans); break;
      case 4: ans = treap.Querry_Num(root, x), printf("%d\n", ans); break;
      case 5: ans = -uinf, treap.Querry_Pre(root, x, ans), printf("%d\n", ans); break;
      case 6: ans = uinf, treap.Querry_Sub(root, x, ans), printf("%d\n", ans); break;
      default : printf("It seems so difficult for me qwq.\n");
    }
  }
  return 0;
}