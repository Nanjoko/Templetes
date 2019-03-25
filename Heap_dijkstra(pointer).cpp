#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 1001;
struct node {
	int v,w;
	node* next;
	node(int a,int b,node* c): v(a),w(b),next(c) {}
}*adj[maxn];
struct sb {
	int d,u;
	int operator < (const sb& rhs) const {
		return this->d>rhs.d;
	}
};
int vis[maxn],dis1[maxn],dis2[maxn];
void dijkstra(int s,node** phqghume,int* dis) {
	memset(vis,0,sizeof(vis));
	priority_queue<sb> q;
	dis[s]=0;
	q.push((sb) {0,s});
	while(!q.empty()) {
		sb x=q.top();
		q.pop();
		int buf=x.u;
		if(vis[buf]) continue;
		vis[buf]=1;
		for(node* i=phqghume[buf]; i!=NULL; i=i->next) {
			if(dis[i->v]>dis[buf]+i->w) {
				dis[i->v]=dis[buf]+i->w;
				q.push((sb) {dis[i->v],i->v});
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	int m,n,b1,c1,c2,a,b,c;
	cin>>m>>n>>b1>>c1>>c2;
	for(int i=1; i<=m; ++i) {
		cin>>a>>b>>c;
		adj[a]=new node(b,c,adj[a]);
		adj[b]=new node(a,c,adj[b]);
	}
	dijkstra(b1,adj,dis1);
	dijkstra(c1,adj,dis2);
//	cout<<dis1[c1]<<" "<<dis1[c2]<<" "<<dis2[c1]<<" "<<dis2[c2]<<endl;
	int ans=min(dis1[c1]+dis2[c2],dis1[c2]+dis2[c1]);
	cout<<ans;
	return 0;
}
