#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int mod = 998244353;
const int maxn = (1 << 17) + 10;
int n, m, limit, f_1[maxn], f_2[maxn], f_3[maxn], f_4[maxn], r[maxn];

class Walsh_transform_and {
public:
  inline void Fast_walsh_transform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1)
      for(int l = 0, length = mid << 1; l < limit; l = l + length)
        for(int k = 0; k < mid; ++k) a[l + k] = (a[l + k] + a[l + mid + k]) % mod;
  }

  inline void Fast_walsh_inverform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1)
      for(int l = 0, length = mid << 1; l < limit; l = l + length)
        for(int k = 0; k < mid; ++k) a[l + k] = (a[l + k] - a[l + mid + k] + mod) % mod;
  }
} calculate_and;

class Walsh_transform_or {
public:
  inline void Fast_walsh_transform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1)
      for(int l = 0, length = mid << 1; l < limit; l = l + length)
        for(int k = 0; k < mid; ++k) a[l + mid + k] = (a[l + mid + k] + a[l + k]) % mod;
  }

  inline void Fast_walsh_inverform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1)
      for(int l = 0, length = mid << 1; l < limit; l = l + length)
        for(int k = 0; k < mid; ++k) a[l + mid + k] = (a[l + mid + k] - a[l + k] + mod) % mod;
  }
} calculate_or;

class Walsh_transform_xor {
public:
  inline void Fast_walsh_transform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1) {
      for(int l = 0, length = mid << 1; l < limit; l = l + length) {
        for(int k = 0; k < mid; ++k) {
          int x = a[l + k], y = a[l + mid + k];
          a[l + k] = (x + y) % mod, a[l + mid + k] = (x - y + mod) % mod;
        }
      }
    }
  }

  inline void Fast_walsh_inverform(int *a) {
    for(int mid = 1; mid < limit; mid = mid << 1) {
      for(int l = 0, length = mid << 1; l < limit; l = l + length) {
        for(int k = 0; k < mid; ++k) {
          int x = a[l + k], y = a[l + mid + k];
          a[l + k] = (x + y) % mod, a[l + mid + k] = (x - y + mod) % mod;
          a[l + k] = (a[l + k] & 1) ? (a[l + k] + mod) >> 1 : a[l + k] >> 1;
          a[l + mid + k] = (a[l + mid + k] & 1) ? (a[l + mid + k] + mod) >> 1 : a[l + mid + k] >> 1;
        }
      }
    }
  }
} calculate_xor;

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  n = read(), limit = (1 << n);
  for(int i = 0; i < limit; ++i) f_1[i] = read();
  for(int i = 0; i < limit; ++i) f_2[i] = read();

  for(int i = 0; i < limit; ++i) f_3[i] = f_1[i];
  for(int i = 0; i < limit; ++i) f_4[i] = f_2[i];
  calculate_or.Fast_walsh_transform(f_3);
  calculate_or.Fast_walsh_transform(f_4);
  for(int i = 0; i < limit; ++i) r[i] = (1ll * f_3[i] * f_4[i]) % mod;
  calculate_or.Fast_walsh_inverform(r);
  for(int i = 0; i < limit; ++i) printf("%d ", r[i]);
  printf("\n");

  for(int i = 0; i < limit; ++i) f_3[i] = f_1[i];
  for(int i = 0; i < limit; ++i) f_4[i] = f_2[i];
  calculate_and.Fast_walsh_transform(f_3);
  calculate_and.Fast_walsh_transform(f_4);
  for(int i = 0; i < limit; ++i) r[i] = (1ll * f_3[i] * f_4[i]) % mod;
  calculate_and.Fast_walsh_inverform(r);
  for(int i = 0; i < limit; ++i) printf("%d ", r[i]);
  printf("\n");

  for(int i = 0; i < limit; ++i) f_3[i] = f_1[i];
  for(int i = 0; i < limit; ++i) f_4[i] = f_2[i];
  calculate_xor.Fast_walsh_transform(f_3);
  calculate_xor.Fast_walsh_transform(f_4);
  for(int i = 0; i < limit; ++i) r[i] = (1ll * f_3[i] * f_4[i]) % mod;
  calculate_xor.Fast_walsh_inverform(r);
  for(int i = 0; i < limit; ++i) printf("%d ", r[i]);
  printf("\n");

  fclose(stdin), fclose(stdout);
  return 0;
}