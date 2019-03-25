/*
	首先讲倍增
	倍增的思想很简单，首先进行预处理，用一个深搜将每个点的深度和它向上跳一步到达的点（也就是它的父节点）处理出来，
	☆☆☆然后用下列递推式 f[i][j]=f[f[i][j-1]][j-1] 求出该点跳2^j步所到达的点。
	为什么是f[f[i][j-1]][j-1]？因为倍增每次都是跳的2的整数次幂步，而2^j=2^(j-1)+2^(j-1),这样就不难理解了。
	然后，对于每两个询问的点，只需要先找出那个点的深度更深，就将它跳跃到与另一个点深度相同；
	如果此时两个点相同，那么这个点就是最近公共祖先;如果不相同，两个点就一起跳，直找到最近公共祖先为止。
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;

const int maxn = 5e5 + 5e1;
int n, m, s, deep[maxn], step[maxn][21], head[maxn], edge_num;
struct Edge{
	int u, v, next;
} edge[2*maxn];

inline void read(int &x) {
	char ch = getchar(); x = 0;
	if( !isdigit(ch) )	ch = getchar();
	while( isdigit(ch) )
		x = (x*10)+(ch^48), ch = getchar(); 
}

inline void Init(int x) {
	for(int i=1; i<=20; ++i)
		for(int j=1; j<=x; ++j)
			step[j][i] = step[step[j][i-1]][i-1];
}

inline void Add_edge(int from, int to) {
	edge[++edge_num].v = to;
	edge[edge_num].next = head[from];
	head[from] = edge_num;
}

void Dfs(int x) {		//Dfs初始化各个节点深度 
	for(int i=head[x]; i; i=edge[i].next)
		if( !deep[edge[i].v] ) {	//尚未修改 
			deep[edge[i].v] = deep[x] + 1;
			step[edge[i].v][0] = x;
			Dfs(edge[i].v);
		}
}

int Lca(int a, int b) {
	if( deep[a]<deep[b] )	swap(a, b);
	for(int i=20; i>=0; --i) {		//较深的向上跳 
		if( deep[step[a][i]]>=deep[b] )
			a = step[a][i];
	}
	if( a==b )	return a;
	for(int i=20; i>=0; --i) {	//一起跳 
		if( step[a][i]!=step[b][i] )
			a = step[a][i], b = step[b][i];
	}
	return step[a][0];
}

int main() {
	int a, b;
	read(n), read(m), read(s);
	for(int i=1; i<n; ++i) {	//加n-1条边 
		read(a), read(b);
		Add_edge(a, b), Add_edge(b, a);
	}
	deep[s] = 1;
	Dfs(s), Init(n);
	for(int i=1; i<=m; ++i) {	//处理询问 
		read(a), read(b);
		printf("%d\n", Lca(a, b));
	}
	return 0;
}

/*
	什么是Tarjan(离线)算法呢？顾名思义，就是在一次遍历中把所有询问一次性解决，所以其时间复杂度是O(n+q)。
	Tarjan算法的优点在于相对稳定，时间复杂度也比较居中，也很容易理解。
	下面详细介绍一下Tarjan算法的基本思路：
	1.任选一个点为根节点，从根节点开始。
	2.遍历该点u所有子节点v，并标记这些子节点v已被访问过。
	3.若是v还有子节点，返回2，否则下一步。
	4.合并v到u上。
	5.寻找与当前点u有询问关系的点v。
	6.若是v已经被访问过了，则可以确认u和v的最近公共祖先为v被合并到的父亲节点a。
	遍历的话需要用到dfs来遍历，至于合并，最优化的方式就是利用并查集来合并两个节点。

	伪代码： 
	Tarjan(u)		//marge和find为并查集合并函数和查找函数
	{
	    for each(u,v)    //访问所有u子节点v
	    {
	        Tarjan(v);        //继续往下遍历
	        marge(u,v);    //合并v到u上
	        标记v被访问过;
	    }
	    for each(u,e)    //访问所有和u有询问关系的e
	    {
	        如果e被访问过;
	        u,e的最近公共祖先为find(e);
	    }
	}

*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5e5 + 5e1;
const int maxm = 1e6 + 1e1;
int n, m, s, edge_num1, edge_num2;
int p[maxn], ans[maxn], vis[maxn], head1[maxn], head2[maxn];
struct Edge{
	int v, num, next;
}edge1[maxm], edge2[maxm];

struct Union_Find_Set{		//日常3行UFS，合并 
	inline void Refl(int x) { for(int i=1; i<=x; ++i) p[i] = i; }
	int Find(int x) { return x==p[x] ? x : p[x]=Find(p[x]); }
	//inline void Unio(int x, int y) { p[Find(x)] = Find(y); }
	inline void Unio(int x, int y) { if( Find(x)!=Find(y) ) p[y] = x; }
				//这个Unio与普通的并查集板子有所不同。 
}ufs;
struct About_edge{
	inline void g1(int x, int y) {		//图G加边 
		edge1[++edge_num1].v = y;
		edge1[edge_num1].next = head1[x];
		head1[x] = edge_num1;
	}
	inline void g2(int x, int y, int z) {	//询问关系储存！！ 
		edge2[++edge_num2].v = y;
		edge2[edge_num2].num = z;
		edge2[edge_num2].next = head2[x];
		head2[x] = edge_num2;
	}
}Add_edge;

inline void read(int &x) {
	char ch = getchar(); x = 0;
	if( !isdigit(ch) )	ch = getchar();
	while( isdigit(ch) )
		x = (x*10)+(ch^48), ch = getchar();
}

void Tarjan(int x) {
	int tmp;  vis[x] = 1;
	for(int i=head1[x]; i; i=edge1[i].next) {
		if( !vis[edge1[i].v] )
			Tarjan(edge1[i].v), ufs.Unio(x, edge1[i].v);	//继续往下遍历并合并u，v 
		//vis[edge1[i].v] = 1;
	}
	for(int i=head2[x]; i; i=edge2[i].next) {	//访问所有和u有询问关系的e
		tmp = edge2[i].num;		//num代表第几次询问 
		if( vis[edge2[i].v] )  ans[tmp] = ufs.Find(edge2[i].v);	//如果e被访问过， u,v的最近公共祖先为find(v);
	}
}

int main() {
	int a, b;
	scanf("%d%d%d", &n, &m, &s);
	for(int i=1; i<n; ++i) {
		scanf("%d%d", &a, &b);
		Add_edge.g1(a, b);
		Add_edge.g1(b, a);
	}
	ufs.Refl(n);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d", &a, &b);
		Add_edge.g2(a, b, i);
		Add_edge.g2(b, a, i);
	}
	Tarjan(s);
	for(int i=1; i<=m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
