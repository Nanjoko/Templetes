#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, a[maxn]; long long s[maxn], sum[maxn];

class Bianry_tree {
public:
  inline void Update(int x, int c) {
    for(int i = x; i <= n; i = i + (i & -i))
      s[i] = s[i] + c, sum[i] = sum[i] + 1ll * x * c;
  }

  inline long long Querry(int x) {
    long long ans = 0ll, i = x;
    while( i ) ans = ans + (x + 1) * s[i] - sum[i], i = i - (i & -i);
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
inline void Getsum(int l, int r) { printf("%lld\n", bit.Querry(r) - bit.Querry(l - 1)); }

int main(int argc, char const *argv[])
{
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) a[i] = read(), bit.Update(i, a[i] - a[i - 1]);
  for(int l, r, x, i = 1; i <= m; ++i)
    if( read() == 1 ) l = read(), r = read(), x = read(), Addnum(l, r, x);
    else l = read(), r = read(), Getsum(l, r);

  return 0;
}