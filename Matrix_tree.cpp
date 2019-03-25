#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define scnaf scanf
typedef long long u64;

const int maxn = 100 + 10;
const int mod = 1000000000;
char a[12][12];
u64 kir[maxn][maxn], ans;
int n, m, id[12][12], deg[maxn][maxn], edg[maxn][maxn], cnt;

inline void Gaussian() {
  for(int i = 1; i <= n; ++i)
    for(int j = i + 1; j <= n; ++j) while( kir[j][i] ) {
      int tmp = kir[i][i] / kir[j][i];
      for(int k = i; k <= n; ++k)
        kir[i][k] = (kir[i][k] - tmp * kir[j][k] % mod + mod) % mod, swap(kir[i][k], kir[j][k]);
      ans = (mod - ans) % mod;
    }
}

int main(int argc, char const *argv[])
{
  freopen("nanjolno.in", "r", stdin);
  freopen("nanjolno.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) scnaf("%s", a[i] + 1);
  for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) if( a[i][j] == '.' ) id[i][j] = ++cnt;
  for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) if( a[i][j] == '.' ) {
    if( a[i - 1][j] == '.' ) edg[id[i][j]][id[i - 1][j]] = 1, ++deg[id[i][j]][id[i][j]];
    if( a[i + 1][j] == '.' ) edg[id[i][j]][id[i + 1][j]] = 1, ++deg[id[i][j]][id[i][j]];
    if( a[i][j - 1] == '.' ) edg[id[i][j]][id[i][j - 1]] = 1, ++deg[id[i][j]][id[i][j]];
    if( a[i][j + 1] == '.' ) edg[id[i][j]][id[i][j + 1]] = 1, ++deg[id[i][j]][id[i][j]];
  }
  n = cnt - 1, ans = 1ll;
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) kir[i][j] = (deg[i][j] - edg[i][j] + mod) % mod;
  Gaussian();
  for(int i = 1; i <= n; ++i) ans = ans * kir[i][i] % mod;
  printf("%lld\n", (ans + mod) % mod);

  fclose(stdin), fclose(stdout);
  return 0;
}