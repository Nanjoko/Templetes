#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, a[maxn], ans;

inline int Gcd(int a, int b) { return !b ? a : Gcd(b, a % b); }

int main(int argc, char const *argv[])
{
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] = (a[i] > 0 ? a[i] : -a[i]);
  for(int i = 2; i <= n; ++i) a[1] = Gcd(a[1], a[i]);
  printf("%d\n", a[1] > 0 ? a[1] : -a[1]);

  return 0;
}