// Warning: There Is An Error In This Code.
// When There Are Two Strings That One Is Included By The Other.
// It Will Give A Wrong Answer.
// By. Kimitsu Nanjo In 06.28.2018.
// https://www.luogu.org/problemnew/show/P3796

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int maxn = 1000000 + 10;
char a[maxn], word[maxn];

struct Node{
  int cnt;
  Node *fail, *next[26];
}*queue[maxn], *root;

inline void Refl(Node *root) {
  root->cnt = 0;
  root->fail = NULL;
  for(int i = 0; i < 26; ++i)
    root->next[i] = NULL;
}

inline void Insert(char *s, int len) {
  Node *p = root;
  for(int i = 0; i < len; ++i) {
    if( p->next[s[i] - 'a'] == NULL ) {
      Node *q = (Node*)malloc(sizeof(Node)); Refl(q);
      p->next[s[i] - 'a'] = q;
    }
    p = p->next[s[i] - 'a'];
  }
  p->cnt++;
}

inline void Build_fail(Node *root) {
  int head = 0, tail = 0;   //队列头、尾指针 
  queue[head++] = root;   //先将root入队 
  while( head != tail )
  {
    Node *p = NULL, *temp = queue[tail++];    //弹出队头结点 
    for(int i = 0; i < 26; ++i) {
      if( temp->next[i] != NULL ) {
            //找到实际存在的字符结点
            //temp->next[i] 为该结点，temp为其父结点 
        if( temp == root ) temp->next[i]->fail = root;
            //若是第一层中的字符结点，则把该结点的失败指针指向root 
        else {
              //依次回溯该节点的父节点的失败指针直到某节点的next[i]与该节点相同
              //则把该节点的失败指针指向该next[i]节点； 
              //若回溯到 root 都没有找到，则该节点的失败指针指向 root
          p = temp->fail;   //将该结点的父结点的失败指针给p 
          while( p != NULL ) {
            if( p->next[i] != NULL ) {
              temp->next[i]->fail = p->next[i];
              break;
            }
            p = p->fail;
          }
              //让该结点的失败指针也指向root 
          if( p == NULL ) temp->next[i]->fail = root;
        }
        queue[head++] = temp->next[i];
            //每处理一个结点，都让该结点的所有孩子依次入队 
      }
    }
  }
}

inline int Querry(Node *root, int len) {    //i为主串指针，p为模式串指针 
  int ans = 0;
  Node *p = root;
  for(int i = 0; i < len; ++i) {
        //由失败指针回溯查找，判断s[i]是否存在于Trie树中 
    while( p->next[a[i] - 'a'] == NULL && p != root ) p = p->fail;
    p = p->next[a[i] - 'a'];    //找到后p指针指向该结点 
    if( p == NULL ) p = root;   //若指针返回为空，则没有找到与之匹配的字符 
    Node *temp = p;   //匹配该结点后，沿其失败指针回溯，判断其它结点是否匹配 
    while( temp != root ) {   //匹配结束控制 
      if( temp->cnt >= 0 )   //判断该结点是否被访问 
        ans += temp->cnt, temp->cnt = -1;
          //由于cnt初始化为 0，所以只有cnt>0时才统计了单词的个数, 标记已访问过 
      temp = temp->fail;    //回溯 失败指针 继续寻找下一个满足条件的结点 
    }
  }
  return ans;
}

void Free_Node(Node *p) {
  for(int i = 0; i < 26; ++i)
    if( p->next[i] != NULL ) Free_Node(p->next[i]);
  free(p);
}

int main(int argc, char* const argv[])
{
  int n = 0;
  root = (struct Node*)malloc(sizeof(Node)), Refl(root);
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%s", word);
    Insert(word, strlen(word));
  }
  Build_fail(root);
  scanf("%s", a);
  printf("%d\n", Querry(root, strlen(a)));

  return 0;
}