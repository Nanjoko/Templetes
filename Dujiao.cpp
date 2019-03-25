#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;

typedef long long u64;
tr1::unordered_map<int, int> fmu;
tr1::unordered_map<u64, u64> fphi;

const int maxn = 6000000 + 10;
int n, mu[maxn], vis[maxn], pri[maxn], top; u64 phi[maxn];

inline void Get_fun(int x) {
  mu[1] = phi[1] = 1;
  for(int i = 2; i <= x; ++i) {
    if( !vis[i] ) pri[++top] = i, mu[i] = -1, phi[i] = i - 1;
    for(int j = 1; (i * pri[j] <= x && j <= top); ++j) {
      vis[i * pri[j]] = 1;
      if( i % pri[j] == 0 ) { phi[i * pri[j]] = phi[i] * pri[j]; break; }
      else mu[i * pri[j]] = -mu[i], phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
  }
  for(int i = 1; i <= x; ++i) mu[i] = mu[i - 1] + mu[i], phi[i] = phi[i - 1] + phi[i];
}

inline int Get_mus(int x) {
  if( x <= maxn - 5 ) return mu[x];
  if( fmu[x] ) return fmu[x];
  int ans = 1;
  for(int l = 2, r; l <= x; l = r + 1)
    r = x / (x / l), ans = ans - (r - l + 1) * Get_mus(x / l);
  return fmu[x] = ans;
}

inline u64 Get_phis(u64 x) {
  if( x <= maxn - 5 ) return phi[x];
  if( fphi[x] ) return fphi[x];
  u64 ans = (x * (x + 1)) >> 1;
  for(u64 l = 2, r; l <= x; l = r + 1)
    r = x / (x / l), ans = ans - (r - l + 1) * Get_phis(x / l);
  return fphi[x] = ans;
}

int main(int argc, const char *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d", &n), Get_fun(maxn - 5);
  while( ~scanf("%d", &n) ) printf("%lld %d\n", Get_phis(n), Get_mus(n));

  fclose(stdin), fclose(stdout);
  return 0;
}