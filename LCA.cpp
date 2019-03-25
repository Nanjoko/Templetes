/*
	���Ƚ�����
	������˼��ܼ򵥣����Ƚ���Ԥ������һ�����ѽ�ÿ�������Ⱥ���������һ������ĵ㣨Ҳ�������ĸ��ڵ㣩���������
	����Ȼ�������е���ʽ f[i][j]=f[f[i][j-1]][j-1] ����õ���2^j��������ĵ㡣
	Ϊʲô��f[f[i][j-1]][j-1]����Ϊ����ÿ�ζ�������2���������ݲ�����2^j=2^(j-1)+2^(j-1),�����Ͳ�������ˡ�
	Ȼ�󣬶���ÿ����ѯ�ʵĵ㣬ֻ��Ҫ���ҳ��Ǹ������ȸ���ͽ�����Ծ������һ���������ͬ��
	�����ʱ��������ͬ����ô�������������������;�������ͬ���������һ������ֱ�ҵ������������Ϊֹ��
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

void Dfs(int x) {		//Dfs��ʼ�������ڵ���� 
	for(int i=head[x]; i; i=edge[i].next)
		if( !deep[edge[i].v] ) {	//��δ�޸� 
			deep[edge[i].v] = deep[x] + 1;
			step[edge[i].v][0] = x;
			Dfs(edge[i].v);
		}
}

int Lca(int a, int b) {
	if( deep[a]<deep[b] )	swap(a, b);
	for(int i=20; i>=0; --i) {		//����������� 
		if( deep[step[a][i]]>=deep[b] )
			a = step[a][i];
	}
	if( a==b )	return a;
	for(int i=20; i>=0; --i) {	//һ���� 
		if( step[a][i]!=step[b][i] )
			a = step[a][i], b = step[b][i];
	}
	return step[a][0];
}

int main() {
	int a, b;
	read(n), read(m), read(s);
	for(int i=1; i<n; ++i) {	//��n-1���� 
		read(a), read(b);
		Add_edge(a, b), Add_edge(b, a);
	}
	deep[s] = 1;
	Dfs(s), Init(n);
	for(int i=1; i<=m; ++i) {	//����ѯ�� 
		read(a), read(b);
		printf("%d\n", Lca(a, b));
	}
	return 0;
}

/*
	ʲô��Tarjan(����)�㷨�أ�����˼�壬������һ�α����а�����ѯ��һ���Խ����������ʱ�临�Ӷ���O(n+q)��
	Tarjan�㷨���ŵ���������ȶ���ʱ�临�Ӷ�Ҳ�ȽϾ��У�Ҳ��������⡣
	������ϸ����һ��Tarjan�㷨�Ļ���˼·��
	1.��ѡһ����Ϊ���ڵ㣬�Ӹ��ڵ㿪ʼ��
	2.�����õ�u�����ӽڵ�v���������Щ�ӽڵ�v�ѱ����ʹ���
	3.����v�����ӽڵ㣬����2��������һ����
	4.�ϲ�v��u�ϡ�
	5.Ѱ���뵱ǰ��u��ѯ�ʹ�ϵ�ĵ�v��
	6.����v�Ѿ������ʹ��ˣ������ȷ��u��v�������������Ϊv���ϲ����ĸ��׽ڵ�a��
	�����Ļ���Ҫ�õ�dfs�����������ںϲ������Ż��ķ�ʽ�������ò��鼯���ϲ������ڵ㡣

	α���룺 
	Tarjan(u)		//marge��findΪ���鼯�ϲ������Ͳ��Һ���
	{
	    for each(u,v)    //��������u�ӽڵ�v
	    {
	        Tarjan(v);        //�������±���
	        marge(u,v);    //�ϲ�v��u��
	        ���v�����ʹ�;
	    }
	    for each(u,e)    //�������к�u��ѯ�ʹ�ϵ��e
	    {
	        ���e�����ʹ�;
	        u,e�������������Ϊfind(e);
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

struct Union_Find_Set{		//�ճ�3��UFS���ϲ� 
	inline void Refl(int x) { for(int i=1; i<=x; ++i) p[i] = i; }
	int Find(int x) { return x==p[x] ? x : p[x]=Find(p[x]); }
	//inline void Unio(int x, int y) { p[Find(x)] = Find(y); }
	inline void Unio(int x, int y) { if( Find(x)!=Find(y) ) p[y] = x; }
				//���Unio����ͨ�Ĳ��鼯����������ͬ�� 
}ufs;
struct About_edge{
	inline void g1(int x, int y) {		//ͼG�ӱ� 
		edge1[++edge_num1].v = y;
		edge1[edge_num1].next = head1[x];
		head1[x] = edge_num1;
	}
	inline void g2(int x, int y, int z) {	//ѯ�ʹ�ϵ���棡�� 
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
			Tarjan(edge1[i].v), ufs.Unio(x, edge1[i].v);	//�������±������ϲ�u��v 
		//vis[edge1[i].v] = 1;
	}
	for(int i=head2[x]; i; i=edge2[i].next) {	//�������к�u��ѯ�ʹ�ϵ��e
		tmp = edge2[i].num;		//num����ڼ���ѯ�� 
		if( vis[edge2[i].v] )  ans[tmp] = ufs.Find(edge2[i].v);	//���e�����ʹ��� u,v�������������Ϊfind(v);
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
