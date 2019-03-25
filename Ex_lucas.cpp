#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long u64;

const int maxn = 1000000 + 10;
long long n, m, p, mul[maxn];

inline int Fast_pow(int a, u64 b, int mod) {
  int ans = 1;
  for( ; b; a = 1ll * a * a % mod, b = b >> 1) if( b & 1 ) ans = 1ll * a * ans % mod;
  return ans;
}

inline int Ex_gcd(int a, int b, int &x, int &y) {
  if( !b ) { x = 1, y = 0; return a; }
  int d = Ex_gcd(b, a % b, y, x); y = y - (a / b) * x;
  return d;
}

inline int Inverse(int a, int mod) {
  if( !a ) return 0;
  int x = 0, y = 0, d = Ex_gcd(a, mod, x, y);
  return (x = x % p + p) > p ? x - p : x;
}

inline int Multi(u64 n, int pri, int num) { // 求 n! mod pi^ki
  if( n <= 1 ) return 1;
  int ans = 1;
  if( n >= num ) ans = mul[num - 1], ans = Fast_pow(ans, n / num, num); // 算一组后快速幂
  if( n % num ) ans = ans * mul[n % num] % num; // 计算冗余
  return 1ll * ans * Multi(n / pri, pri, num) % num;  // 递归求提出来的阶乘形式的一部分
}

inline int C(u64 n, u64 m, int pri, int num) {
  mul[0] = mul[1] = 1;
  for(int i = 2; i < num; ++i) mul[i] = mul[i - 1] * (i % pri ? i : 1ll) % num; // 前缀积并剔除了 pri
  int a = Multi(n, pri, num), b = Multi(m, pri, num), c = Multi(n - m, pri, num);
  int inv_1 = Inverse(b, num), inv_2 = Inverse(c, num);
  int ans = 1ll * a * inv_1 % num * inv_2 % num; // 组合数 C(n,m)
  u64 k = 0ll;
  for(u64 i = n / pri; i; i = i / pri) k = k + i;
  for(u64 i = m / pri; i; i = i / pri) k = k - i;
  for(u64 i = (n - m) / pri; i; i = i / pri) k = k - i; // 计数以加入被剔除的 pri 的贡献
  return 1ll * ans * Fast_pow(pri, k, num) % num;
}

inline long long Ex_lucas(u64 n, u64 m, u64 p) {
  u64 P = p, ans = 0ll;
  for(int i = 2, num = 1; i <= p; ++i) if( p % i == 0 && (num = 1) ) {
    while( p % i == 0 ) p = p / i, num = num * i;
    ans = (ans + 1ll * C(n, m, i, num) * (P / num) % P * Inverse(P / num, num)) % P; // CRT 合并
  }
  return ans;
}

int main(int argc, char const *argv[])
{
  scanf("%lld%lld%lld", &n, &m, &p);
  printf("%lld\n", Ex_lucas(n, m, p));

  return 0;
}