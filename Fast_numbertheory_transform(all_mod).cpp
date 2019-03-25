#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long u64;

const int maxn = 5000000 + 10;
const u64 prime[] = { 469762049ll, 998244353ll, 1004535809ll };
u64 n, m, k, len, ans[3][maxn];
u64 limit, rado, f_1[maxn], f_2[maxn], f_3[maxn], f_4[maxn], r[maxn];

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline u64 Slow_mul(u64 a, u64 p, u64 mod) {
  u64 x = a % mod, ans = 0ll;
  for( ; p; x = (x + x) % mod, p = p >> 1) if( p & 1 ) ans = (x + ans) % mod;
  return ans;
}

inline u64 Fast_pow(u64 a, u64 p, u64 mod) {
  u64 x = a % mod, ans = 1ll;
  for( ; p; x = x * x % mod, p = p >> 1) if( p & 1 ) ans = x * ans % mod;
  return ans;
}

inline void Fast_numbertheory_transform(u64 *a, u64 type, u64 mod) {
  for(int i = 0; i < limit; ++i) if( i < r[i] ) swap(a[i], a[r[i]]);
  for(int mid = 1; mid < limit; mid = mid << 1) {
    u64 Base_p = Fast_pow(3, (mod - 1) / (mid << 1), mod);
    if( type == -1 ) Base_p = Fast_pow(Base_p, mod - 2, mod);
    for(int l = 0, length = mid << 1; l < limit; l = l + length) {
      for(int k = 0, p = 1; k < mid; ++k, p = p * Base_p % mod) {
        u64 tmp_1 = a[l + k], tmp_2 = p * a[l + mid + k] % mod;
        a[l + k] = (tmp_1 + tmp_2 + mod) % mod, a[l + mid + k] = (tmp_1 - tmp_2 + mod) % mod;
      }
    }
  }
}

inline void Chinese_remainder_theorem(u64 mod) {
  u64 inv_1 = Fast_pow(prime[1], prime[0] - 2, prime[0]);
  u64 inv_2 = Fast_pow(prime[0], prime[1] - 2, prime[1]);
  u64 inv = Fast_pow(prime[0] * prime[1], prime[2] - 2, prime[2]);
  for(u64 i = 0, con = 0, tmp = 0; i <= len; ++i, con = 0) {
    con = (con + Slow_mul(ans[0][i] * prime[1], inv_1, prime[0] * prime[1])) % (prime[0] * prime[1]);
    con = (con + Slow_mul(ans[1][i] * prime[0], inv_2, prime[0] * prime[1])) % (prime[0] * prime[1]);
    tmp = ((ans[2][i] - con) % prime[2] + prime[2]) * inv % prime[2];
    printf("%lld ", (tmp * (prime[0] * prime[1] % mod) + con) % mod);
  }
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d%d%d", &n, &m, &k);
  for(int i = 0; i <= n; ++i) f_1[i] = read();
  for(int i = 0; i <= m; ++i) f_2[i] = read();
  len = n + m, limit = 1, rado = 0;
  while( limit <= len ) limit = limit << 1, ++rado;
  for(int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (rado - 1));
  for(u64 p = 0; p < 3; ++p) {
    memcpy(f_3, f_1, sizeof f_3), memcpy(f_4, f_2, sizeof f_4);
    Fast_numbertheory_transform(f_3, 1, prime[p]);
    Fast_numbertheory_transform(f_4, 1, prime[p]);
    for(int i = 0; i < limit; ++i) f_3[i] = f_3[i] * f_4[i] % prime[p];
    Fast_numbertheory_transform(f_3, -1, prime[p]);
    u64 inv = Fast_pow(limit, prime[p] - 2, prime[p]);
    for(int i = 0; i < limit; ++i) ans[p][i] = f_3[i] * inv % prime[p];
  }
  Chinese_remainder_theorem(k);

  fclose(stdin), fclose(stdout);
  return 0;
}