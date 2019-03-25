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
int n, m, r[maxn], bit[maxn];
u64 tmp[maxn], tmp_1[maxn], tmp_2[maxn];
u64 f_1[maxn], f_2[maxn], inv[maxn], mul[maxn], ans[maxn];

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline u64 Fast_pow(u64 a, int p) {
  u64 x = a, res = 1ll;
  for( ; p; x = x * x % mod, p = p >> 1) if( p & 1 ) res = x * res % mod;
  return res;
}

inline int Limit(int len) { for(int i = 1; ; i = i << 1) if( i > len ) return i; }

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
  if( type == -1 ) for(int i = 0, inv_lim = Fast_pow(limit, mod - 2); i < limit; ++i) a[i] = a[i] * inv_lim % mod;
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

inline void Multiply_transform(u64 *a, u64 *b, u64 *c, int len_1, int len_2) {
  int len = Limit(len_1 + len_2);
  for(int i = 0; i <= len_1; ++i) tmp_1[i] = a[i];
  for(int i = 0; i <= len_2; ++i) tmp_2[i] = b[i];
  Number_theory_transform(tmp_1, len, 1);
  Number_theory_transform(tmp_2, len, 1);
  for(int i = 0; i < len; ++i) c[i] = tmp_1[i] * tmp_2[i] % mod, tmp_1[i] = tmp_2[i] = 0;
  Number_theory_transform(c, len, -1);
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  for(int i = 0; i < 20; ++i) bit[1 << i] = i;
  scanf("%d%d", &n, &m);
  for(int i = 0; i <= n; ++i) f_1[i] = read();
  for(int i = 0; i <= m; ++i) f_2[i] = read();
  reverse(f_1, f_1 + n + 1), reverse(f_2, f_2 + m + 1);
  Inverse_transform(f_2, inv, Limit(n - m));
  Multiply_transform(f_1, inv, ans, n - m, n - m);
  reverse(ans, ans + n - m + 1);
  for(int i = 0; i <= n - m; ++i) printf("%lld ", ans[i]); printf("\n");
  reverse(f_1, f_1 + n + 1), reverse(f_2, f_2 + m + 1);
  Multiply_transform(ans, f_2, mul, n - m, m);
  for(int i = 0; i < m; ++i) printf("%lld ", (f_1[i] - mul[i] + mod) % mod); printf("\n");

  fclose(stdin), fclose(stdout);
  return 0;
}