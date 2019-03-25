#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m; long long s[maxn];

class Bianry_tree {
public:
  inline void Update(int x, int c) {
    while( x <= n ) s[x] = s[x] + c, x = x + (x & -x);
  }

  inline long long Querry(int x) {
    long long ans = 0ll;
    while( x ) ans = ans + s[x], x = x - (x & -x);
    return ans;
  }
} bit;

inline int read() {
  register int ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline void Addnum(int x, int c) { bit.Update(x, c); }
inline void Getsum(int l, int r) { printf("%lld\n", bit.Querry(r) - bit.Querry(l - 1)); }

int main(int argc, char const *argv[])
{
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) Addnum(i, read());
  for(int ques, l, r, i = 1; i <= m; ++i)
    ques = read(), l = read(), r = read(), ques == 1 ? Addnum(l, r) : Getsum(l, r);

  return 0;
}