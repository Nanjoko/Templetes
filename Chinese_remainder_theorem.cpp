#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int u64;

u64 Ex_gcd(u64 a, u64 b, u64 &x, u64 &y) {
  if( !b ) { x = 1, y = 0; return a; }
  u64 d = Ex_gcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

u64 CRT(u64 *a, u64 *b, u64 k) {
  u64 x = 0, y = 0, mul = 1, ans = 0;
  for(int i = 1; i <= k; ++i) mul *= a[i];
  for(int i = 1; i <= k; ++i) {
    u64 m = mul / a[i];
    Ex_gcd(m, a[i], x, y);
    ans = (ans + m * y * b[i]) % mul;
  }
  return ans > 0 ? ans : ans + mul;
}

int main(int argc, char* const argv[])
{
  u64 n = 0, a[12] = {0}, b[12] = {0};
  scanf("%lld", &n);
  for(int i = 1; i <= n; ++i)
    scanf("%lld%lld", &a[i], &b[i]);
  printf("%lld\n", CRT(a, b, n));

  printf("_______________________________________________\n");
  printf("Process Exited Correctly With A Return Value 0.\n");
  printf("All Rights Reserved By Kimitsu Nanjo In 2018.\n\n");
  return 0;
}