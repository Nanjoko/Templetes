#include <vector>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long u64;
u64 n, pri[13] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 }, ans;

vector<u64> v;

inline u64 Abs(u64 x) { return x > 0 ? x : -x; }
inline u64 Gcd(u64 a, u64 b) { return !b ? a : Gcd(b, a % b); }

inline u64 Fast_mul(u64 a, u64 b, u64 p) {
  u64 ans = 0;
  a = a % p, b = b % p;
  for( ; b; a = (a << 1) % p, b = b >> 1) if( b & 1 ) ans = (a + ans) % p;
  return ans;
}

inline u64 Fast_pow(u64 a, u64 b, u64 p) {
  u64 ans = 1;
  for( ; b; a = Fast_mul(a, a, p), b = b >> 1) if( b & 1 ) ans = Fast_mul(ans, a, p);
  return ans;
}

inline bool Judge(u64 x, u64 k, u64 rado, u64 p) {
  u64 tmp = Fast_pow(x, k, p);
  if( tmp == 1 ) return false;
  for(int i = 0; i <= rado; ++i, tmp = Fast_mul(tmp, tmp, p))
    if( tmp == 1 || tmp == x - 1 ) return false;
  return true;
}

inline bool Miller_robin(u64 x) {
  if( x == 1 ) return true;
  for(int i = 0; i < 13; ++i) if( x % pri[i] == 0 ) return x == pri[i];
  u64 tmp = x - 1, rado = 0;
  while( (tmp & 1) == 0 ) tmp = tmp >> 1, ++rado;
  for(int i = 0; i < 13; ++i) if( Judge(pri[i], tmp, rado, x) ) return false;
  return true;
}

inline void Pollard_rho(u64 x) {
  if( Miller_robin(x) ) { v.push_back(x); return ; }
  u64 a = 0, b = 0, c = 0, tmp = 0;
  while( true ) {
    c = rand() % x, a = b = rand() % x, b = (Fast_mul(b, b, x) + c) % x;
    while( a != b ) {
      tmp = a - b, tmp = Gcd(Abs(a - b), x);
      if( tmp > 1 && tmp < x ) { Pollard_rho(tmp), Pollard_rho(x / tmp); return ; }
      a = (Fast_mul(a, a, x) + c) % x;
      b = (Fast_mul(b, b, x) + c) % x, b = (Fast_mul(b, b, x) + c) % x;
    }
  }
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  srand(20001106), v.push_back(1ll);
  scanf("%lld", &n), Pollard_rho(n), sort(v.begin(), v.end()), ans = 1;
  for(int i = 1; i < v.size(); ++i) ans = ans * (v[i] - (v[i] != v[i - 1]));
  printf("%lld\n", ans);

  fclose(stdin), fclose(stdout);
  return 0;
}