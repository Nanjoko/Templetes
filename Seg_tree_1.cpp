/*
	操作1： 格式：1 x y k 含义：将区间[x,y]内每个数加上k
	操作2： 格式：2 x y 含义：输出区间[x,y]内每个数的和
*/
#include<cstdio>
#define lch x<<1
#define rch (x<<1)|1

const int maxn = 1e5 + 1e1;
int num[maxn], n, m, ques, quesl, quesr, add_num;
long long add[maxn*4], sum[maxn*4];

void Build(int x, int lef, int righ) {
	if( lef==righ ) {
		sum[x] = num[lef];
		return ;
	}
	int mid = (lef+righ)>>1;
	Build(lch, lef, mid);
	Build(rch, mid+1, righ);
	sum[x] = sum[lch] + sum[rch];
}

void Tain(int x, int lef, int righ) {
	sum[x] = 0;
	if( righ>lef ) {
		sum[x] = sum[lch] + sum[rch];
	}
	sum[x] += add[x]*( righ-lef+1 );
}

void Add(int x, int lef, int righ) {
	if( lef>=quesl && quesr>=righ ) {
		add[x] += add_num;
		sum[x] += add_num*( righ-lef+1 );
		return ;
	}
	int mid = (lef+righ)>>1;
	if( quesl<=mid ) {
		Add(lch, lef, mid);
		}
	if( quesr>mid ) {
		Add(rch, mid+1, righ);
	}
	Tain(x, lef, righ);
}

long long Query(int x, int lef, int righ, long long fac_add) {
	if( lef>=quesl && righ<=quesr ) {
		return sum[x] + fac_add*( righ-lef+1 );
	}
	int mid = (lef+righ)>>1;
	long long fac_sum = 0;
	if( quesl<=mid ) {
		fac_sum += Query(lch, lef, mid, fac_add+add[x]);
	}
	if( quesr>mid ) {
		fac_sum += Query(rch, mid+1, righ, fac_add+add[x]);
	}
	return fac_sum;
}
/*
void Print() {
	for(int i=1; i<=n<<1; ++i) {
		printf("%d %lld ", i, add[i]);
		printf("%lld\n", sum[i]);
	}
}
*/
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i) {
		scanf("%d", &num[i]);
	}
	Build(1, 1, n);
	
	for(int i=1; i<=m; ++i) {
		scanf("%d%d%d", &ques, &quesl, &quesr);
		if( ques==1 ) {
			scanf("%d", &add_num);
			Add(1, 1, n);
		}
		else {
			printf("%lld\n", Query(1, 1, n, 0));
		}
	}
	
	return 0;
}
