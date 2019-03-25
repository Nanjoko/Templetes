#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long u64;

const u64 mod = 1e9 + 7;
int n; u64 k, m[110][110];

inline void Mati_Mul(u64 a[][110], u64 b[][110]) {
    u64 tmp[110][110] = {0};
    for(int i=1; i<=n; ++i)
    for(int j=1; j<=n; ++j)
    for(int k=1; k<=n; ++k)
        tmp[i][j] += a[i][k] * b[k][j], tmp[i][j] %= mod;
    for(int i=1; i<=n; ++i)
    for(int j=1; j<=n; ++j)
        a[i][j] = tmp[i][j];
}

inline void Fast_Pow(u64 a[][110], u64 p) {
    u64 ans[110][110] = {0};
    for(int i=1; i<=n; ++i) ans[i][i] = 1;
    while(p) {
        if( p&1 ) Mati_Mul(ans, a);
        Mati_Mul(a, a), p >>= 1;
    }
    for(int i=1; i<=n; ++i)
    for(int j=1; j<=n; ++j)
        a[i][j] = ans[i][j];
}

int main(int argc, char const *argv[])
{
    scanf("%lld%lld", &n, &k);
    for(int i=1; i<=n; ++i)
    for(int j=1; j<=n; ++j)
        scanf("%lld", &m[i][j]);
    Fast_Pow(m, k);
    for(int i=1; i<=n; ++i) {
    for(int j=1; j<=n; ++j)
        printf("%d ", m[i][j] % mod);
        printf("\n");
    }
    return 0;
}