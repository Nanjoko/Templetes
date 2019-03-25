#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 50;
const int maxm = 200000 + 200;
int unio[maxn];
int n, m, mx, my, mz, ans, k; 

struct Edge{
	int u, v, w;
	void Init(int cu, int cv, int cw){
		this->u = cu;
		this->v = cv;
		this->w = cw;
	}
}edge[maxm];

struct Ufs{
	void Init(int x)
	{
		for(int i=1; i<=x; ++i)
			unio[i] = i;
	}
	int Find(int x)
	{
		return x==unio[x]?x:unio[x]=Find(unio[x]);
	}
	void Unio(int x, int y)
	{
		unio[Find(x)] = Find(y);
	}
}ufs;

bool cmp(const Edge a, const Edge b)
{
	return a.w < b.w;
}

int main()
{
	cin >> n >> m;
	ufs.Init(n);
	for(int i=1; i<=m; ++i)
	{
		cin >> mx >> my >> mz;
		edge[i].Init(mx, my, mz);
	}
	sort(edge+1, edge+m+1, cmp);
	
	for(int i=1; i<=m; ++i)
	{
		if( ufs.Find(unio[edge[i].u]) != ufs.Find(unio[edge[i].v]) )
		{
			ufs.Unio(unio[edge[i].u], unio[edge[i].v]);
			++k;
			ans += edge[i].w;
		}
		if( k==n-1 )	break;
	}
	
	if( k==n-1 )	
		cout << ans;
	else	cout << "orz";
	return 0;
}
