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
		a[i] = c[i].s, f[i] = 0x3fffffff;		//��ʼֵҪ��ΪINF
	/*  ԭ��ܼ򵥣�ÿ����һ���µ�Ԫ��ʱ,�͸��Ѿ���¼��f���鵱ǰ����¼������������е�ĩβԪ����Ƚϣ�
	���С�ڴ�Ԫ�أ���ô�Ͳ�����ǰ�ң�ֱ���ҵ�һ���պñ������Ԫ�أ��滻��
	��֮������ڣ�ô�ĩβԪ�ص���һ��q��INF����Ϊ�˷�������滻����  */
	t = 1, f[1] = a[1];		//ͨ����¼f�������Чλ������ø���
	/*  ��Ϊ���������ᵽ�����п���Ҫ������ǰѰ�ң����Կ��Բ��ö��ֲ��ҵĲ��ԣ�
	����ǽ�ʱ�临�ӶȽ���nlogn����Ĺؼ����ء�  */
	for(miho i=1; i<=n; ++i) {
		if( a[i]>f[t] ) f[++t] = a[i];		//����պô���ĩβ����ʱ���˳�����
		else {
			k = lower_bound(f+1, f+t+1, a[i]) - f;		//��Ϊ������������У�����f�����Ȼ���㵥��
			f[k] = min(a[i], f[k]);		//������Сĩβ
		}
	}
	printf("%d", t);
	return 0;
}
