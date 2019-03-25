/*
	朴素LCS：
	譬如给定2个序列：
	1 2 3 4 5
	3 2 1 4 5
	试求出最长的公共子序列。
	显然长度是3，包含3 4 5 三个元素.

	解析：我们可以用dp[i][j]来表示第一个串的前i位，第二个串的前j位的LCS的长度，那么我们是很容易想到状态转移方程的：
	如果当前的a1[i]和a2[j]相同（即是有新的公共元素） 那么：dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
	如果不相同，即无法更新公共元素，考虑继承：dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
*/
// n*n算法
#include<cstdio>
#include<algorithm>
using namespace std;
int dp[1001][1001], a1[2001], a2[2001], n, m;
int main() {
	//dp[i][j]表示两个串从头开始，直到第一个串的第i位和第二个串的第j位最多有多少个公共子元素
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) scanf("%d", &a1[i]);
	for(int i=1; i<=m; ++i) scanf("%d", &a2[i]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if( a1[i]==a2[j] )
				dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);  //更新，+1；
		}
	printf("%d", dp[n][m]);
	return 0;
}

/*
	考虑nlogn的做法：
	因为两个序列都是1~n的全排列，那么两个序列元素互异且相同，也就是说只是位置不同罢了，
	那么我们通过一个map数组将a序列的数字在b序列中的位置表示出来；
	因为最长公共子序列是按位向后比对的，所以a序列每个元素在b序列中的位置如果递增，
	就说明b中的这个数在a中的这个数整体位置偏后，可以考虑纳入LCS；
	那么就可以转变成nlogn求用来记录新的位置的p数组中的LIS。
*/
// n*logn算法
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 10; 
int n, a[maxn], b[maxn], p[maxn], f[maxn];
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	for(int i=1; i<=n; ++i) scanf("%d", &b[i]);
	for(int i=1; i<=n; ++i)
		p[a[i]] = i, f[i] = 0x7fffffff;
	int t = 0;  f[0] = 0;
	for(int i=1; i<=n; ++i) {
		if( p[b[i]]>f[t] ) f[++t] = p[b[i]];
		else { 
			int x = lower_bound(f, f+t+1, p[b[i]]) - f;
			f[x] = min(p[b[i]], f[x]);
		}
	}
	printf("%d", t);
	return 0;
}

// Although there're difficulties ahead of us,remember:
// 就算出走半生，归来仍要是少年.

