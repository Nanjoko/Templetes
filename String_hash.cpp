#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;

int n, ans = 1, prime = 19260817; 
ull a[10010], base = 131;
char s[1600];
ull mod = 212370440130137957ll;
ull hash(char *s)
{
    int len = strlen(s);
    ull h = 0;
    for (int i=0; i<len; ++i)
        h = h*base + (ull)s[i];
    return h&0x7fffffff;
}


int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) {
		scanf("%s", s);
		a[i] = hash(s);
	}
	sort(a+1, a+n+1);
	for(int i=2; i<=n; ++i) {
		if( a[i]!=a[i-1] ) 
			++ans;
	}
	printf("%d", ans);
	return 0;
}




ull hashs(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
        ans=ans*base+(ull)s[i];
    return ans&0x7fffffff;
}
ull hashe(char s[])
{
    int len=strlen(s);
    ull ans=0;
    for (int i=0;i<len;i++)
    ans=(ans*base+(ull)s[i])%mod+prime;
    return ans;
}
