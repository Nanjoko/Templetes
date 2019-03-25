#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long u64;

const int mod = 998244353;
const int maxn = 600000 + 10;
int n, r[maxn], bit[maxn]; u64 f[maxn], inv[maxn], tmp[maxn];

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline u64 Fast_pow(u64 a, int p) {
  u64 x = a, ans = 1ll;
  for( ; p; x = x * x % mod, p = p >> 1) if( p & 1 ) ans = x * ans % mod;
  return ans;
}

inline void Number_theory_transform(u64 *a, int limit, int type) {
  int rado = bit[limit];
  for(int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (rado - 1));
  for(int i = 0; i < limit; ++i) if( i < r[i] ) swap(a[i], a[r[i]]);
  for(int mid = 1; mid < limit; mid = mid << 1) {
    u64 Base_p = Fast_pow(3ll, (mod - 1) / (mid << 1));
    if( type == -1 ) Base_p = Fast_pow(Base_p, mod - 2);
    for(int l = 0, length = mid << 1; l < limit; l = l + length) {
      for(int k = 0, p = 1; k < mid; ++k, p = p * Base_p % mod) {
        u64 x = a[l + k], y = p * a[l + mid + k] % mod;
        a[l + k] = (x + y) % mod, a[l + mid + k] = (x - y + mod) % mod;
      }
    }
  }
  if( type == -1 ) for(int i = 0; i < limit; ++i) a[i] = a[i] * Fast_pow(limit, mod - 2) % mod;
}

inline void Inverse_transform(u64 *a, u64 *b, int limit) {
  if( limit == 1 ) { b[0] = Fast_pow(a[0], mod - 2); return ; }
  Inverse_transform(a, b, (limit + 1) >> 1);
  int len = limit << 1;
  for(int i = 0; i < limit; ++i) tmp[i] = a[i];
  for(int i = limit; i < len; ++i) tmp[i] = 0;
  Number_theory_transform(tmp, len, 1);
  Number_theory_transform(b, len, 1);
  for(int i = 0; i < len; ++i) b[i] = (2 * b[i] % mod - (b[i] * b[i] % mod) * tmp[i] % mod + mod) % mod;
  Number_theory_transform(b, len, -1);
  for(int i = limit; i < len; ++i) b[i] = 0;
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d", &n);
  for(int i = 0; i < n; ++i) f[i] = read();
  int limit = 1, rado = 0;
  while( limit <= n ) limit = limit << 1, ++rado;
  for(int i = 0; i < 20; ++i) bit[1 << i] = i;
  Inverse_transform(f, inv, limit);
  for(int i = 0; i < n; ++i) printf("%lld ", inv[i]);

  fclose(stdin), fclose(stdout);
  return 0;
}