#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read(int mod, int &f) {
  register int ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) {
    x = (x * 10) + (ch ^ 48), ch = getchar();
    if( x >= mod ) x = x % mod, f = 1;
  }
  return w ? -x : x;
}

inline int Fast_pow(int x, int p, int mod) {
  int res = 1;
  for( ; p; x = 1ll * x * x % mod, p = p >> 1) if( p & 1 ) res = 1ll * x * res % mod;
  return res;
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

int main(int argc, char const *argv[])
{
  int a = 0, b = 0, m = 0, flag = 0;
  scanf("%d%d", &a, &m), b = read(Phi(m), flag);
  printf("%d\n", Fast_pow(a, b + flag * Phi(m), m));

  return 0;
}