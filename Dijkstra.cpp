#include<iostream>
using namespace std;

const int maxn = 1000 + 10;
long long g[maxn][maxn];
long long dis[maxn], b[maxn];
int k, n, m, u, v, w, ans=1;
int minn, maxx = 0x7fffffff;

int main()
{
	cin >> n >> m;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			g[i][j] = maxx;
	for(int i=1; i<=n; ++i)
	{
		cin >> u >> v >> w;
		g[u][v] = w; 
	}
	for(int i=1; i<=n; ++i)
		dis[i] = g[1][i];
	dis[1] = 0;	b[1] = 1;
	
	for(int i=1; i<=n; ++i)
	{
		minn = maxx;
		k = 0;
		for(int j=1; j<=n; ++j)
			if( !b[j] && dis[j]<minn )
			{
				minn = dis[j];
				k = j;
			}
		if( !k )	break;
		b[k] = 1;
		for(int j=1; j<=n; ++j)
			if( (g[k][j]!=0x7fffffff) && (dis[k]*g[k][j]<dis[j]) )
			    dis[j] = dis[k] * g[k][j];
	}
	
	cout << dis[n] % 9987;
	return 0;
}
