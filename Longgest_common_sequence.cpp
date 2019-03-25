/*
	����LCS��
	Ʃ�����2�����У�
	1 2 3 4 5
	3 2 1 4 5
	�������Ĺ��������С�
	��Ȼ������3������3 4 5 ����Ԫ��.

	���������ǿ�����dp[i][j]����ʾ��һ������ǰiλ���ڶ�������ǰjλ��LCS�ĳ��ȣ���ô�����Ǻ������뵽״̬ת�Ʒ��̵ģ�
	�����ǰ��a1[i]��a2[j]��ͬ���������µĹ���Ԫ�أ� ��ô��dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
	�������ͬ�����޷����¹���Ԫ�أ����Ǽ̳У�dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
*/
// n*n�㷨
#include<cstdio>
#include<algorithm>
using namespace std;
int dp[1001][1001], a1[2001], a2[2001], n, m;
int main() {
	//dp[i][j]��ʾ��������ͷ��ʼ��ֱ����һ�����ĵ�iλ�͵ڶ������ĵ�jλ����ж��ٸ�������Ԫ��
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) scanf("%d", &a1[i]);
	for(int i=1; i<=m; ++i) scanf("%d", &a2[i]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if( a1[i]==a2[j] )
				dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);  //���£�+1��
		}
	printf("%d", dp[n][m]);
	return 0;
}

/*
	����nlogn��������
	��Ϊ�������ж���1~n��ȫ���У���ô��������Ԫ�ػ�������ͬ��Ҳ����˵ֻ��λ�ò�ͬ���ˣ�
	��ô����ͨ��һ��map���齫a���е�������b�����е�λ�ñ�ʾ������
	��Ϊ������������ǰ�λ���ȶԵģ�����a����ÿ��Ԫ����b�����е�λ�����������
	��˵��b�е��������a�е����������λ��ƫ�󣬿��Կ�������LCS��
	��ô�Ϳ���ת���nlogn��������¼�µ�λ�õ�p�����е�LIS��
*/
// n*logn�㷨
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
// ������߰�����������Ҫ������.

