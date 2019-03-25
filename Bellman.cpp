#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn = 500 + 50;
const int maxm = maxn * maxn;
struct Edge{
	int u, v, w;
	void Init(int cv, int cu)
	{
		this->u = cu;
		this->v = cv;
		this->w = 1;
	}
}edge[maxm];
int pre[maxn], dis[maxn], c[maxn];
int n, m, pc, pe, x;

int main()
{
	memset(dis, -1, n+1);
	cin >> n >> m;
	for(int i=1; i<=m; i++)
	{
		while( x = getchar() )
		{
			if( x>='0' && x<='9' )
				c[++pc]=x-48;
			if( x=='\n')
				break;
		}
		//cout << 0;
		while( pc )
			edge[++pe].Init(c[pc], c[--pc]);
		//cout << 1;
	}
	for(int i=1; i<=m; i++)
		cout << edge[i].u << " " << edge[i].v <<endl;
	return 0;
}
