#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    long long b, p ,k, ans=1;
    cin >> b >> p >> k;
    for(int i=1; i<=p; ++i)
    {
    	ans *= b;
		ans %= k; 
	}
	printf("%lld^%lld mod %lld=%lld", b, p, k, ans);
    return 0;
}

inline void pow(int x, int y, int& ans) {
	for(ans=1; y; y>>=1, x=mul(x, x))
		if( y&1 )	ans = mul(ans, x);
}