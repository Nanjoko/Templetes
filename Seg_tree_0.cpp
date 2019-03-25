#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define lch (x << 1)
#define rch (x << 1) | 1

const int maxn = 100000 + 10;

class Seg_tree{
  private:
    int tag[maxn << 2], sum[maxn << 2];
  public:
    Seg_tree() {
      
    }
    ~Seg_tree() {}
    
    inline void Maintain(int x) {
      sum[x] = sum[lch] + sum[rch];
    }
    
    inline void Pushdown(int x) {
      tag[lch] += tag[x], tag[rch] += tag[x];
    }
    
    void Build(int x, int l, int r) {
      
    }
    
    void Update(int x, int l, int r, int ques, int add_num) {
      
    }
    
    void Update(int x, int l, int r, int quesl, int quesr, int add_num) {
      
    }
    
    void Change(int x, int l, int r, int quesl, int quesr, int num) {
      
    }
    
    int Querry(int x, int l, int r, int quesl, int quesr, int fac_add) {
      
    }
}tree;

int a[maxn];

int main() {
  freopen("inputdata.in", "r", stdin);
  freopen("outputdata.out", "w", stdout);
  
  int n = read();
  for(int i = 1; i <= n; ++i) a[i] = read();
  
  
  fclose(stdin), fclose(stdout);
  return 0;
}
