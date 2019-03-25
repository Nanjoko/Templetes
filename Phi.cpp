#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long u64;
const int maxn = 10000000 + 10;
int n, prime[maxn], not_pri[maxn], phi[maxn];

/* 单个欧拉函数 */
inline u64 Sig_Phi(u64 x) {
  u64 phi = x;
  for(u64 i = 2; i * i <= x; ++i) {
    if( !(x % i) ) {
      phi = phi - phi / i;
      while( !(x % i) ) x /= i;
    }
  }
  if( x > 1 ) phi = phi - phi / x;
  return phi;
}

/* 线性求欧拉函数 */
inline void Che_Phi(u64 x) {
  phi[1] = 1;
  for(int i = 2; i < x; ++i) phi[i] = i;
  for(int i = 2; i < x; ++i) {
    if( phi[i] == i ) for(int j = i; j < x; j += i)
      phi[j] = phi[j] / i * (i - 1);
  }
}

/* 线性求欧拉函数 */
inline void Get_Phi(u64 x) {
  int p = -1, k;
  phi[1] = 1, not_pri[0] = not_pri[1] = 1;
  for(int i = 2; i <= x; ++i) {
    if( !not_pri[i] ) {
      prime[++p] = not_pri[i] = i;
      phi[i] = i - 1;
    }
    for(int j = 0; j <= p; ++j) {
      if( (k = prime[j] * i) > x ) break;
      not_pri[k] = prime[j];
      if( not_pri[i] == prime[j] ) {
        phi[k] = phi[i] * prime[j]; break;
      } else phi[k] = phi[i] * (prime[j] - 1);
    }
  }
}

int main(int argc, char* const argv[])
{
  Get_Phi(10000000);
  for(int i = 1; i <= 20; ++i) printf("%d\n", phi[i]);
  // while( ~scanf("%lld", &n) ) printf("%lld\n", Phi(n));

  printf("_______________________________________________\n");
  printf("Process Exited Correctly With A Return Value 0.\n");
  printf("All Rights Reserved By Kimitsu Nanjo In 2018.\n\n");
  return 0;
}