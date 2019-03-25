#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 60 + 5;
long long n, a[maxn], p[maxn], ans;

int main(int argc, char const *argv[])
{
  scanf("%lld", &n);
  for(int i = 1; i <= n; ++i) scanf("%lld", a + i);
  for(int i = 1; i <= n; ++i) for(int j = 60; j >= 0; --j) {
    if( (a[i] >> j) == 0 ) continue;
    if( p[j] == 0 ) { p[j] = a[i]; break; }
    a[i] = a[i] ^ p[j];
  }
  for(int i = 60; i >= 0; --i) if( ans < (ans ^ p[i]) ) ans = ans ^ p[i];
  printf("%lld\n", ans);

  return 0;
}