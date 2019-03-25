#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 100;
int a[maxn], m, n, ans[2], b;
int BiSearch(int l, int r, int x)
{
	int mid, ans;
	while( l<=r )
	{
		mid = (l+r)/2;
		if( a[mid]==x )	return mid;
		x>a[mid] ? l=mid+1 : r=mid-1;
	}
	return -1;
}

int main()
{
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> a[i];
	sort(a+1, a+n+1);
	cin >> m;
	for(int i=1; i<=n; ++i)
	{
		ans[0] = i;
		ans[1] = BiSearch(1, n, m-a[i]);
		if( ans[1]!=-1 && ans[0]-ans[1] )
		{
			b = 1;
			break;
		}
	}
	if( b )
		cout << a[ans[0]] << " " << a[ans[1]];
	else	cout << "No";
	return 0;
}
