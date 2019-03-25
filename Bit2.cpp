/*
这个题目是树状数组的一个拓展,在树状数组中可以用前 i 项的和来表示第 i 个数.
那么当对 x ~ y 的区间进行修改的时候需要在树状数组中的第 x 个位置 + k, 第 y + 1 个位置 -k
这样便维护了这个树状数组
输出时候直接输出查询即可
*/
#include<iostream>
using namespace std;

const int maxn = 500000 + 500;
int a[maxn], c, n, m, b, x, y, k;
int lowbit(int x)
{
	return x&(-x);
}
struct Bit{
	void Init(int x)
	{
		int last=0, now;
        for (int i=1; i<=x; ++i)
        {
            cin >> now;
            Add(i, now - last);
            last = now;
        }
	}
void Add(int node, int add)
	{
		for(int i=node; i<=n; i+=lowbit(i))
			a[i] += add;
	}
	int Sum(int x)
	{
		int sum=0;
		for(int i=x; i>=1; i-=lowbit(i))
			sum += a[i];
		return sum;
	}
	void Unio(int x1, int x2, int ck)
	{
			Add(x1, ck);
			Add(x2+1, -ck);
	}
}bit;

int main()
{
	cin >> n >> m;
	bit.Init(n);
	for(int i=1; i<=m; ++i)
	{
		cin >> b;
		if( b==1 ) {
			cin >> x >> y >> k;
			bit.Unio(x, y, k);
		}
		else{
			cin >> x;
			cout << bit.Sum(x) << endl;
		}
	}
	return 0;	
}
