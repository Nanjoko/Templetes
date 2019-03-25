#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int mod = 998244353;
const int maxn = 5000000 + 10;
int n, m, len, limit, rado, f_1[maxn], f_2[maxn], r[maxn];

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline int Fast_pow(int a, int p) {
  long long x = a, ans = 1ll;
  for( ; p; x = x * x % mod, p = p >> 1) if( p & 1 ) ans = x * ans % mod;
  return (int)ans;
}

inline void Fast_numbertheory_transform(int *a, int limit, int type) {
  int rado = bit[limit];
  for(int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (rado - 1));
  for(int i = 0; i < limit; ++i) if( i < r[i] ) swap(a[i], a[r[i]]);
  for(int mid = 1; mid < limit; mid = mid << 1) {
    int Base_p = Fast_pow(3ll, (mod - 1) / (mid << 1));
    if( type == -1 ) Base_p = Fast_pow(Base_p, mod - 2);
    for(int l = 0, length = mid << 1; l < limit; l = l + length) {
      for(int k = 0, p = 1; k < mid; ++k, p = 1ll * p * Base_p % mod) {
        int x = a[l + k], y = 1ll * p * a[l + mid + k] % mod;
        a[l + k] = (x + y) % mod, a[l + mid + k] = (x - y + mod) % mod;
      }
    }
  }
  if( type == -1 ) for(int i = 0; i < limit; ++i) a[i] = 1ll * a[i] * Fast_pow(limit, mod - 2) % mod;
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 0; i <= n; ++i) f_1[i] = read();
  for(int i = 0; i <= m; ++i) f_2[i] = read();
  len = n + m, limit = 1, rado = 0;
  while( limit <= len ) limit = limit << 1, ++rado;
  for(int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (rado - 1));
  Fast_numbertheory_transform(f_1, 1);
  Fast_numbertheory_transform(f_2, 1);
  for(int i = 0; i < limit; ++i) f_1[i] = 1ll * f_1[i] * f_2[i] % mod;
  Fast_numbertheory_transform(f_1, -1);
  for(int i = 0; i <= len; ++i) printf("%d ", f_1[i]);

  fclose(stdin), fclose(stdout);
  return 0;
}