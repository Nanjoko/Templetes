/*
	ST表是利用的是倍增的思想
	拿最大值来说
	我们用Max[i][j]表示，从i位置开始的2^j个数中的最大值，
	例如Max[i][1]表示的是i位置和i+1位置中两个数的最大值.
	查询的时候也比较简单,我们计算出log2(区间长度)
	然后对于左端点和右端点分别进行查询，这样可以保证一定可以覆盖查询的区间
	刚开始学的时候我不太理解为什么从右端点开始查的时候左端点是r−2k+1
	实际很简单，因为我们需要找到一个点x，使得x+2k−1=r
	这样的话就可以得到x=r−2k+1
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;
int n, m, a[maxn][21], lg[maxn];

inline void read(int &x) {
	register char ch = 0;  x = 0;
	while( !isdigit(ch) ) ch = getchar();
	while( isdigit(ch) ) x = (x * 10) + (ch ^ 48)， ch = getchar();
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) read(a[i][0]);
	for(int j = 1; j <= 20; ++j)
		for(int i = 1; i + (1 << j) - 1 <= n; ++i)	//注意这里要控制边界 
				a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
	int tmp = 3;
	for(int i = 3; i <= n; ++i) {		// 处理log2(i)
		lg[i] = lg[i - 1];
		if( i == tmp )  ++lg[i], tmp = (tmp << 1) - 1;
	}
	int l, r, ans;
	for(int i = 1; i <= m; ++i) {
		read(l), read(r);
		int t = lg [r - l + 1];
		ans = max(a[l][t], a[r - (1 << t) + 1][t]);	//把拆出来的区间分别取最值 
		printf("%d\n", ans);
	}
	return 0;
}