#include<cstdio>
using namespace std;

const int maxn = 500000 + 500;
int a[maxn], n, m, cx, cy, cz, add;

int lowbit(int x)
{
	return x&(-x);
}

struct Bit{
	void Add(int node_num, int add_num)
	{
		for(int i=node_num; i<=n; i+=lowbit(i))
			a[i] += add_num;
	}
	int Sum(int k)
	{
		int sum=0;
		for(int i=k; i>=1; i-=lowbit(i))
			sum += a[i];
		return sum;
	}
	int Unio(int x, int y)
	{
		return Sum(x) - Sum(y-1);
	}
}bit;

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d", &add);
		bit.Add(i, add);
	}
	for(int i=1; i<=m; ++i)
	{
		scanf("%d%d%d", &cx, &cy, &cz);
		if( cx==1 )
			bit.Add(cy, cz);
		else
			printf("%d\n", bit.Unio(cz, cy));
	}
	return 0;
}
