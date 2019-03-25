/*
�����Ŀ����״�����һ����չ,����״�����п�����ǰ i ��ĺ�����ʾ�� i ����.
��ô���� x ~ y ����������޸ĵ�ʱ����Ҫ����״�����еĵ� x ��λ�� + k, �� y + 1 ��λ�� -k
������ά���������״����
���ʱ��ֱ�������ѯ����
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
