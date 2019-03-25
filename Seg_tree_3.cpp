#include<cstring>
#include<cstdio>
#define N 100001
using namespace std;
int n, m, k, p;
int x, y, t;
int ll[4*N], rr[4*N];
long long sum[4*N];
long long flag1[4*N],flag2[4*N];
void tree_up(int now) {
	sum[now] =sum[now*2] + sum[now*2+1];
}
void tree_down(int now) {
	if(k == 1) {
		flag1[now*2] *= flag1[now];
		flag2[now*2] *= flag1[now];
		flag1[now*2+1] *= flag1[now];
		flag2[now*2+1] *= flag1[now];
		sum[now*2] *= flag1[now];
		sum[now*2+1] *= flag1[now];
		flag1[now] = 1;
	}
	else {
		flag2[now*2] += flag2[now];
		flag2[now*2+1] += flag2[now];
		sum[now*2] += (rr[now*2]-ll[now*2]+1) * flag2[now];
		sum[now*2+1] += (rr[now*2+1]-ll[now*2+1]+1) * flag2[now];
		flag2[now] = 0;
	}
	return ;
}
void tree_build(int now, int l, int r) {
	ll[now] = l; rr[now] = r;
	if(l == r) {
		scanf("%I64d", &sum[now]);
		return ;
	}
	int mid = (l+r) / 2;
	tree_build(now*2, l, mid);
	tree_build(now*2+1, mid+1, r);
	tree_up(now); 
}
void tree_change1(int now, int l, int r) {
	if(ll[now]==l && rr[now]==r) {
		sum[now] = (sum[now]*t) % p;
		flag1[now] = (flag1[now] * t) % p;
		return ;
	}
	if(flag1[now] || flag2[now]!=1) tree_down(now);
	int mid = (ll[now]+rr[now]) / 2;
	if(l<=mid && mid<r) tree_change1(now*2, l, mid), tree_change1(now*2+1, mid+1, r);
	else if(r<=mid) tree_change1(now*2, l, r);
			else tree_change1(now*2+1, l, r);
	tree_up(now);
}
void tree_change2(int now, int l, int r) {
	if(ll[now]==l && rr[now]==r) {
		sum[now] += (rr[now]-ll[now]+1) * t;
		flag2[now] += t;
		return ;
	}
	if(flag2[now] || flag1[now]!=1) tree_down(now);
	int mid = (ll[now]+rr[now]) / 2;
	if(l<=mid && mid<r) tree_change2(now*2, l, mid), tree_change2(now*2+1, mid+1, r);
	else if(r <= mid) tree_change2(now*2, l, r);
			else tree_change2(now*2+1, l, r);
	tree_up(now);
}
long long tree_query(int now, int l, int r) {
	if(ll[now]==l && rr[now]==r)
		return sum[now];
	int mid = (ll[now]+rr[now]) / 2;
	if(l<=mid && mid<r) return tree_query(now*2, l, mid)%p + tree_query(now*2+1, mid+1, r)%p;
	else if(r <= mid) return tree_query(now*2, l, r);
			else return tree_query(now*2+1, l, r);
}
int main() {
	scanf("%d%d%d", &n, &m, &p);
	memset(flag1, 1, sizeof(flag1));
	tree_build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		scanf("%d", &k);
		if(k == 1) { scanf("%d%d%d", &x, &y, &t); tree_change1(1, x, y); }
		if(k == 2) { scanf("%d%d%d", &x, &y, &t); tree_change2(1, x, y); }
		if(k == 3) { scanf("%d%d", &x, &y); printf("%I64d\n", tree_query(1, x, y)); }
	}
	return 0;
}
