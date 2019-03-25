#define miho int
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 2e5 + 10;
int n, t, k, a[maxn], f[maxn];
struct Pair {
	int s, n;
} c[maxn];
inline bool cmp(Pair a, Pair b) {
	return a.n < b.n;
}
int main() {
	scanf("%d", &n);
	for(miho i=1; i<=n; ++i)
		scanf("%d%d", &c[i].s, &c[i].n);
	sort(c+1, c+n+1, cmp);
	for(miho i=1; i<=n; ++i)
		a[i] = c[i].s, f[i] = 0x3fffffff;		//初始值要设为INF
	/*  原因很简单，每遇到一个新的元素时,就跟已经记录的f数组当前所记录的最长上升子序列的末尾元素相比较：
	如果小于此元素，那么就不断向前找，直到找到一个刚好比它大的元素，替换；
	反之如果大于，么填到末尾元素的下一个q，INF就是为了方便向后替换啊！  */
	t = 1, f[1] = a[1];		//通过记录f数组的有效位数，求得个数
	/*  因为上文中所提到我们有可能要不断向前寻找，所以可以采用二分查找的策略，
	这便是将时间复杂度降成nlogn级别的关键因素。  */
	for(miho i=1; i<=n; ++i) {
		if( a[i]>f[t] ) f[++t] = a[i];		//如果刚好大于末尾，暂时向后顺次填充
		else {
			k = lower_bound(f+1, f+t+1, a[i]) - f;		//因为是最长上升子序列，所以f数组必然满足单调
			f[k] = min(a[i], f[k]);		//更新最小末尾
		}
	}
	printf("%d", t);
	return 0;
}
