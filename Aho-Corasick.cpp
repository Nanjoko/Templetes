#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxm = 151 * 71;
const int maxn = 1000000 + 10;

int m;
char s[151][71], arti[maxn];

class Aho_Corasick_Automaton{
  private:
    int node_num, f[maxm], ch[maxm][26], cnt[maxm], val[maxm], last[maxm];
  public:
    inline void clear() {
      memset(f, 0, sizeof f);
      memset(ch, 0, sizeof ch);
      memset(cnt, 0, sizeof cnt);
      memset(val, 0, sizeof val);
      memset(last, 0, sizeof last);
      node_num = 0;
    }
    inline void insert(char *s,int index) {
      int u=0,len=strlen(s);
      for(int i = 0; i < len; ++i){
        if (!ch[u][s[i] - 'a'])ch[u][s[i] - 'a']=++node_num;
        u=ch[u][s[i] - 'a'];
      }
      val[u]=index;
    }
    inline void getFail() {
      queue<int> q;
      q.push(0);
      while ( !q.empty() ){
        int u = q.front(), k=f[u];  q.pop();
        for(int i = 0; i < 26; ++i) {
          int v=ch[u][i];
          if (!v){ch[u][i]=ch[k][i];continue;}
          f[v]=u?ch[k][i]:0;
          last[v]=val[f[v]]?f[v]:last[f[v]];
          q.push(v);
        }
      }
    }
    inline void Querry(char *arti) {
      int u = 0, len = strlen(arti), res = 0;
      for(int i = 0; i < len; ++i) {
        int c=arti[i]-'a';
        u=ch[u][c];
        if (val[u])cnt[val[u]]++;
        int v=last[u];
        while (v){
          if (val[v])cnt[val[v]]++;
          v=last[v];
        }
      }
      for(int i = 0; i <= m; ++i) res = max(res, cnt[i]);
      printf("%d\n", res);
      for(int i = 0; i <= m; ++i)
        if( cnt[i] == res ) printf("%s\n", s[i]);
    }
}AC;

int main(int argc, char* const argv[]) {
  while ( scanf("%d", &m) && m ) {
    AC.clear();
    for(int i = 0; i <= m; ++i) {
      scanf("%s", s[i]);
      AC.insert(s[i], i);
    }
    AC.getFail();
    scanf("%s", arti);
    AC.Querry(arti);
  }
  return 0;
}