#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long u64;

const int maxn = 100000 + 10;
u64 n, m, p, inv[maxn];

inline u64 Fast_Pow(u64 x, u64 k) {
    u64 ans = 1;
    while(k) {
        if( k&1 ) ans = ans * x % p;
        k >>= 1, x = x * x % p;
    }
    return ans;
}

u64 C(u64 k, u64 b) {
    if( k<b )  return 0;
    return inv[k] * Fast_Pow(inv[b], p-2) * Fast_Pow(inv[k-b], p-2) % p;
}

u64 Lucas(u64 k, u64 b) {
    if( !b )  return 1;
    return C(k%p, b%p) * Lucas(k/p, b/p) % p;
}

int main(int argc, char const *argv[])
{
    int t;  scanf("%d", &t);
    while( t-- ) {
        inv[0] = 1;
        scanf("%lld%lld%lld", &n, &m, &p);
        for(int i=1; i<=p; ++i)
            inv[i] = inv[i-1] * i % p;
        printf("%lld\n", Lucas(n+m, n));
    }
    return 0;
}
