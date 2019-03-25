#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
const int mod = 1000000000 + 7;
int n, m, t, vis[maxn], pri[maxn], phi[maxn], top; long long ans;

inline void Get_phi(int x) {
  vis[1] = phi[1] = 1;
  for(int i = 2; i <= x; ++i) {
    if( !vis[i] ) pri[++top] = i, phi[i] = i - 1;
    for(int j = 1; (j <= top && i * pri[j] <= x); ++j) {
      vis[i * pri[j]] = 1, phi[i * pri[j]] = phi[i] * (pri[j] - 1);
      if( i % pri[j] == 0 ) { phi[i * pri[j]] = phi[i] * pri[j]; break; }
    }
  }
}

inline int Phi(int x) {
  int res = 1;
  for(int i = 2; i * i <= x; ++i) if( x % i == 0 ) {
    res = res * (i - 1), x = x / i;
    while( x % i == 0 ) res = res * i, x = x / i;
  }
  if( x > 1 ) res = res * (x - 1);
  return res;
}

inline int Fast_pow(int x, int p) {
  int res = 1;
  for( ; p; x = 1ll * x * x % mod, p = p >> 1) if( p & 1 ) res = 1ll * x * res % mod;
  return res;
}

int main(int argc, char const *argv[])
{
  scanf("%d", &t), Get_phi(maxn - 10);
  while( t-- ) {
    scanf("%d", &n), m = sqrt(n + 0.5), ans = 0ll;
    for(int i = 1; i <= m; ++i) if( n % i == 0 ) {
      ans = (ans + 1ll * (i > 1e6 ? Phi(i) : phi[i]) * Fast_pow(n, n / i)) % mod;
      ans = (ans + 1ll * (n / i > 1e6 ? Phi(n / i) : phi[n / i]) * Fast_pow(n, i)) % mod;
    }
    if( m * m == n ) ans = (mod + ans - 1ll * phi[m] * Fast_pow(n, m) % mod) % mod;
    printf("%lld\n", ans * Fast_pow(n, mod - 2) % mod);
  }

  return 0;
}