#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, a[maxn]; long long s[maxn];

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

inline void Addnum(int l, int r, int c) { bit.Update(l, c), bit.Update(r + 1, -c); }

int main(int argc, char const *argv[])
{
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) a[i] = read(), bit.Update(i, a[i] - a[i - 1]);
  for(int l, r, x, i = 1; i <= m; ++i)
    if( read() == 1 ) l = read(), r = read(), x = read(), Addnum(l, r, x);
    else printf("%lld\n", bit.Querry(read()));

  return 0;
}